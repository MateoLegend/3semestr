#include <stdio.h>
#include "point.h"

struct point{
    int x;
    int y;
};

point_t *point_new(int x, int y){
    point_t *p = malloc(sizeof(point_t));
    p->x = x;
    p->y = y;
    return p;
}

point_free(point_t* p){
    free(p);
}

point_get_x(point_t* p){
    return ;
}