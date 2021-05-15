#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include "parse_map.h"


char* concat_2_strings(char* str1, char *str2) { 
    char* new = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(new, str1); 
    strcat(new, str2); 
    return new; 
}
//bleh = concat_2_strings(bleh, line);

static void print_element_names(xmlNode * a_node, struct mymap *map)
{
    xmlNode *cur_node = NULL;
    char** tokens;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        char* name = (char *)cur_node->name; // grab current node name

        if (cur_node->type == XML_ELEMENT_NODE) { 
            printf("node name: %s\n", cur_node->name);
        }

        char *map_info = "map"; //get map dimension
        if ( strcmp(name,map_info) == 0){
            map->map_width = atoi((char *)xmlGetProp(cur_node, (const xmlChar *)"width")); // get width
            map->map_height = atoi((char *)xmlGetProp(cur_node, (const xmlChar *)"height")); // get height
        }

        char *layer = "layer"; // get layer id
        if ( strcmp(name,layer) == 0){
            map->layer_id = atoi((char *)xmlGetProp(cur_node, (const xmlChar *)"id")) -1 ;
            printf("layer id = %d\n", map->layer_id); //debug
        }

        char* data = "data"; // get layer data
        if ( strcmp(name,data) == 0 ){
            map->layer_length = map->map_width * map->map_height;
            map->layer_data[map->layer_id] = malloc(map->layer_length * sizeof(int)); 

            printf(" --name = %s, \n", cur_node->name);
            //printf(" content = %s \n", cur_node->children->content) // commented out to reduce output on term
            char *string = (char *)cur_node->children->content; 
            char *pt = string;
            int counter = 0;
            pt = strtok (string,",");
            printf("huuh layer_id = %d \n", map->layer_id);

            while (pt != NULL) {
                int a = atoi(pt);                
                map->layer_data[map->layer_id][counter] = a;
                // if conditions to reduce output, and confirm data is 
                // being filled in "layer_data[][]" first dimension
                if (a != 0 && a != 507 && a !=508 && a != 178 && a != 476 &&  a!= 146 && a != 147 ) {
                    printf("layer_data[%d][%d]=%d\n", map->layer_id, counter, map->layer_data[map->layer_id][counter]);
                }
                pt = strtok (NULL, ",");
                counter++;
            }
        }
        print_element_names( cur_node->children, map );
    }
}
struct mymap *loadmap(char* filename){

    struct mymap *map = malloc(sizeof(struct mymap));
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    char * file2 = filename;
    doc = xmlReadFile(file2, NULL, 0);
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element, map);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    printf("\n");
    for (int i = 320; i < 350; i++) {
        // why output is always zero ? in the while loop above i see first dimension is being filled.
        // but i cannot verify it here.
        printf("map value layer[1][i] = %d\n", map->layer_data[1][i]);  
    }

    return map;
}