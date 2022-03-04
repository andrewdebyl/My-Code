#ifndef GPX_HELPER
#define GPX_HELPER

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
#include <stdbool.h>

GPXData* createGPXdata (char* name, char* value);
Waypoint* createWaypoint (char* name, double longitude, double latitude);
Route* createRoute (char* name);
TrackSegment* createTrackSegment (void);
Track* createTrack (char *name);
Waypoint* parseWaypoint(xmlNode *node);
Route* parseRoute(xmlNode* node);
TrackSegment* parseTrackSegment (xmlNode* node);
Track* parseTrack (xmlNode* node);
bool isWaypoint (void* node);
char* getName (xmlNode* node);
bool isText (xmlNode* node);
bool isName (xmlNode* node);
xmlNode* GPXDataToNode (GPXData* ptr, xmlNs* namespace);
xmlNode* GPXNameToNode(char *name, xmlNs* namespace);
xmlNode* WaypointToNode (Waypoint* ptr, char* type, xmlNs* namespace);
xmlNode* TrackSegmentToNode (TrackSegment* trk, xmlNs* namespace);
xmlNode* RouteToNode (Route* rte, xmlNs* namespace);
xmlNode* TrackToNode (Track* trk, xmlNs* namespace);
xmlNode* GPXDocToNode (GPXdoc* gpx);
float getDistanceWaypoints(List* waypoints);
float getDistancePoints (Waypoint* head, Waypoint* tail);
TrackSegment* getSegWaypoints (List* segments, bool forwards);
void dummyDelete (void* data);
char* GPXdataToJSON (void* data);
char* waypointToJSON (void* data);
char* listToJSON (List* data, char*(*dataToJSON)(void*));
char* trackSegToJSON (void* data);
char* trim (char* arg);
bool validateGPXdata (GPXData* gpx);
bool validateWaypoint (Waypoint* wpt);
bool validateRoute (Route* rt);
bool validateTrackSeg (TrackSegment* seg);
bool validateTrack (Track* trk);
bool validateGPXdoc (GPXdoc* gpx);
char* routeToJSON2 (void* data);
char *trackToJSON2(void* data);
char* copyString (char* og, int start, int end);
int getIndex (char* s, char c);
char* waypointListToJSON (List* data);
char* GPXfileToJSON (char* filename);
char* fileAndDocToJSON (char* filename, GPXdoc* doc);
bool validateGPXFile (char* filename, char* scemaFile);
int getNumPointsFromTrack (Track* trk);
char* fileDetailsToJSON (char* filename);
char* routeComponentToJSON (int comNum, Route* rt);
char* trackComponentToJSON (int comNum, Track* rt);
bool changeComponentName (char* filename, char* newName, char* oldname);
bool addNewRoute (char* filename, char* routeName, char* startlat, char* startlon, int count);
float* stringToFloats (char* string);
char* routesToJSON (char* filename);
char* waypointToJSON2 (Waypoint* wpt, int index);
char* listWaypointstoJSON (char* filename, char* routename);







#endif

