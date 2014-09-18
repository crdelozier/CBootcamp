#include <stdlib.h>
#include <stdio.h>

#define NUM 50

typedef struct point_t{
    int x;
    int y;
} point;

int compare_points(const void *v1, const void *v2){
  point *p1 = (point*)v1;
  point *p2 = (point*)v2;

  if(p1->x > p2->x && p1->y > p2->y){
    return 1;
  }else if(p1->x < p2->x && p1->y < p2->y){
    return -1;
  }else{
    return 0;
  }
}

int main(){
  point *points = (point*)malloc(NUM * sizeof(point));
  int c = 0;

  points[0].x = 5;
  points[0].y = 7;

  for(c = 1; c < NUM; c++){
    points[c].x = rand() % 100;
    points[c].y = rand() % 100;
  }

  qsort(points,NUM,sizeof(point),compare_points);

  point point_to_find;
  point_to_find.x = 5;
  point_to_find.y = 7;

  point *p1 = (point*)bsearch(&point_to_find,points,NUM,sizeof(point),compare_points);
  if(p1 != NULL){
    printf("Found it!\n");
  }

  point_to_find.x = 1000;
  point_to_find.y = 1000;

  point *p2 = (point*)bsearch(&point_to_find,points,NUM,sizeof(point),compare_points);
  if(p2 != NULL){
    printf("Found it?\n");
  }

  return 0;
}
