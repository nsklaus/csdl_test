#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

void loadmap() {

    /* WIP: open map file, read line by line, search for patterns 
    if found store it, in array, later on process the array to construct game map */
    static const char filename[] = "assets/level01.tmx";
    FILE *file = fopen(filename, "r");
    int count = 0;
    if ( file != NULL ) 
    {
        char line[256]; // maximum line size
        const char *mystring = "layer id"; // pattern to search for
        while (fgets(line, sizeof line, file) != NULL) // read line by line 
        {
            if (strstr(line,mystring)) // if pattern is found
            {
                printf("%s\n",line); // print it
                fflush(stdout); 
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