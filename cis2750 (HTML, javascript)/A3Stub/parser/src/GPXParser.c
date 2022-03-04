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

void deleteGpxData(void *data)
{
    if (data == NULL)
    {
        return;
    }

    GPXData *temp = (GPXData *)data;

    free(temp);
}

char *gpxDataToString(void *data)
{
    if (data == NULL)
    {
        return NULL;
    }

    GPXData *temp = (GPXData *)data;

    char *content = calloc(256 + strlen(temp->value) + 50, sizeof(char));

    strcpy(content, "\nData\n");
    strcat(content, temp->name);
    strcat(content, "\n");
    strcat(content, temp->value);
    strcat(content, "\n");

    return content;
}

int compareGpxData(const void *first, const void *second)
{
    return -1;
}

void deleteWaypoint(void *data)
{
    if (data == NULL)
    {
        return;
    }

    Waypoint *temp = (Waypoint *)data;

    free(temp->name);
    freeList(temp->otherData);
    free(temp);
}

char *waypointToString(void *data)
{
    if (data == NULL)
    {
        return NULL;
    }

    Waypoint *temp = (Waypoint *)data;

    char s[50] = "";

    char *tempList = toString(temp->otherData);
    char *content = calloc(strlen(tempList) + 100, sizeof(char));

    strcpy(content, "\nWaypoint\n");
    strcat(content, temp->name);
    strcat(content, "\n");

    sprintf(s, "%.2f", temp->latitude);
    strcat(content, s);

    strcat(content, "\n");

    sprintf(s, "%.2f", temp->longitude);
    strcat(content, s);

    strcat(content, tempList);
    strcat(content, "\n");

    free(tempList);

    return content;
}

int compareWaypoints(const void *first, const void *second)
{
    return -1;
}

void deleteRoute(void *data)
{
    if (data == NULL)
    {
        return;
    }

    Route *temp = (Route *)data;

    free(temp->name);
    freeList(temp->waypoints);
    freeList(temp->otherData);
    free(temp);
}

char *routeToString(void *data)
{
    if (data == NULL)
    {
        return NULL;
    }

    Route *temp = (Route *)data;

    char *tempList = toString(temp->otherData);
    char *tempListW = toString(temp->waypoints);

    char *content = calloc(strlen(tempList) + strlen(tempListW) + 100, sizeof(char));

    strcpy(content, "\nRoute\n");
    strcat(content, temp->name);
    strcat(content, "\n");
    strcat(content, tempListW);
    strcat(content, "\n");
    strcat(content, tempList);
    strcat(content, "\n");

    free(tempList);
    free(tempListW);

    return content;
}

int compareRoutes(const void *first, const void *second)
{
    return -1;
}

void deleteTrackSegment(void *data)
{
    if (data == NULL)
    {
        return;
    }

    TrackSegment *temp = (TrackSegment *)data;

    freeList(temp->waypoints);
    free(temp);
}

char *trackSegmentToString(void *data)
{
    if (data == NULL)
    {
        return NULL;
    }

    TrackSegment *temp = (TrackSegment *)data;

    char *tempList = toString(temp->waypoints);
    char *content = calloc(strlen(tempList) + 100, sizeof(char));

    strcpy(content, "\nTrack Segment\n");
    strcat(content, tempList);
    strcat(content, "\n");

    free(tempList);

    return content;
}

int compareTrackSegments(const void *first, const void *second)
{
    return -1;
}

void deleteTrack(void *data)
{
    if (data == NULL)
    {
        return;
    }

    Track *temp = (Track *)data;

    free(temp->name);
    freeList(temp->segments);
    freeList(temp->otherData);
    free(temp);
}

char *trackToString(void *data)
{
    if (data == NULL)
    {
        return NULL;
    }

    Track *temp = (Track *)data;

    char *tempList = toString(temp->otherData);
    char *tempListS = toString(temp->segments);

    char *content = calloc(strlen(tempList) + strlen(tempListS) + 100, sizeof(char));

    strcpy(content, "\nTrack\n");
    strcat(content, temp->name);
    strcat(content, "\n");
    strcat(content, tempListS);
    strcat(content, "\n");
    strcat(content, tempList);
    strcat(content, "\n");

    free(tempList);
    free(tempListS);

    return content;
}

int compareTracks(const void *first, const void *second)
{
    return -1;
}

