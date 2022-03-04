#include <stdio.h>
#include <string.h>
#include <math.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"
#include "GPXParser.h"
#include "GPXHelpers.h"
#include <ctype.h>
#include <stdbool.h>

GPXData *createGPXdata(char *name, char *value)
{
    if (name == NULL || value == NULL)
    {
        return NULL;
    }

    if (strlen(name) == 0 || strlen(value) == 0)
    {
        return NULL;
    }

    GPXData *gpxPtr = calloc(1, sizeof(GPXData) + (strlen(value) * sizeof(char)) + 10);

    strcpy(gpxPtr->name, name);
    strcpy(gpxPtr->value, value);

    return gpxPtr;
}

Waypoint *createWaypoint(char *name, double longitude, double latitude)
{
    char *newName = calloc(100, 1);

    if (name == NULL)
    {
    }
    else
    {
        strcpy(newName, name);
    }

    Waypoint *gpxPtr = calloc(1, sizeof(Waypoint));
    gpxPtr->name = calloc(100, sizeof(char));

    strcpy(gpxPtr->name, newName);
    free(newName);
    gpxPtr->longitude = longitude;
    gpxPtr->latitude = latitude;

    gpxPtr->otherData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);

    return gpxPtr;
}
Route *createRoute(char *name)
{
    char *newName = calloc(100, 1);

    if (name == NULL)
    {
    }
    else
    {
        strcpy(newName, name);
    }

    Route *gpxPtr = calloc(1, sizeof(Route));
    gpxPtr->name = calloc(100, sizeof(char));

    strcpy(gpxPtr->name, newName);
    free(newName);

    gpxPtr->otherData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    gpxPtr->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);

    return gpxPtr;
}

TrackSegment *createTrackSegment(void)
{
    TrackSegment *gpxPtr = calloc(1, sizeof(TrackSegment));

    gpxPtr->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);

    return gpxPtr;
}

Track *createTrack(char *name)
{
    char *newName = calloc(100, 1);

    if (name == NULL)
    {
    }
    else
    {
        strcpy(newName, name);
    }

    Track *gpxPtr = calloc(1, sizeof(Track));
    gpxPtr->name = calloc(100, sizeof(char));

    strcpy(gpxPtr->name, newName);
    free(newName);

    gpxPtr->otherData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    gpxPtr->segments = initializeList(&trackSegmentToString, &deleteTrackSegment, &compareTrackSegments);

    return gpxPtr;
}

char *getName(xmlNode *node)
{
    char *name = NULL;

    for (xmlNode *child = node->children; child != NULL; child = child->next)
    {
        char *temp = (char *)child->name;

        if (strcmp(temp, "name") == 0)
        {
            name = (char *)child->children->content;
            return trim(name);
        }
    }
    return NULL;
}

Waypoint *parseWaypoint(xmlNode *node)
{
    char *name = getName(node);
    double lat = 0.0;
    double lon = 0.0;

    xmlAttr *attr = NULL;

    for (attr = node->properties; attr != NULL; attr = attr->next)
    {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;

        if (strcmp(attrName, "lat") == 0)
        {
            lat = atof((char *)value->content);
        }
        if (strcmp(attrName, "lon") == 0)
        {
            lon = atof((char *)value->content);
        }
    }

    Waypoint *ptr = createWaypoint(name, lon, lat);
    free(name);

    if (ptr == NULL)
    {
        return NULL;
    }

    for (xmlNode *child = node->children; child != NULL; child = child->next)
    {
        if (isText(child))
        {
            continue;
        }

        if (isName(child))
        {
            continue;
        }

        GPXData *gpxTemp = createGPXdata((char *)child->name, (char *)child->children->content);

        if (gpxTemp == NULL)
        {
            deleteWaypoint(ptr);
            return NULL;
        }

        insertBack(ptr->otherData, gpxTemp);
    }

    return ptr;
}

