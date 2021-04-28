#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <json-c/json.h>
#include "jsmn.h"
#include "map.h"

void loadmap() {

    /* test jsmn json parser */
    jsmn_parser parser;
    jsmntok_t tokens[10];

    jsmn_init(&parser);


    /* WIP: open map file, read line by line, search for patterns 
    if found store it, in array, later on process the array to construct game map */
    char *patterns[10] = { "map version", "tileset firstgid", // pattern to search for
                           "image source", "layer id" };  
                           //, "data encoding" };

    static const char filename[] = "assets/level01.json"; // map file
    FILE *file = fopen(filename, "r");

    int count = 0;
    if ( file != NULL ) 
    {
        char line[256]; // maximum line size
        char *p = 0; 
        int len = 0; 
        while (fgets(line, sizeof line, file) != NULL) // read line by line 
        {
            int llen = strlen(line);  // get length of 'line'
            p = realloc(p, len + llen + 1);  // ?
            memcpy(p+len, line, llen);   // ?
            len += llen;   // ?
        } 
        printf("%s \n", p); 
        jsmn_parse(&parser, p, strlen(p), tokens, 10);

        p[len] = 0;
        fclose(file);
    } 
    else 
    {
        printf("file doesn't exist\n");
        fflush(stdout); 
    }
}