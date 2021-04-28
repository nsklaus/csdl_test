#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "map.h"

void loadmap() {

    /* WIP: open map file, read line by line, search for patterns 
    if found store it, in array, later on process the array to construct game map */

    char *patterns[10] = { "map version", "tileset firstgid", // pattern to search for
                           "image source", "layer id" };  
                           //, "data encoding" };

    static const char filename[] = "assets/level01.tmx"; // map file
    FILE *file = fopen(filename, "r");
    int count = 0;
    if ( file != NULL ) 
    {
        char line[256]; // maximum line size
        while (fgets(line, sizeof line, file) != NULL) // read line by line 
        {
            for (int i = 0; i < 9; i++ ) { // check each line with each entry of patterns array
                if (patterns[i] != NULL && strstr(line,patterns[i])) // if pattern is found
                {
                    printf("%s\n",line); // print it
                    fflush(stdout); 
                }
            }
        }
        fclose(file);
    } 
    else 
    {
        printf("file doesn't exist\n");
        fflush(stdout); 
    }
}