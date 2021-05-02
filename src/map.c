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

    char *patterns[10] = { "map version", "tileset firstgid", // pattern to search for
                        "image source", "layer id","data encoding " };

    static const char filename[] = "assets/level01.tmx"; // map file
    FILE *file = fopen(filename, "r");

    int count = 0;
    if ( file != NULL ) 
    {
        char line[256]; // maximum line size
        char *bleh = "";
        while (fgets(line, sizeof line, file) != NULL) // read line by line 
        {

            // get map width
            if (strstr(line, "map version")) {
                printf("\noriginal line:\n=============\n %s \n", line);
                fflush(stdout); 
                char *map_width = strstr(line, "width="); 
                int pos = map_width - line;
                char *result; // the "result"

                result = strtok(line + pos, "\""); // find the first double quote
                result = strtok(NULL, "\"");   // find the second double quote
                printf("line until prop:\n===============\n %s \n", line);
                printf("position of prop in line = %ld \n", map_width - line);
                printf("grabbed prop 'width' = %s\n\n", result);
                fflush(stdout); 
            }
            // for (int i = 0; i < 9; i++ ) { // check each line with each entry of patterns array
            //     if (patterns[i] != NULL && strstr(line,patterns[i])) // if pattern is found
            //     {
            //         printf("%s\n",line); // print it
            //         fflush(stdout); 
            //     }
            // }
        } 
        fclose(file);
    } 
    else 
    {
        printf("file doesn't exist\n");
        fflush(stdout); 
    }

}