GPXdoc *createGPXdoc(char *fileName)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    LIBXML_TEST_VERSION

    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL)
    {
        return NULL;
    }

    root_element = xmlDocGetRootElement(doc);

    GPXdoc *ptr = calloc(1, sizeof(GPXdoc));

    ptr->creator = calloc(256, sizeof(char));
    strcpy(ptr->creator, "bob");
    strcpy(ptr->namespace, "NAMESPACEE");
    ptr->version = 1.1;
    if (root_element->ns != NULL)
    {
        if (root_element->ns->href != NULL)
        {
            strcpy(ptr->namespace, (char *)root_element->ns->href);
        }
    }
    ptr->routes = initializeList(&routeToString, &deleteRoute, &compareRoutes);
    ptr->waypoints = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    ptr->tracks = initializeList(&trackToString, &deleteTrack, &compareTracks);

    xmlAttr *attr = NULL;

    for (attr = root_element->properties; attr != NULL; attr = attr->next)
    {
        xmlNode *value = attr->children;
        char *attrName = (char *)attr->name;

        if (strcmp(attrName, "creator") == 0)
        {
            strcpy(ptr->creator, (char *)value->content);
        }
    }

    for (xmlNode *child = root_element->children; child != NULL; child = child->next)
    {
        char *name = (char *)child->name;

        if (isWaypoint(child) == true)
        {
            Waypoint *wPoint = parseWaypoint(child);

            if (wPoint == NULL)
            {
            }
            else
            {
                insertBack(ptr->waypoints, wPoint);
            }
        }

        if (strcmp(name, "rte") == 0)
        {
            Route *route = parseRoute(child);

            if (route == NULL)
            {
            }
            else
            {
                insertBack(ptr->routes, route);
            }
        }

        if (strcmp(name, "trk") == 0)
        {
            Track *trk = parseTrack(child);

            if (trk == NULL)
            {
                //printf("is NULL track\n");
            }
            else
            {
                insertBack(ptr->tracks, trk);
            }
        }
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();

    return ptr;
}

char *GPXdocToString(GPXdoc *doc)
{
    char *track = toString(doc->tracks);
    char *waypoint = toString(doc->waypoints);
    char *routes = toString(doc->routes);
    char *s = calloc(strlen(track) + strlen(waypoint) + strlen(routes) + 200, 1);

    char *temp = calloc(30, sizeof(char));
    sprintf(temp, "%.2f", doc->version);

    strcat(s, temp);
    free(temp);
    strcat(s, "\n");
    strcat(s, doc->namespace);
    strcat(s, "\n");
    strcat(s, doc->creator);
    strcat(s, "\n");
    strcat(s, track);
    strcat(s, waypoint);
    strcat(s, routes);

    free(track);
    free(waypoint);
    free(routes);

    return s;
}

void deleteGPXdoc(GPXdoc *doc)
{
    if (doc == NULL)
    {
        return;
    }

    free(doc->creator);
    freeList(doc->waypoints);
    freeList(doc->routes);
    freeList(doc->tracks);

    free(doc);
}

int getNumTracks(const GPXdoc *doc)
{
    if (doc == NULL)
    {
        return 0;
    }

    if (doc->tracks == NULL)
    {
        return 0;
    }

    return getLength(doc->tracks);
}

int getNumRoutes(const GPXdoc *doc)
{
    if (doc == NULL)
    {
        return 0;
    }

    if (doc->routes == NULL)
    {
        return 0;
    }

    return getLength(doc->routes);
}

int getNumSegments(const GPXdoc *doc)
{
    if (doc == NULL)
    {
        return 0;
    }

    if (doc->tracks == NULL)
    {
        return 0;
    }

    int count = 0;

    for (Node *temp = doc->tracks->head; temp != NULL; temp = temp->next)
    {
        Track *track = temp->data;

        if (track->segments == NULL)
        {
            count += 0;
        }
        else
        {
            count += getLength(track->segments);
        }
    }

    return count;
}

int getNumWaypoints(const GPXdoc *doc)
{
    if (doc == NULL)
    {
        return 0;
    }

    int count = 0;

    if (doc->waypoints != NULL)
    {
        count += getLength(doc->waypoints);
    }

    return count;
}

