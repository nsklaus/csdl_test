#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void loadmap() {
  FILE *fp;

  if (( fp = fopen("assets/level01.tmx","r")) == NULL) {
    printf("bleh");
  }
  int ch;
  while((ch = fgetc(fp)) != EOF) {
    putchar(ch);
  }

  fflush(stdout); 
  fclose(fp); 
}