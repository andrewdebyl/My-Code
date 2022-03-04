'use strict'

// C library API
const ffi = require('ffi-napi');
const mysql = require('mysql2/promise');
let con;

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname+'/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');


let parserLibrary = ffi.Library("./parser/bin/libgpxparser.so", {

  "GPXfileToJSON": ["string", ["string"]],
  "validateGPXFile":["bool",["string","string"]],
  "fileDetailsToJSON": ["string",["string"]],
  "changeComponentName":["bool",["string","string","string"]],
  "addNewRoute":["bool",["string","string", "string","string", "int"]],
  "routesToJSON": ["string", ["string"]],
  "listWaypointstoJSON": ["string",["string","string"]]
});


// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }
 
  let uploadFile = req.files.uploadFile;
 
  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: '+err);
      res.send('');
    }
  });
});

//******************** Your code goes here ******************** 

//Sample endpoint
app.get('/endpoint1', function(req , res){
  let retStr = req.query.stuff + " " + req.query.junk;
  res.send({
    stuff: retStr
  });
});

app.get('/fileLogLoad', function(req , res){
  var temp = getGPXMetadata();
  res.send({
    fileLogInfo:temp
  });
});

app.get('/fileNamesToDropDown', function(req,res){
  var schemaFile = getSchemaFile();
  var dirPath = fs.readdirSync(path.join(__dirname+'/uploads/'));

  var vaildFileNames=[];

  for (var file of dirPath)
  {
    if (parserLibrary.validateGPXFile("./uploads/"+file,schemaFile)==true)
    {
      vaildFileNames.push(file);
    }
  }
  console.log(vaildFileNames);
  console.log(schemaFile);
  res.send(vaildFileNames);
});

app.get('/getGPXData',function(req,res){
  var requestObj = req.query;
  var fileName = requestObj.fileName;
  var GPXData = parserLibrary.fileDetailsToJSON("./uploads/"+fileName);
  res.send(GPXData);
});

app.get('/changeComponentName',function(req,res){
  var requestObj = req.query;
  var filename = "./uploads/" +requestObj.filename;
  var oldName = requestObj.oldName;
  var newName = requestObj.newName;

  console.log(filename);
  console.log(oldName);
  console.log(newName);
  
  res.send(parserLibrary.changeComponentName(filename,newName,oldName));
});

app.get('/addroute',function(req,res){
  var requestObj = req.query;
  var filename = "./uploads/" +requestObj.filename;
  var routename = requestObj.routename;
  var latitude = requestObj.startlat;
  var longitude = requestObj.startlon;
  
  var count = requestObj.numPoints;

  res.send(parserLibrary.addNewRoute(filename,routename,latitude,longitude,count));
});

//A4 Functions
app.get('/connecttodatabase', async function(req,res){
  var requestObj = req.query;
  var host = requestObj.host;
  var username = requestObj.user;
  var database = requestObj.db;
  var password = requestObj.pw;

  try
  {
    con = await mysql.createConnection({
      host: host,
      user: username,
      password: password,
      database: database
    });

    createTables();

    var filesArr = getGXPFilesAsJSON();

    for (var file of filesArr)
    {
      file = JSON.parse(file);

      var doesExist = await doesFileExist(file.fileName.replace("./uploads/",""));

      if (doesExist==true)
      {
        continue;
      }
      
      var sql = addJSONToSQLFileTable(file);
      await con.execute(sql);
      
      var routes = parserLibrary.routesToJSON(file.fileName);
      routes = JSON.parse(routes);

      if (routes.length == 0)
      {
        continue;
      }

      var [rows, fields] = await con.execute(`SELECT gpx_id FROM FILE WHERE file_name="${file.fileName.replace("./uploads/","")}"`);
      
      var gpx_id = rows[0].gpx_id;

      for (var route of routes)
      {

        sql = routeToSQL(route, gpx_id);
        await con.execute(sql);

        [rows,fields] = await con.execute(`SELECT route_id FROM ROUTE WHERE route_name="${route.name}"`);

        var route_id = rows[0].route_id;
        var waypoints = parserLibrary.listWaypointstoJSON(file.fileName, route.name);
        waypoints=JSON.parse(waypoints);

        for (var waypoint of waypoints)
        {
          sql = waypointToSQL(waypoint, route_id);
          await con.execute(sql);
        }
      }
    }
    res.send(true);
  }
  catch(e)
  {
    res.send(false);
  }
});