int getNumGPXData(const GPXdoc *doc)
{
    if (doc == NULL)
    {
        return 0;
    }

    int count = 0;

    if (doc->waypoints != NULL)
    {
        for (Node *temp = doc->waypoints->head; temp != NULL; temp = temp->next)
        {
            Waypoint *wpt = temp->data;

            if (strlen(wpt->name) > 0)
            {
                count++;
            }

            count += getLength(wpt->otherData);
        }
    }

    if (doc->tracks != NULL)
    {
        for (Node *temp = doc->tracks->head; temp != NULL; temp = temp->next)
        {
            Track *trk = temp->data;

            if (strlen(trk->name) > 0)
            {
                count++;
            }

            count += getLength(trk->otherData);

            for (Node *temp1 = trk->segments->head; temp1 != NULL; temp1 = temp1->next)
            {
                TrackSegment *trkSeg = temp1->data;

                for (Node *temp2 = trkSeg->waypoints->head; temp2 != NULL; temp2 = temp2->next)
                {
                    Waypoint *wpt = temp2->data;

                    if (strlen(wpt->name) > 0)
                    {
                        count++;
                    }

                    count += getLength(wpt->otherData);
                }
            }
        }
    }

    if (doc->routes != NULL)
    {
        for (Node *temp = doc->routes->head; temp != NULL; temp = temp->next)
        {
            Route *rte = temp->data;

            if (strlen(rte->name) > 0)
            {
                count++;
            }

            count += getLength(rte->otherData);

            for (Node *temp2 = rte->waypoints->head; temp2 != NULL; temp2 = temp2->next)
            {
                Waypoint *wpt = temp2->data;

                if (strlen(wpt->name) > 0)
                {
                    count++;
                }

                count += getLength(wpt->otherData);
            }
        }
    }

    return count;
}

Waypoint *getWaypoint(const GPXdoc *doc, char *name)
{
    int count = 0;

    if (doc == NULL || name == NULL)
    {
        return NULL;
    }

    if (doc->waypoints != NULL) //if 1
    {
        for (Node *temp = doc->waypoints->head; temp != NULL; temp = temp->next) //for 1
        {
            Waypoint *wpt = temp->data;

            if (strcmp(wpt->name, name) == 0)
            {
                return wpt;
            }
        } //end for 1
    }     //end if 1

    for (Node *temp = doc->routes->head; temp != NULL; temp = temp->next) //for 1
    {
        Route *route = temp->data;

        if (route->waypoints != NULL) //if 1
        {
            for (Node *temp1 = route->waypoints->head; temp1 != NULL; temp1 = temp1->next) //for 2
            {
                Waypoint *wpt = temp1->data;

                if (strcmp(wpt->name, name) == 0)
                {
                    return wpt;
                }
            } //end for 2
        }     //end if 1
    }         // end for 1

    for (Node *temp = doc->tracks->head; temp != NULL; temp = temp->next) //for 1
    {
        Track *track = temp->data;

        if (track->segments == NULL) // if 1
        {
            count += 0;
        }
        else
        {
            for (Node *temp1 = track->segments->head; temp1 != NULL; temp1 = temp1->next) //for 2
            {
                TrackSegment *trkSeg = temp1->data;

                if (trkSeg->waypoints != NULL) // if 2
                {
                    for (Node *temp2 = trkSeg->waypoints->head; temp2 != NULL; temp2 = temp2->next) //for 3
                    {
                        Waypoint *wpt = temp2->data;

                        if (strcmp(wpt->name, name) == 0)
                        {
                            return wpt;
                        }
                    } //end for 3
                }     // end if 2
            }         //end for 2
        }             // end if 1
    }                 // end for 1

    return NULL;
}

Track *getTrack(const GPXdoc *doc, char *name)
{
    if (doc == NULL || name == NULL)
    {
        return NULL;
    }

    for (Node *temp = doc->tracks->head; temp != NULL; temp = temp->next)
    {
        Track *trk = temp->data;

        if (strcmp(trk->name, name) == 0)
        {
            return trk;
        }
    }
    return NULL;
}

Route *getRoute(const GPXdoc *doc, char *name)
{
    if (doc == NULL || name == NULL)
    {
        return NULL;
    }

    for (Node *temp = doc->routes->head; temp != NULL; temp = temp->next)
    {
        Route *route = temp->data;

        if (strcmp(route->name, name) == 0)
        {
            return route;
        }
    }
    return NULL;
}

/******************************** A2 functions  - MUST be implemented *************************** */

