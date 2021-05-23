#ifndef PARSEMAP_H_INCLUDED
#define PARSEMAP_H_INCLUDED

struct  mymap{
    int map_width;
    int map_height;
    int layer_name;
    int *layer_data[3];
    int layer_length;
    int layer_id;
    char *tileset_name;
    int tileset_firstgid;
    int counter;
} ;

//void loadmap();
struct mymap* loadmap(char* filename);
void free_map(struct mymap *m);

#endif
