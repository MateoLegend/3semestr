#include <stdio.h>
#include "line.h"
#include "point.h"

int main(){
    point_t *p1 = point_new(10,20);
    point_t *p2 = point_new(30,40);

    line_t *l1 = line_new(p1,p2);

    printf("Dlugość linii: %f\n", line_get_length(l1));

    line_free(l1);
    point_free(p2);
    point_free(p1);

    return 0;
}