Route *parseRoute(xmlNode *node)
{
    char* name = getName(node);
    Route *route = createRoute(name);
    free(name);

    if (route == NULL)
    {
        return NULL;
    }

    for (xmlNode *child = node->children; child != NULL; child = child->next)
    {
        if (isText(child))
        {
            continue;
        }
        if (isName(child))
        {
            continue;
        }

        if (isWaypoint(child) == true)
        {
            Waypoint *ptr = parseWaypoint(child);

            if (ptr == NULL)
            {
                deleteRoute(route);
                return NULL;
            }
            else
            {
                insertBack(route->waypoints, ptr);
            }
        }
        else
        {
            GPXData *ptr = createGPXdata((char *)child->name, (char *)child->children->content);

            if (ptr == NULL)
            {
                deleteRoute(route);
                return NULL;
            }
            else
            {
                insertBack(route->otherData, ptr);
            }
        }
    }
    return route;
}

TrackSegment *parseTrackSegment(xmlNode *node)
{

    TrackSegment *trk = createTrackSegment();

    for (xmlNode *child = node->children; child != NULL; child = child->next)
    {
        if (isText(child))
        {
            continue;
        }
        if (isName(child))
        {
            continue;
        }

        if (isWaypoint(child) == false)
        {
            deleteTrackSegment(trk);
            return NULL;
        }
        else
        {
            Waypoint *ptr = parseWaypoint(child);

            if (ptr == NULL)
            {
                deleteTrackSegment(trk);
                return NULL;
            }
            else
            {
                insertBack(trk->waypoints, ptr);
            }
        }
    }

    return trk;
}

Track *parseTrack(xmlNode *node)
{
    char* name = getName(node);
    Track *trk = createTrack(name);
    free(name);

    if (trk == NULL)
    {
        return NULL;
    }

    for (xmlNode *child = node->children; child != NULL; child = child->next)
    {
        if (isText(child))
        {
            continue;
        }
        if (isName(child))
        {
            continue;
        }

        if (strcmp((char *)child->name, "trkseg") == 0)
        {
            TrackSegment *seg = parseTrackSegment(child);

            if (seg == NULL)
            {
                deleteTrack(trk);
                return NULL;
            }
            else
            {
                insertBack(trk->segments, seg);
            }
        }
        else
        {
            GPXData *ptr = createGPXdata((char *)child->name, (char *)child->children->content);

            if (ptr == NULL)
            {
                deleteTrack(ptr);
                return NULL;
            }
            else
            {
                insertBack(trk->otherData, ptr);
            }
        }
    }

    return trk;
}

bool isWaypoint(void *node)
{
    xmlNode *temp = (xmlNode *)node;

    if (strcmp((char *)temp->name, "wpt") == 0)
    {
        return true;
    }
    if (strcmp((char *)temp->name, "rtept") == 0)
    {
        return true;
    }
    if (strcmp((char *)temp->name, "trkpt") == 0)
    {
        return true;
    }

    return false;
}

