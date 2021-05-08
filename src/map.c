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
    int *layer_data[3]; 
    char *tileset_name;
    int tileset_firstgid;
    int counter;
};

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
            map->map_width = atoi((char *)xmlGetProp(cur_node, (const xmlChar *)"width")); // get width
            map->map_height = atoi((char *)xmlGetProp(cur_node, (const xmlChar *)"height")); // get height
        }

        char* data = "data";
        if ( strcmp(name,data) == 0){

            int layer_data_length = map->map_width * map->map_height * 4; // works
            map->layer_data[0] = malloc(layer_data_length); // works

            printf(" --name = %s, \n", cur_node->name);
            //printf(" content = %s \n", cur_node->children->content) // commented out to reduce output on term
            char *string = (char *)cur_node->children->content; 
            char *pt = string;
            int counter = 0;
            int layer_number = 0;
            pt = strtok (string,",");
            while (pt != NULL) {
                int a = atoi(pt);
                if (counter == 3200)
                    layer_number ++;
                if (counter == 6400)
                    layer_number ++;   
                map->layer_data[layer_number][counter] = a;
                printf("map->layer_data[counter]=%d\n",map->layer_data[layer_number][counter]);
                //printf("%d\n", a);
                pt = strtok (NULL, ",");
                counter++;
                if (counter<3200)
                    map->counter ++;
            }
            //int layer_data_length = map->map_width * map->map_height * 4; // works
            //map->layer_data = malloc(layer_data_length); // works
            //int layer_data_length = 60; // use shorter value than above for debug purpose

            //worked without malloc
            // for (int i = 0; i < layer_data_length/4; i++) {
            //     map->layer_data[i] = 111; // assign bogus debug value
            //     map->counter = i; // keep track of map.layer_data length
            // }
        }
        print_element_names( cur_node->children, map );
    }
}

void loadmap() {

    //struct mymap map;
    struct mymap map = {0};
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    char * file2 = "assets/level01.tmx";
    doc = xmlReadFile(file2, NULL, 0);
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element, &map);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    int tt = 0;
    for (int i = 0; i < map.counter; i++) {
        // verify layer_data[0-14] = 111
        if (map.layer_data[0][i] != 0) {
            printf("****layer_data = %d, i = %d \n", map.layer_data[0][i], i);
            tt ++;
        }
    }
    printf("+++++layer_data_length = %d \n", map.counter);  // 3200 * 3 (3 layers.. 80*40)

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