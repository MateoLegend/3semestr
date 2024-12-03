#include <stdio.h>
#include "line.h"
#include "point.h"

struct line{
    point_t *start;
    point_t *end;
};

point_t *line_new(point_t *p1, point_t *p2){
    point_t *l = malloc(sizeof(line_t));
    l->start = p1;
    l->end = p2;
    return l;
}

line_free(line_t *l){
    free(l);
}