bool isText(xmlNode *node)
{
    char *temp = (char *)node->name;

    if (strcmp(temp, "text") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isName(xmlNode *node)
{
    char *temp = (char *)node->name;

    if (strcmp(temp, "name") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/************** HELPER FUNCTIONS FOR A2 *****************/

xmlNode *GPXDataToNode(GPXData *ptr, xmlNs *namespace)
{
    xmlNode *node = xmlNewNode(NULL, BAD_CAST ptr->name);

    xmlSetNs(node, namespace);

    xmlNode *node1 = xmlNewText(BAD_CAST ptr->value);
    xmlAddChild(node, node1);

    return node;
}

xmlNode *GPXNameToNode(char *name, xmlNs *namespace)
{
    if (strcmp(name, "") == 0)
    {
        return NULL;
    }
    else
    {
        xmlNode *node = xmlNewNode(NULL, BAD_CAST "name");

        xmlSetNs(node, namespace);

        xmlNode *node1 = xmlNewText(BAD_CAST name);
        xmlAddChild(node, node1);

        return node;
    }
}

xmlNode *WaypointToNode(Waypoint *ptr, char *type, xmlNs *namespace)
{
    xmlNode *node = xmlNewNode(NULL, BAD_CAST type);
    char *temp = calloc(100, sizeof(char));

    xmlSetNs(node, namespace);

    sprintf(temp, "%.5f", ptr->latitude);
    xmlNewProp(node, BAD_CAST "lat", BAD_CAST temp);

    sprintf(temp, "%.5f", ptr->longitude);
    xmlNewProp(node, BAD_CAST "lon", BAD_CAST temp);

    free(temp);

    for (Node *temp = ptr->otherData->head; temp != NULL; temp = temp->next)
    {
        xmlNode *p = GPXDataToNode(temp->data, namespace);

        xmlAddChild(node, p);
    }

    xmlNode *nameNode = GPXNameToNode(ptr->name, namespace);

    if (nameNode != NULL)
    {
        xmlAddChild(node, nameNode);
    }
    else
    {
        xmlNode *node1 = xmlNewText(NULL);
        xmlAddChild(node, node1);
    }

    return node;
}

xmlNode *TrackSegmentToNode(TrackSegment *trk, xmlNs *namespace)
{
    xmlNode *node = xmlNewNode(NULL, BAD_CAST "trkseg");

    xmlSetNs(node, namespace);

    for (Node *temp = trk->waypoints->head; temp != NULL; temp = temp->next)
    {
        xmlNode *p = WaypointToNode(temp->data, "trkpt", namespace);

        xmlAddChild(node, p);
    }

    return node;
}

xmlNode *RouteToNode(Route *rte, xmlNs *namespace)
{
    xmlNode *node = xmlNewNode(NULL, BAD_CAST "rte");

    xmlSetNs(node, namespace);

    xmlNode *nameNode = GPXNameToNode(rte->name, namespace);

    if (nameNode != NULL)
    {
        xmlAddChild(node, nameNode);
    }
    else
    {
        xmlNode *node1 = xmlNewText(NULL);
        xmlAddChild(node, node1);
    }

    for (Node *temp = rte->otherData->head; temp != NULL; temp = temp->next)
    {
        xmlNode *p = GPXDataToNode(temp->data, namespace);

        xmlAddChild(node, p);
    }

    for (Node *temp = rte->waypoints->head; temp != NULL; temp = temp->next)
    {
        xmlNode *p = WaypointToNode(temp->data, "rtept", namespace);

        xmlAddChild(node, p);
    }

    return node;
}

xmlNode *TrackToNode(Track *trk, xmlNs *namespace)
{
    xmlNode *node = xmlNewNode(NULL, BAD_CAST "trk");

    xmlSetNs(node, namespace);

    xmlNode *nameNode = GPXNameToNode(trk->name, namespace);

    if (nameNode != NULL)
    {
        xmlAddChild(node, nameNode);
    }
    else
    {
        xmlNode *node1 = xmlNewText(NULL);
        xmlAddChild(node, node1);
    }

    for (Node *temp = trk->otherData->head; temp != NULL; temp = temp->next)
    {
        xmlNode *p = GPXDataToNode(temp->data, namespace);

        xmlAddChild(node, p);
    }

    for (Node *temp = trk->segments->head; temp != NULL; temp = temp->next)
    {
        xmlNode *p = TrackSegmentToNode(temp->data, namespace);

        xmlAddChild(node, p);
    }

    return node;
}

xmlNode *GPXDocToNode(GPXdoc *gpx)
{
    xmlNode *node = xmlNewNode(NULL, BAD_CAST "gpx");
    xmlNs *nameSpace = xmlNewNs(node, BAD_CAST gpx->namespace, NULL);
    xmlSetNs(node, nameSpace);

    char *temp = calloc(100, sizeof(char));

    sprintf(temp, "%.1f", gpx->version);
    xmlNewProp(node, BAD_CAST "version", BAD_CAST temp);

    free(temp);

    xmlNewProp(node, BAD_CAST "creator", BAD_CAST gpx->creator);

    for (Node *temp = gpx->waypoints->head; temp != NULL; temp = temp->next)
    {
        xmlNode *wpt = WaypointToNode(temp->data, "wpt", nameSpace);
        xmlAddChild(node, wpt);
    }

    for (Node *temp = gpx->routes->head; temp != NULL; temp = temp->next)
    {
        xmlNode *rte = RouteToNode(temp->data, nameSpace);
        xmlAddChild(node, rte);
    }

    for (Node *temp = gpx->tracks->head; temp != NULL; temp = temp->next)
    {
        xmlNode *trk = TrackToNode(temp->data, nameSpace);
        xmlAddChild(node, trk);
    }

    return node;
}

float getDistanceWaypoints(List *waypoints)
{
    float total = 0.0;

    if (waypoints == NULL)
    {
        return total;
    }

    if (getLength(waypoints) <= 1)
    {
        return total;
    }

    for (Node *temp2 = waypoints->head; temp2->next != NULL; temp2 = temp2->next)
    {
        Waypoint *wpt1 = temp2->data;
        Node *temp3 = temp2->next;
        Waypoint *wpt2 = temp3->data;

        total+=getDistancePoints(wpt1,wpt2);
    }
    return total;
}

float getDistancePoints(Waypoint *head, Waypoint *tail)
{
    Waypoint *wpt1 = head;
    Waypoint *wpt2 = tail;

    float R = 6371000;

    float total=0.0;

    float lat1 = wpt1->latitude;
    float lat2 = wpt2->latitude;
    float lon1 = wpt1->longitude;
    float lon2 = wpt2->longitude;

    float phi1 = lat1 * M_PI / 180;
    float phi2 = lat2 * M_PI / 180;
    float changePhi = (lat2 - lat1) * M_PI / 180;
    float changeAlpha = (lon2 - lon1) * M_PI / 180;

    float a = sin(changePhi / 2) * sin(changePhi / 2) + cos(phi1) * cos(phi2) * sin(changeAlpha / 2) * sin(changeAlpha / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    float d = R * c;

    total = d + total;

    return total;
}

TrackSegment* getSegWaypoints (List* segments, bool forwards)
{
    if (forwards == true)
    {
        for (Node* temp = segments->head; temp!=NULL; temp=temp->next)
        {
            TrackSegment* temp2 = temp->data;

            if (getLength(temp2->waypoints) > 0)
            {
                return temp2;
            }
        }
    }
    else
    {
        for (Node* temp = segments->tail; temp!=NULL; temp=temp->previous)
        {
            TrackSegment* temp2 = temp->data;

            if (getLength(temp2->waypoints) > 0)
            {
                return temp2;
            }
        }
    }
    return NULL;
}

void dummyDelete (void* data)
{
    return;
}

char* GPXdataToJSON (void* data)
{
    if (data == NULL)
    {
        char* s = calloc(20,sizeof(char));
        strcpy(s, "{}");
        return s;
    }

    GPXData* gpx = data;

    int memSize= 0;

    memSize+=strlen(gpx->name);
    memSize+=strlen(gpx->value) + 200;

    char* json = calloc(memSize, sizeof(char));

    strcat(json, "{");
    strcat(json, "\"name\"");
    strcat(json, ":");
    strcat(json, "\"");
    strcat(json, gpx->name);
    strcat(json, "\"");
    strcat(json, ",");

    strcat(json, "\"value\"");
    strcat(json, ":");
    strcat(json, "\"");
    strcat(json, gpx->value);
    strcat(json, "\"");
    strcat(json, "}");

    return json;
}

char* listToJSON (List* data, char*(*dataToJSON)(void*))
{
    if (data == NULL)
    {
        char* temp = calloc(20, sizeof(char));
        strcpy(temp,"[]");
        return temp;
    }
    if (getLength(data)==0)
    {
        char* temp = calloc(20, sizeof(char));
        strcpy(temp,"[]");
        return temp;
    }

    char* s = calloc(100, sizeof(char));

    strcat(s, "[");

    int memSize = 100;

    for (Node* node = data->head; node!=NULL; node = node->next)
    {
        char* temp = dataToJSON(node->data);
        memSize+=strlen(temp)+10;

        s=realloc(s, memSize*sizeof(char));

        strcat(s, temp);
        free(temp);

        if (node->next != NULL)
        {
            strcat(s, ",");
        }
    }

    strcat(s, "]");

    return s;
}

char* waypointListToJSON (List* data)
{
    return listToJSON(data, &waypointToJSON);
}

char* waypointToJSON (void* data)
{
    if (data == NULL)
    {
        char* s = calloc(20,sizeof(char));
        strcpy(s, "{}");
        return s;
    }

    Waypoint* wpt = data;

    int memSize=0;

    memSize+=strlen("lat") + strlen("lon") + 500;

    char* json = calloc(memSize, sizeof(char));

    sprintf(json, "{\"lat\":%.6f,\"lon\":%.6f}", wpt->latitude, wpt->longitude);

    return json;
}

char* trackSegToJSON (void* data)
{
    if (data ==NULL)
    {
        char* s = calloc(20,sizeof(char));
        strcpy(s, "{}");
        return s;
    }

    TrackSegment* trk = data;

    int memSize=0;

    char* waypointJSON = listToJSON(trk->waypoints, &waypointToJSON);

    memSize+=strlen(waypointJSON)+100;

    char* json = calloc(memSize, sizeof(char));

    sprintf(json, "{\"waypoints\":%s}",waypointJSON);

    free(waypointJSON);

    return json;
}

char* routeToJSON2 (void* data)
{
    Route* rt= data;

    if(rt == NULL)
    {
        char* temp = calloc(20, sizeof(char));
        strcpy(temp,"{}");
        return temp;
    }

    char* tempName = calloc(256,sizeof(char));
    if (strlen(rt->name) ==0)
    {
        strcpy(tempName,"None");
    }
    else
    {
        strcpy(tempName, rt->name);
    }

    int memSize = 0;

    memSize+=1000;

    char* json = calloc(memSize, sizeof(char));

    char* isLoop = calloc(20, sizeof(char));

    if (isLoopRoute(rt, 10))
    {
        strcpy(isLoop, "true");
    }
    else
    {
        strcpy(isLoop, "false");

    }

    sprintf(json,"{\"name\":\"%s\",\"numPoints\":%d,\"len\":%.1f,\"loop\":%s}", tempName, getLength(rt->waypoints), round10(getRouteLen(rt)), isLoop);

    free(isLoop);
    free(tempName);

    return json;
}

char *trackToJSON2(void* data)
{
    Track* tr = data;
    if(tr == NULL)
    {
        char* temp = calloc(20, sizeof(char));
        strcpy(temp,"{}");
        return temp;
    }

    char* tempName = calloc(256, sizeof(char));
    if (strlen(tr->name) ==0)
    {
        strcpy(tempName,"None");
    }
    else
    {
        strcpy(tempName, tr->name);
    }

    int memSize = 1000;

    char* json = calloc(memSize, sizeof(char));
    
    char* isLoop = calloc(20, sizeof(char));

    if (isLoopTrack(tr, 10))
    {
        strcpy(isLoop, "true");
    }
    else
    {
        strcpy(isLoop, "false");
    }

    sprintf(json,"{\"name\":\"%s\",\"len\":%.1f,\"loop\":%s}", tempName, round10(getTrackLen(tr)), isLoop);

    free(isLoop);
    free(tempName);

    return json;
}


char* trim (char* arg)
{
    int i=0, j=0, k=0, l;
    char* temp = calloc(strlen(arg) +10, sizeof(char));

    while(isspace(arg[i])!=0)
    {
        i++;
    }

    j=strlen(arg)-1;

    while(isspace(arg[j])!=0)
    {
        j--;
    }
    for(l=i; l <= j; l++)
    {
        temp[k] = arg[l];
        k++;
    }

    return temp;
}

bool validateGPXdata (GPXData* gpx)
{
    if (gpx==NULL)
    {
        return false;
    }

    if (strcmp(gpx->name, "") == 0 || strcmp(gpx->value, "")==0 || strcmp(gpx->name, "name")==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool validateWaypoint (Waypoint* wpt)
{
    if (wpt ==NULL)
    {
        return false;
    }

    if (wpt->name == NULL)
    {
        return false;
    }

    if (wpt->otherData == NULL)
    {
        return false;
    }

    for(Node* temp = wpt->otherData->head; temp!=NULL; temp=temp->next)
    {
        if (validateGPXdata(temp->data) == false)
        {
            return false;
        }
    }

    return true;
}

bool validateRoute (Route* rt)
{
    if (rt == NULL)
    {
        return false;
    }

    if (rt->name == NULL)
    {
        return false;
    }

    if (rt->otherData == NULL || rt->waypoints==NULL)
    {
        return false;
    }

    for(Node* temp = rt->waypoints->head; temp!=NULL; temp=temp->next)
    {
        if (validateWaypoint(temp->data) == false)
        {
            return false;
        }
    }

    for(Node* temp = rt->otherData->head; temp!=NULL; temp=temp->next)
    {
        if (validateGPXdata(temp->data) == false)
        {
            return false;
        }
    }

    return true;
}

bool validateTrackSeg (TrackSegment* seg)
{
    if (seg == NULL)
    {
        return false;
    }

    if (seg->waypoints == NULL)
    {
        return false;
    }

    for(Node* temp = seg->waypoints->head; temp!=NULL; temp=temp->next)
    {
        if (validateWaypoint(temp->data) == false)
        {
            return false;
        }
    }

    return true;
}

bool validateTrack (Track* trk)
{
    if (trk == NULL)
    {
        return false;
    }

    if (trk->name==NULL || trk->otherData == NULL || trk->segments == NULL)
    {
        return false;
    }

    for(Node* temp = trk->segments->head; temp!=NULL; temp=temp->next)
    {
        if (validateTrackSeg(temp->data) == false)
        {
            return false;
        }
    }

    for(Node* temp = trk->otherData->head; temp!=NULL; temp=temp->next)
    {
        if (validateGPXdata(temp->data) == false)
        {
            return false;
        }

    }

    return true;
}

bool validateGPXdoc (GPXdoc* gpx)
{
    if (gpx == NULL)
    {
        return false;
    }

    if (strcmp(gpx->namespace, "")==0)
    {
        return false;
    }

    if (gpx->creator == NULL)
    {
        return false;
    }

    if (strcmp(gpx->creator,"")==0)
    {
        return false;
    }

    if (gpx->waypoints == NULL || gpx->tracks == NULL || gpx->routes == NULL)
    {
        return false;
    }

    for(Node* temp = gpx->waypoints->head; temp!=NULL; temp=temp->next)
    {
        if (validateWaypoint(temp->data) == false)
        {
            return false;
        }
    }

    for(Node* temp = gpx->tracks->head; temp!=NULL; temp=temp->next)
    {
        if (validateTrack(temp->data) == false)
        {
            return false;
        }
    }

    for(Node* temp = gpx->routes->head; temp!=NULL; temp=temp->next)
    {
        if (validateRoute(temp->data) == false)
        {
            return false;
        }
    }

    return true;
}

char* copyString (char* og, int start, int end)
{
    if (og == NULL)
    {
        return NULL;
    }
    if (end <= start)
    {
        return NULL;
    }

    char* copy = calloc(strlen(og), sizeof(char));

    int i;
    for (i=start; i<end; i++)
    {
        copy[i-start] = og[i];
    }

    return copy;
}

int getIndex (char* s, char c)
{
    if (s==NULL)
    {
        return -1;
    }
    if (strlen(s)==0)
    {
        return -1;
    }

    int i;

    for(i=0; i < strlen(s); i++)
    {
        if (s[i] == c)
        {
            return i;
        }
    }

    return -1;
}

char* GPXfileToJSON (char* filename)
{
    GPXdoc* doc = createGPXdoc(filename);

    char* json = fileAndDocToJSON(filename, doc);

    deleteGPXdoc(doc);

    return json;
}

char* fileAndDocToJSON (char* filename, GPXdoc* doc)
{
    if(doc == NULL || filename == NULL)
    {
        char* temp = calloc(20, sizeof(char));
        strcpy(temp,"{}");
        return temp;
    }

    char* json = calloc(2000,sizeof(char));

    sprintf(json,"{\"fileName\":\"%s\",\"version\":%.1f,\"creator\":\"%s\",\"numWaypoints\":%d,\"numRoutes\":%d,\"numTracks\":%d}",filename, doc->version, doc->creator, getNumWaypoints(doc), getNumRoutes(doc), getNumTracks(doc));

    return json;
}

bool validateGPXFile (char* filename, char* scemaFile)
{
    GPXdoc* ptr = createValidGPXdoc(filename,scemaFile);

    if (ptr==NULL)
    {
        return false;
    }

    return validateGPXDoc(ptr, scemaFile);
}

char* fileDetailsToJSON (char* filename)
{
    GPXdoc* ptr = createGPXdoc(filename);

    if(ptr==NULL)
    {
        return "[]";
    }

    int memSize=100;
    int count=1;
    char* json = calloc(memSize,sizeof(char));

    strcat(json, "[");
    if (getLength(ptr->routes) >0 && getLength(ptr->tracks)>0)
    {
        for (Node* temp = ptr->routes->head; temp!=NULL; temp=temp->next)
        {
            char* temp1 = routeComponentToJSON(count, temp->data);
            memSize+=strlen(temp1)+4;
            json=realloc(json, memSize*sizeof(char));
            strcat(json, temp1);
            strcat(json,",");
            count++;
        }
        count=1;

        for (Node* temp = ptr->tracks->head; temp!=NULL; temp=temp->next)
        {
            char* temp1 = trackComponentToJSON(count, temp->data);
            memSize+=strlen(temp1)+4;
            json=realloc(json, memSize*sizeof(char));
            strcat(json, temp1);
            if (temp->next!=NULL)
            {
                strcat(json,",");
            }
            count++;
        }

        strcat(json,"]");
        return json;
    }
    else if(getLength(ptr->routes) >0 )
    {
        for (Node* temp = ptr->routes->head; temp!=NULL; temp=temp->next)
        {
            char* temp1 = routeComponentToJSON(count, temp->data);
            memSize+=strlen(temp1)+4;
            json=realloc(json, memSize*sizeof(char));
            strcat(json, temp1);
            if (temp->next!=NULL)
            {
                strcat(json,",");
            }
            count++;
        }
        strcat(json,"]");
        return json;
    }
    else{
        for (Node* temp = ptr->tracks->head; temp!=NULL; temp=temp->next)
        {
            char* temp1 = trackComponentToJSON(count, temp->data);
            memSize+=strlen(temp1)+4;
            json=realloc(json, memSize*sizeof(char));
            strcat(json, temp1);
            if (temp->next!=NULL)
            {
                strcat(json,",");
            }
            count++;
        }
        strcat(json,"]");
        return json;
    }
}

int getNumPointsFromTrack (Track* trk)
{
    if (trk==NULL)
    {
        return 0;
    }

    int sum=0;

    for (Node* temp = trk->segments->head; temp!=NULL; temp=temp->next)
    {
        TrackSegment* seg = temp->data;
        sum+=getLength(seg->waypoints);
    }
    return sum;
}

char* routeComponentToJSON (int comNum, Route* rt)
{
    if (rt==NULL)
    {
        return "{}";
    }

    char* tempName = calloc(256,sizeof(char));
    if (strlen(rt->name) ==0)
    {
        strcpy(tempName,"None");
    }
    else
    {
        strcpy(tempName, rt->name);
    }

    int memSize = 0;

    memSize+=1000;

    char* json = calloc(memSize, sizeof(char));

    char* isLoop = calloc(20, sizeof(char));

    if (isLoopRoute(rt, 10))
    {
        strcpy(isLoop, "true");
    }
    else
    {
        strcpy(isLoop, "false");

    }

    char component[256];

    sprintf(component, "Route %d",comNum);

    sprintf(json,"{\"component\":\"%s\",\"name\":\"%s\",\"numPoints\":%d,\"len\":%.1f,\"loop\":%s}", component, tempName, getLength(rt->waypoints), round10(getRouteLen(rt)), isLoop);

    free(isLoop);
    free(tempName);

    return json;
}

char* trackComponentToJSON (int comNum, Track* rt)
{
    if (rt==NULL)
    {
        return "{}";
    }

    char* tempName = calloc(256,sizeof(char));
    if (strlen(rt->name) ==0)
    {
        strcpy(tempName,"None");
    }
    else
    {
        strcpy(tempName, rt->name);
    }

    int memSize = 0;

    memSize+=1000;

    char* json = calloc(memSize, sizeof(char));

    char* isLoop = calloc(20, sizeof(char));

    if (isLoopTrack(rt, 10))
    {
        strcpy(isLoop, "true");
    }
    else
    {
        strcpy(isLoop, "false");
    }

    char component[256];

    sprintf(component, "Track %d",comNum);

    sprintf(json,"{\"component\":\"%s\",\"name\":\"%s\",\"numPoints\":%d,\"len\":%.1f,\"loop\":%s}", component, tempName, getNumPointsFromTrack(rt), round10(getTrackLen(rt)), isLoop);

    free(isLoop);
    free(tempName);

    return json;
}

bool changeComponentName (char* filename, char* newName, char* oldname)
{
    if (filename==NULL || newName == NULL)
    {
        return false;
    }

    GPXdoc* ptr = createGPXdoc(filename);
    Route* rt = getRoute(ptr, oldname);
    Track* trk = getTrack(ptr,oldname);

    if (rt!=NULL)
    {
        strcpy(rt->name,newName);
        return writeGPXdoc(ptr, filename);
    }
    else if(trk!=NULL)
    {
        strcpy(trk->name,newName);
        return writeGPXdoc(ptr,filename);
    }
    else{
        return false;
    }
}

bool addNewRoute (char* filename, char* routeName, char* lat, char* lon, int count)
{
    if (filename==NULL || routeName==NULL)
    {
        return false;
    }

    GPXdoc* ptr = createGPXdoc(filename);
    Route* rt = createRoute(routeName);

    if (lat!=NULL && lon!=NULL)
    {
        float* latitude = stringToFloats(lat);
        float* longitude = stringToFloats(lon);

        for (int i=0;i<count;i++)
        {
            Waypoint* wp=createWaypoint("",longitude[i],latitude[i]);
                    printf("%.2f %.2f\n",latitude[i], longitude[i]);

            addWaypoint(rt,wp);
        }

        addRoute(ptr,rt);
        writeGPXdoc(ptr,filename);

        return true;
    }
    else if(lat==NULL && lon!=NULL)
    {
        return false;
    }
    else if(lat!=NULL && lon==NULL)
    {
        return false;
    }
    else{
        addRoute(ptr,rt);
        writeGPXdoc(ptr,filename);
        return true;
    }
}

float* stringToFloats (char* string)
{
    char* token = strtok(string,", ");
    float* ptr=calloc(strlen(string),sizeof(float));
    int count=0;

    while(token!=NULL)
    {
        ptr[count] = atof(token);
        token=strtok(NULL,", ");
        count++;
    }

    return ptr;
}

char* routesToJSON (char* filename)
{
    GPXdoc* ptr = createGPXdoc(filename);
   
    char* routes = listToJSON(ptr->routes, routeToJSON2);

    return routes;
}

char* waypointToJSON2 (Waypoint* wpt, int index)
{
    char* json = calloc(1000, sizeof(char));

    if (wpt ==NULL || index <0)
    {
        strcpy(json, "{}");
        return json;
    }

    char* name = calloc(256, sizeof(char));

    if (strlen(wpt->name)==0)
    {
        strcpy(name, "null");
    }
    else
    {
        strcpy(name, wpt->name);
    }

    sprintf(json, "{\"ptindex\":%d,\"name\":\"%s\",\"lat\":%.7f,\"lon\":%.7f}", index, name, wpt->latitude, wpt->longitude);

    free(name);
    return json;
}

char* listWaypointstoJSON (char* filename, char* routename)
{
    if (filename == NULL || routename==NULL)
    {
        char* json = calloc(1000, sizeof(char));
        strcpy(json, "[]");
        return json;
    }

    GPXdoc* ptr = createGPXdoc(filename);
    Route* route = getRoute(ptr,routename);

    if (route == NULL)
    {
        char* json = calloc(1000, sizeof(char));
        strcpy(json, "[]");
        return json;
    }

    int memSize = 100;

    char* json = calloc(memSize, sizeof(char));

    strcpy(json, "[");

    int index=0;

    for (Node* temp = route->waypoints->head; temp!=NULL; temp=temp->next)
    {
        char* s = waypointToJSON2(temp->data, index);
        memSize+=strlen(s)+5;

        json =realloc(json, memSize*sizeof(char));

        strcat(json, s);
        free(s);
        if (temp->next!=NULL)
        {
            strcat(json, ",");
        }
    }

    strcat(json, "]");
    return json;
}