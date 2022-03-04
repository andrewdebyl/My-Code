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
#include <stdbool.h>


int main(int argc, char **argv)
{
    
    GPXdoc* doc = createValidGPXdoc(argv[1], argv[2]);

    char* json = routeListToJSON(doc->routes);
    printf("%s\n",json);
    free(json);

    json = trackListToJSON(doc->tracks);
    printf("%s\n",json);
    free(json);

    json = waypointListToJSON(doc->waypoints);
    printf("%s\n",json);
    free(json);

    return 0;
}