app.get('/deletetables', async function(req,res){
  await con.execute("DELETE FROM POINT;");
  await con.execute("DELETE FROM ROUTE;");
  await con.execute("DELETE FROM FILE;");

  res.send(true);
});

app.get('/displaytables', async function (req,res){
  try
  {
    var [rows,fields] = await con.execute("SELECT COUNT(*) AS numfiles FROM FILE;");
    var numfiles = rows[0].numfiles;
    [rows,fields] = await con.execute("SELECT COUNT(*) AS numroutes FROM ROUTE;");
    var numroutes = rows[0].numroutes;
    [rows,fields] = await con.execute("SELECT COUNT(*) AS numpoints FROM POINT;");
    var numpoints = rows[0].numpoints;

    var obj = {
      numfiles: numfiles,
      numpoints: numpoints,
      numroutes: numroutes
    }

    res.send(obj);
  }
  catch (e)
  {
    res.send(false);
  }
});

app.listen(portNum);
console.log('Running app at localhost: ' + portNum);

function getGPXMetadata ()
{
  var dirPath = fs.readdirSync(path.join(__dirname+'/uploads/'));
  var array = [];

  for (var file of dirPath)
  {
    var json = parserLibrary.GPXfileToJSON(path.join(__dirname+'/uploads/'+file));
    array.push(json);
  }
  var thing = JSON.stringify(array);
  return thing;
}

function getSchemaFile()
{
  var dirPath = fs.readdirSync(path.join(__dirname+'/uploads/'));

  for (var file of dirPath)
  {
    if (file.includes(".xsd"))
    {
      return "./uploads/"+file;
    }
  }
  return null;
}

async function createTables()
{
  var filetable = "CREATE TABLE IF NOT EXISTS FILE (gpx_id INT AUTO_INCREMENT PRIMARY KEY, file_name VARCHAR(60) NOT NULL, ver DECIMAL(2,1) NOT NULL, creator VARCHAR(256));";
  await con.execute(filetable);

  var routetable = "CREATE TABLE IF NOT EXISTS ROUTE (route_id INT AUTO_INCREMENT PRIMARY KEY, route_name VARCHAR(256), route_len FLOAT(15,7) NOT NULL, gpx_id INT NOT NULL, FOREIGN KEY(gpx_id) REFERENCES FILE(gpx_id) ON DELETE CASCADE);";
  await con.execute(routetable);

  var wpttable = "CREATE TABLE IF NOT EXISTS POINT (point_id INT AUTO_INCREMENT PRIMARY KEY, point_index INT NOT NULL, latitude DECIMAL(11,7) NOT NULL, longitude DECIMAL(11,7) NOT NULL, point_name VARCHAR(256), route_id INT NOT NULL, FOREIGN KEY(route_id) REFERENCES ROUTE(route_id) ON DELETE CASCADE);";
  await con.execute(wpttable);
}


function addJSONToSQLFileTable (json)
{
  var headers = "(file_name, ver, creator)";
  var values = "(" + "\"" + json.fileName.replace("./uploads/","") + "\", " + json.version.toString() + ", " + "\"" + json.creator + "\")";
  
  var q = "INSERT INTO FILE" + headers + " VALUES " + values + ";";
  
  return q;
}

function getGXPFilesAsJSON ()
{
  var dirPath = fs.readdirSync(path.join(__dirname+'/uploads/'));
  var jsons=[];

  var schemafile = getSchemaFile();

  for (var fileName of dirPath)
  {
    if (parserLibrary.validateGPXFile("./uploads/"+fileName, schemafile)==true)
    {
      jsons.push(parserLibrary.GPXfileToJSON("./uploads/"+fileName));
    }
  }
  return jsons;
}

function routeToSQL (route, key)
{
  var headers = `(route_name, route_len, gpx_id)`;
  var values = `("${route.name}", ${route.len}, ${key})`;

  return `INSERT INTO ROUTE ${headers} VALUES ${values};`;
}

function waypointToSQL (waypoint, key)
{
  var headers = `(point_index, point_name, latitude, longitude, route_id)`;
  var values = `(${waypoint.ptindex}, "${waypoint.name}", ${waypoint.lat}, ${waypoint.lon}, ${key})`;

  return `INSERT INTO POINT ${headers} VALUES ${values};`;
}

async function doesFileExist (filename)
{
  var [rows,fields] = await con.execute("SELECT file_name FROM FILE;");
  for (var row of rows)
  {
    if (row.file_name == filename)
    {
      return true;
    }
  }
  return false;
}