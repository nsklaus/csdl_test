#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include "parse_map.h"

static void print_element_names(xmlNode * a_node, struct mymap *map)
{
    xmlNode *cur_node = NULL;
    char** tokens;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        char* name = (char *)cur_node->name; // grab current node name

        //if (cur_node->type == XML_ELEMENT_NODE) { 
            //char* bleh = "data";
            //if ( (char*)cur_node->name != bleh ){
                //printf("node name: %s\n", cur_node->name);
            //}
        //}

        char *map_info = "map"; //get map dimension
        if ( strcmp(name,map_info) == 0){
            xmlChar *mw = xmlGetProp(cur_node, (const xmlChar *)"width");
            xmlChar *mh = xmlGetProp(cur_node, (const xmlChar *)"height");
            map->map_width = atoi((char*)mw);
            map->map_height = atoi((char*)mh); 
            xmlFree(mw);
            xmlFree(mh);
        }

        char *layer = "layer"; // get layer id
        if ( strcmp(name,layer) == 0){
            xmlChar *li = xmlGetProp(cur_node, (const xmlChar *)"id");
            map->layer_id = atoi((char*)li) -1; 
            xmlFree(li);
        }

        char* data = "data"; // get layer data
        if ( strcmp(name,data) == 0 ){
            map->layer_length = map->map_width * map->map_height; 
            map->layer_data[map->layer_id] = malloc(map->layer_length * sizeof(int)); 
            char *string = (char *)cur_node->children->content; 
            char *pt = string;
            int counter = 0;
            pt = strtok (string,",");

            while (pt != NULL) {
                int a = atoi(pt);                
                map->layer_data[map->layer_id][counter] = a;
                pt = strtok (NULL, ",");
                counter++;
            }
        }
        print_element_names( cur_node->children, map );
    }
}
struct mymap* loadmap(char* filename){

    struct mymap *map = malloc(sizeof(struct mymap));
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    char * file2 = filename;
    doc = xmlReadFile(file2, NULL, 0);
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element, map);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return map;
}

void free_map(struct mymap *m) {
	int i;
	for(i=0; i<3; ++i)
		free(m->layer_data[i]);
	free(m);
}