GPXdoc *createValidGPXdoc(char *fileName, char *gpxSchemaFile)
{
    if (fileName == NULL || gpxSchemaFile == NULL)
    {
        return NULL;
    }

    GPXdoc *ptr = NULL;
    xmlDocPtr doc;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
    char *XMLFileName = fileName;
    char *XSDFileName = gpxSchemaFile;

    xmlLineNumbersDefault(1);

    ctxt = xmlSchemaNewParserCtxt(XSDFileName);

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    doc = xmlReadFile(XMLFileName, NULL, 0);

    if (doc == NULL)
    {
        fprintf(stderr, "Could not parse %s\n", XMLFileName);
    }
    else
    {
        xmlSchemaValidCtxtPtr ctxt;
        int ret;

        ctxt = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
        ret = xmlSchemaValidateDoc(ctxt, doc);

        if (ret == 0)
        {
            ptr = createGPXdoc(XMLFileName);
        }
        else if (ret > 0)
        {
        }
        else
        {
        }
        xmlSchemaFreeValidCtxt(ctxt);
        xmlFreeDoc(doc);
    }

    if (schema != NULL)
    {
        xmlSchemaFree(schema);
    }

    xmlSchemaCleanupTypes();
    xmlCleanupParser();
    xmlMemoryDump();

    return ptr;
}

