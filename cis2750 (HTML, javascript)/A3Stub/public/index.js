// Put all onload AJAX calls here, and event listeners

let currentFileName="";
let currentComponent="";

function appendFileNameToDropDown(json)
{
    var html = "<a class=\"dropdownlink\" href="+"\""+json+"\""+">"+json+"</a>";
    $("#myDropdown").append(html);
}

function appendGPXDataToTable(obj)
{
    var component = obj.component;
    var name =obj.name;
    var numPoints = obj.numPoints.toString();
    var length = obj.len.toString();
    var loop = obj.loop.toString();
    var html = "<tr>"+"<td>"+component+"</td>"+
    "<td>" + "<a class=\"componentName\" href="+"\""+name+"\""+">"+name+"</a></td>"
    + "<td>" +numPoints+"</td>"
    + "<td>" +length+"</td>"
    +"<td>" +loop+"</td>"+"</tr>";
    $('#GPXViewPanel').find('tbody').append(html);
}


function fileLogJSONtoHTML(jsonArray) {
    var obj = JSON.parse(jsonArray);
    var ver = obj.version;
    var cre = obj.creator;
    var numWpt = obj.numWaypoints;
    var numTrk = obj.numTracks;
    var filename = obj.fileName;
    var numRt = obj.numRoutes;
    
    var fn = filename.split("/");    

    var html = "<tr>"+ "<td>" + "<a class=\"downloadLink\" href=\"#GPXViewPanel\">" +fn[fn.length-1] + "</a>" + "</td>"+"<td>"+ver.toString()+"</td>"+"<td>"+cre+"</td>"+"<td>"+numWpt.toString()+"</td>"+"<td>"+numTrk.toString()+"</td>"+"<td>"+numRt.toString()+"</td>"+"</tr>";
console.log(html);
    return html;
}


$(document).ready(function () {
    // On page-load AJAX Example
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/endpoint1',   //The server endpoint we are connecting to
        data: {
            stuff: "Value 1",
            junk: "Value 2"
        },
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
            $('#blah').html("On page load, received string '" + data.stuff + "' from server");
            //We write the object to the console to show that the request was successful
            console.log(data);

        },
        fail: function (error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error);
        }
    }); // end of ajax call

    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
    $('#someform').submit(function (e) {
        $('#blah').html("Form has data: " + $('#entryBox').val());
        e.preventDefault();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
        });
    }); // end of someform

    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/fileLogLoad',   //The server endpoint we are connecting to
        
        success: function (data) {
            var listOfJSON = JSON.parse(data.fileLogInfo);
            for (var json of listOfJSON)
            {
                $('#fileLogTable').find('tbody').append(fileLogJSONtoHTML(json));
            }
        },

        fail: function (error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error);
        }
    }); // end of ajax

    var text = $('.downloadLink').find('font');
    console.log(text);

    $.ajax({
        type: 'get',
        dataType: 'json',
        url: '/fileNamesToDropDown',

        success: function (data){
            console.log(data);
            for (var fileName of data)
            {
                appendFileNameToDropDown(fileName);
            }
        },

        fail: function(error){
            console.log(error);
        }
    });

    $(document).on('click',".dropdownlink",function(e){
        e.preventDefault();

        $('#GPXViewPanel').find('tbody').empty();

        currentFileName=$(this).text().toString();

        $.ajax({
            type: 'get',
            dataType: 'json',
            url: '/getGPXData',

            data: {
                fileName: currentFileName
            },

            success: function(data)
            {
                for (var obj of data)
                {
                    appendGPXDataToTable(obj);
                }
            },

            fail: function(error)
            {
                console.log(error);
            }
        });
    });


    $(document).on('click',"#renameBtn",function(e){
            
        e.preventDefault();
        alert("changing name");

        $.ajax({
            type:'get',
            dataType: 'json',
            url: '/changeComponentName',

            data:{
                filename: currentFileName,
                oldName: $('#oldnamebox').val(),
                newName: $("#renameBox").val()
            },

            success: function(data)
            {
                if (data==true)
                {
                    alert("successfully changed com name");
                }
                else{
                    alert("failed to changed com name");
                }
            },

            fail: function(error)
            {
                console.log(error);
            }
        });
    });


    $(document).on('click',"#newroutebtn",function(e){
        e.preventDefault();

        var newroutename = $('#newroutebox').val();
        console.log($('#startlatbox').val().toString());
        var startlat = $('#startlatbox').val().split(',');
        var startlon = $('#startlonbox').val().split(',');

        var numPoints = startlat.length;
        alert(numPoints);
        console.log(startlat);

        if (startlat.length == 0)
        {
            startlat=null;
        }
        if (startlon.length == 0)
        {
            startlon=null;
        }

        $.ajax({
            type:'get',
            dataType: 'json',
            url: '/addroute',

            data:
            {
                filename: currentFileName,
                routename: newroutename,
                startlat: $('#startlatbox').val().toString(),
                startlon: $('#startlonbox').val().toString(),
                numPoints: numPoints
            },

            success: function (data)
            {
                console.log(data);
            },

            fail: function(error)
            {
                console.log(error);
            }
        });

    });

    //A4 Functions

    $(document).on('click','#loginbutton',function(e){
        e.preventDefault();

        var database = $('#databaseinput').val();
        var username = $('#usernameinput').val();
        var password = $('#passwordinput').val();

        $.ajax({
            type:'get',
            dataType: 'json',
            url: '/connecttodatabase',

            data:{
                host: 'dursley.socs.uoguelph.ca',
                user: username,
                db: database,
                pw: password
            },

            success: function(data)
            {
                if(data==true)
                {
                    alert("Successful login");
                }
                else
                {
                    alert("Failed login");
                }
            },

            fail: function(error)
            {
                alert(error);
            }
        });
    });

    $(document).on('click','#deletetables',function(e){
        e.preventDefault();
        $.ajax({
            type:'get',
            dataType: 'json',
            url: '/deletetables',

            success: function(data)
            {
                if (data==true)
                {
                    alert(`Successfully deleted tables`);
                }
                else
                {
                    alert(`Failed to delete tables`);
                }
            },

            fail: function(error)
            {

            }
        });
    });

    $(document).on('click','#displaytables',function(e){
        e.preventDefault();
        $.ajax({
            type:'get',
            dataType: 'json',
            url: '/displaytables',

            success: function(data)
            {
                if (data!=false)
                {
                    alert(`Database has ${data.numfiles} files, ${data.numroutes} routes, and ${data.numpoints} points.`);
                }
                else
                {
                    alert(`Failed to display database`);
                }
            },

            fail: function(error)
            {

            }
        });
    });
    

});
