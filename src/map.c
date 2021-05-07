#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
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
    int *layer_data; // need a 2d array, of unknown size before hand
    char *tileset_name;
    int tileset_firstgid;

};

static void print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    char** tokens;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node name: %s\n", cur_node->name);
        }

        char* c = "data";
        char* a = (char *)cur_node->name;
        if ( strcmp(a,c) == 0){
            printf(" name = %s, ", cur_node->name);
            printf(" content = %s \n", cur_node->children->content);
            // here i get data, very long string looking like:
            // 508,507,508,507,508,507,507,507,508,507,106,106,106,106,106,106,106,106, ...

        }
        print_element_names( cur_node->children );
    }
}

void loadmap() {

    struct mymap map;

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    char * file2 = "assets/level01.tmx";
    doc = xmlReadFile(file2, NULL, 0);
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    

    static const char filename[] = "assets/level01.tmx"; // map file
    FILE *file = fopen(filename, "r"); 

    int count = 0;
    if ( file != NULL ) 
    {
        char line[256]; // maximum line size
        char line_temp[256];
        char previous_line[256];
        while (fgets(line, sizeof line, file) != NULL) // read line by line 
        {
 
        } 
        fclose(file);
    } 
    else 
    {
        printf("file doesn't exist\n");
        fflush(stdout); 
    }

}