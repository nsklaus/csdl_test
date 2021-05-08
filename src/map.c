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
    int *layer_data; 
    char *tileset_name;
    int tileset_firstgid;
    int counter;
};

// int is_leaf(xmlNode * node){
//     xmlNode * child = node->children;
//     while(child){
//         if(child->type == XML_ELEMENT_NODE) return 0;
//         child = child->next;
//     }
//     return 1;
// }

static void print_element_names(xmlNode * a_node, struct mymap *map)
{
    xmlNode *cur_node = NULL;
    char** tokens;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        char* name = (char *)cur_node->name; // grab current node name

        if (cur_node->type == XML_ELEMENT_NODE) { 
            printf("node name: %s\n", cur_node->name);
        }

        char *map_info = "map";
        if ( strcmp(name,map_info) == 0){
            printf("(char)name = %s\n", xmlGetProp(cur_node, (const xmlChar *)"width")); //debug output "80" (char)
            printf("(char)name = %s\n", xmlGetProp(cur_node, (const xmlChar *)"height")); //debug output "40" (char)
            map->map_width = (int)atoi((char *)xmlGetProp(cur_node, (const xmlChar *)"width")); // get width
            map->map_height = (int)atoi((char *)xmlGetProp(cur_node, (const xmlChar *)"height")); // get height
            printf("(int)map.map_width = %d\n", map->map_width ); //debug output int 80 (int)
            printf("(int)map.map_height = %d\n", map->map_height ); //debug output int 40 (int)
        }

        char* data = "data";
        if ( strcmp(name,data) == 0){
            printf(" --name = %s, \n", cur_node->name);
            //printf(" content = %s \n", cur_node->children->content) // commented out to reduce output on term
            //int layer_data_length = map->map_width * map->map_height * 4; // works
            //map->layer_data = malloc(layer_data_length); // works
            int layer_data_length = 60; // use shorter value than above for debug purpose
            for (int i = 0; i < layer_data_length/4; i++) {
                map->layer_data[i] = 111; // assign bogus debug value
                map->counter = i; // keep track of map.layer_data length
            }
        }
        print_element_names( cur_node->children, map );
    }
}

void loadmap() {

    struct mymap map; // instanciate struct
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    char * file2 = "assets/level01.tmx";
    doc = xmlReadFile(file2, NULL, 0);
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element, &map);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    for (int i = 0; i < map.counter; i++) {
        // verify layer_data[0-14] = 111
        printf("****layer_data = %d \n", map.layer_data[i]);
    }
    printf("-----map.counter=%d\n",map.counter); //debug: 60/4 = 15
    
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