bool validateGPXDoc(GPXdoc *doc, char *gpxSchemaFile)
{
    if (doc == NULL || gpxSchemaFile == NULL)
    {
        return false;
    }

    bool flag = false;

    if (validateGPXdoc(doc) == false)
    {
        return false;
    }

    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
    xmlLineNumbersDefault(1);

    ctxt = xmlSchemaNewParserCtxt(gpxSchemaFile);

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    xmlDocPtr xmldoc = NULL;
    xmlNodePtr root_node = NULL;
    LIBXML_TEST_VERSION;
    xmldoc = xmlNewDoc(BAD_CAST "1.0");

    root_node = GPXDocToNode(doc);

    xmlDocSetRootElement(xmldoc, root_node);

    xmlSchemaValidCtxtPtr ctxt2;
    int ret;

    ctxt2 = xmlSchemaNewValidCtxt(schema);
    xmlSchemaSetValidErrors(ctxt2, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
    ret = xmlSchemaValidateDoc(ctxt2, xmldoc);

    if (ret == 0)
    {
        flag = true;
    }
    else if (ret > 0)
    {
    }
    else
    {
    }

    xmlSchemaFreeValidCtxt(ctxt2);

    xmlFreeDoc(xmldoc);

    if (schema != NULL)
    {
        xmlSchemaFree(schema);
    }

    xmlSchemaCleanupTypes();
    xmlCleanupParser();
    xmlMemoryDump();

    return flag;
}

bool writeGPXdoc(GPXdoc *doc, char *fileName)
{
    if (doc == NULL)
    {
        return false;
    }

    if (fileName == NULL)
    {
        return false;
    }

    xmlDoc *xmldoc = NULL;
    xmlNode *rootNode = NULL;

    xmldoc = xmlNewDoc(BAD_CAST "1.0");

    rootNode = GPXDocToNode(doc);
    xmlDocSetRootElement(xmldoc, rootNode);

    xmlSaveFormatFileEnc(fileName, xmldoc, "ISO-8859-1", 1);

    return true;
}

float getRouteLen(const Route *rt)
{
    if (rt == NULL)
    {
        return 0;
    }

    Route *temp = (Route *)rt;

    float total;

    total = getDistanceWaypoints(temp->waypoints);

    return total;
}

float getTrackLen(const Track *tr)
{
    if (tr == NULL)
    {
        return 0;
    }

    Track *temp = (Track *)tr;

    if (getLength(temp->segments) == 0)
    {
        return 0.0;
    }

    float total = 0.0;
    
    List* allWpt = initializeList(waypointToString, dummyDelete, compareWaypoints);

    for (Node *temp2 = temp->segments->head; temp2 != NULL; temp2 = temp2->next)
    {
        TrackSegment *trkSeg = temp2->data;

        for (Node *temp1 = trkSeg->waypoints->head; temp1 != NULL; temp1 = temp1->next)
        {
            insertBack(allWpt, temp1->data);
        }
    }

    total = getDistanceWaypoints(allWpt);

    freeList(allWpt);

    return total;
}

float round10(float len)
{
    int x = len;
    int i = 0;

    while (i < x)
    {
        i += 10;
    }

    int diff = i - 10;

    if (i - x <= x - diff)
    {
        return i;
    }
    else
    {
        return diff;
    }
}

int numRoutesWithLength(const GPXdoc *doc, float len, float delta)
{
    if (doc == NULL || len < 0 || delta < 0)
    {
        return 0;
    }

    int counter = 0;

    for (Node *temp = doc->routes->head; temp != NULL; temp = temp->next)
    {
        Route *temp2 = temp->data;

        float x = getRouteLen(temp2);

        if (fabs(x - len) <= delta)
        {
            counter++;
        }
    }

    return counter;
}

int numTracksWithLength(const GPXdoc *doc, float len, float delta)
{
    if (doc == NULL || len < 0 || delta < 0)
    {
        return 0;
    }

    int counter = 0;

    for (Node *temp = doc->tracks->head; temp != NULL; temp = temp->next)
    {
        Track *temp2 = temp->data;

        float x = getTrackLen(temp2);

        if (fabs(x - len) <= delta)
        {
            counter++;
        }
    }

    return counter;
}

bool isLoopRoute(const Route *route, float delta)
{
    if (route == NULL || delta < 0)
    {
        return false;
    }

    Route *temp = (Route *)route;

    if (getLength(temp->waypoints) < 4)
    {
        return false;
    }

    Waypoint *head = temp->waypoints->head->data;
    Waypoint *tail = temp->waypoints->tail->data;

    if (head == NULL || tail == NULL)
    {
        return false;
    }

    float length = getDistancePoints(head, tail);

    if (length < delta)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isLoopTrack(const Track *tr, float delta)
{
    if (tr == NULL || delta < 0)
    {
        return false;
    }

    Track *temp = (Track *)tr;

    if (getLength(temp->segments) == 0)
    {
        return false;
    }

    int waypointCount = 0;

    for (Node *temp2 = temp->segments->head; temp2 != NULL; temp2 = temp2->next)
    {
        TrackSegment *trkSeg = temp2->data;

        waypointCount += getLength(trkSeg->waypoints);
    }

    if (waypointCount < 4)
    {
        return false;
    }

    TrackSegment *head1 = getSegWaypoints(temp->segments, true);
    TrackSegment *tail1 = getSegWaypoints(temp->segments, false);

    if (head1 == NULL || tail1 == NULL)
    {
        return false;
    }

    Waypoint *wpt1 = head1->waypoints->head->data;
    Waypoint *wpt2 = tail1->waypoints->tail->data;

    float length = getDistancePoints(wpt1, wpt2);

    if (length < delta)
    {
        return true;
    }
    else
    {
        return false;
    }
}

List *getRoutesBetween(const GPXdoc *doc, float sourceLat, float sourceLong, float destLat, float destLong, float delta)
{
    if (doc == NULL)
    {
        return NULL;
    }

    List *routes = initializeList(routeToString, dummyDelete, compareRoutes);
    Waypoint *wpt1 = createWaypoint("wpt1", sourceLong, sourceLat);
    Waypoint *wpt2 = createWaypoint("wpt2", destLong, destLat);

    for (Node *temp = doc->routes->head; temp != NULL; temp = temp->next)
    {
        Route *rte = temp->data;

        if (getLength(rte->waypoints) > 1)
        {
            Waypoint *w1 = rte->waypoints->head->data;
            Waypoint *w2 = rte->waypoints->tail->data;

            float dist1 = getDistancePoints(wpt1, w1);
            float dist2 = getDistancePoints(w2, wpt2);
            
            if (dist1 <= delta && dist2 <= delta)
            {
                insertBack(routes, rte);
            }
        }
    }

    deleteWaypoint(wpt1);
    deleteWaypoint(wpt2);

    if (getLength(routes) == 0)
    {
        freeList(routes);
        return NULL;
    }

    return routes;
}

List *getTracksBetween(const GPXdoc *doc, float sourceLat, float sourceLong, float destLat, float destLong, float delta)
{
    if (doc == NULL)
    {
        return NULL;
    }

    List *tracks = initializeList(trackToString, dummyDelete, compareTracks);
    Waypoint *wpt1 = createWaypoint("wpt1", sourceLong, sourceLat);
    Waypoint *wpt2 = createWaypoint("wpt2", destLong, destLat);

    for (Node *temp = doc->tracks->head; temp != NULL; temp = temp->next)
    {
        Track *trk = temp->data;

        if (getLength(trk->segments) >=1)
        {
            TrackSegment* firstSeg = getSegWaypoints(trk->segments, true);
            TrackSegment* lastSeg = getSegWaypoints(trk->segments, false);

            if (getLength(firstSeg->waypoints) >=1 && getLength(lastSeg->waypoints) >=1)
            {
                Waypoint *w1 = firstSeg->waypoints->head->data;
                Waypoint *w2 = lastSeg->waypoints->tail->data;

                float dist1 = getDistancePoints(wpt1, w1);
                float dist2 = getDistancePoints(w2, wpt2);
                if (dist1 <= delta && dist2 <= delta)
                {
                    insertBack(tracks, trk);
                }
            }
        }
    }

    deleteWaypoint(wpt1);
    deleteWaypoint(wpt2);

    if (getLength(tracks) == 0)
    {
        freeList(tracks);
        return NULL;
    }
    return tracks;
}

char *trackToJSON(const Track *tr)
{
    return trackToJSON2((Track*)tr);
}

char *routeToJSON(const Route *rt)
{
    return routeToJSON2((Route*)rt);
}

char *routeListToJSON(const List *list)
{
    return listToJSON((List*)list, &routeToJSON2);
}

char *trackListToJSON(const List *list)
{
    return listToJSON((List*)list, &trackToJSON2);
}

char *GPXtoJSON(const GPXdoc *gpx)
{
    if(gpx == NULL)
    {
        char* temp = calloc(20, sizeof(char));
        strcpy(temp,"{}");
        return temp;
    }

    char* json = calloc(2000,sizeof(char));

    sprintf(json,"{\"version\":%.1f,\"creator\":\"%s\",\"numWaypoints\":%d,\"numRoutes\":%d,\"numTracks\":%d}", gpx->version, gpx->creator, getNumWaypoints(gpx), getNumRoutes(gpx), getNumTracks(gpx));

    return json;
}

void addWaypoint(Route *rt, Waypoint *pt)
{
    if (rt == NULL || pt == NULL)
    {
        return;
    }
    
    insertBack(rt->waypoints,pt);
}

void addRoute(GPXdoc* doc, Route* rt)
{
    if (doc == NULL || rt == NULL)
    {
        return;
    }
    
    insertBack(doc->routes,rt);
}

GPXdoc* JSONtoGPX(const char* gpxString)
{
    if (gpxString == NULL)
    {
        return NULL;
    }
    if (strcmp((char*)gpxString,"{}") ==0)
    {
        return NULL;
    }

    char* json = (char*)gpxString;
    char* s1 = copyString(json, 1, strlen(json)-1);

    char* token = strtok(s1, ",");
    int index = getIndex(token, ':');

    char* s2 = copyString(token, index+1, strlen(token));

    double version = atof(s2);
    free(s2);

    token = strtok(NULL, ",");

    index=getIndex(token, ':');

    s2 = copyString(token, index+2, strlen(token)-1);

    GPXdoc* doc = calloc(1, sizeof(GPXdoc));

    doc->version = version;
    doc->creator = copyString(s2, 0, strlen(s2));
    free(s2);

    strcpy(doc->namespace, "http://www.topografix.com/GPX/1/1");

    doc->routes = initializeList(routeToJSON2, deleteRoute, compareRoutes);
    doc->waypoints = initializeList(waypointToJSON, deleteWaypoint, compareWaypoints);
    doc->tracks = initializeList(trackToJSON2, deleteTrack, compareTracks);

    free(s1);

    return doc;
}

Waypoint* JSONtoWaypoint(const char* gpxString)
{
    if (gpxString == NULL)
    {
        return NULL;
    }
    if (strcmp((char*)gpxString,"{}") ==0)
    {
        return NULL;
    }

    char* json = (char*)gpxString;
    char* s1 = copyString(json, 1, strlen(json)-1);

    char* token = strtok(s1, ",");
    int index = getIndex(token, ':');

    char* s2 = copyString(token, index+1, strlen(token));

    double lat = atof(s2);
    free(s2);

    token = strtok(NULL, ",");

    index=getIndex(token, ':');

    s2 = copyString(token, index+1, strlen(token));

    double lon = atof(s2);
    free(s2);

    Waypoint* wpt = createWaypoint("", lon, lat);

    free(s1);

    return wpt;
}

Route* JSONtoRoute(const char* gpxString)
{
    if (gpxString == NULL)
    {
        return NULL;
    }
    if (strcmp((char*)gpxString,"{}") ==0)
    {
        return NULL;
    }

    char* json = (char*)gpxString;
    char* s1 = copyString(json, 1, strlen(json)-1);

    int index = getIndex(s1, ':');
    char* s2 = copyString(s1, index+2, strlen(s1)-1);

    Route* rt = createRoute(s2);
    free(s2);

    return rt;
}