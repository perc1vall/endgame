#ifndef LEVEL_BUILDER_RES_READER_H
#define LEVEL_BUILDER_RES_READER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_object {
    int x1, y1;
    int x2, y2;
    char file[20];
    unsigned int type;
    int id;
} t_object;

bool read_res(char *filename, int *width, int *height, int *obj_num,
              t_object **obj_arr);

#endif //LEVEL_BUILDER_RES_READER_H
