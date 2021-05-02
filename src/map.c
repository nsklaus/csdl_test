#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <json-c/json.h>
#include "jsmn.h"
#include "map.h"

char* concat_2_strings(char* str1, char *str2) { 
    char* new = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(new, str1); 
    strcat(new, str2); 
    return new; 
}
//bleh = concat_2_strings(bleh, line);

struct mymap {
    int map_width;
    int map_height;
    int layer_name;
    char *tileset_name;
    int tileset_firstgid;

};

void loadmap() {

    struct mymap map;

    static const char filename[] = "assets/level01.tmx"; // map file
    FILE *file = fopen(filename, "r");

    int count = 0;
    if ( file != NULL ) 
    {
        char line[256]; // maximum line size
        while (fgets(line, sizeof line, file) != NULL) // read line by line 
        {
            // get map width
            if (strstr(line, "map version")) { // select line where width property exists
                char *map_width = strstr(line, "width="); // search for property in line
                int pos = map_width - line; // find position of property in line
                char *result; // store the "result"
                result = strtok(line + pos, "\""); // find the first double quote
                result = strtok(NULL, "\"");   // find the second double quote
                map.map_width = atoi(result); // cast string to int, set struct member
            }
        } 
        printf("width = %d\n", map.map_width); // debug output
        fclose(file);
    } 
    else 
    {
        printf("file doesn't exist\n");
        fflush(stdout); 
    }

}