#include "../inc/res_reader.h"

bool read_res(char *filename, int *width, int *height, int *obj_num,
              t_object **obj_arr) {
    FILE *fileres = fopen(filename, "rb");
    if (fileres == NULL) {
        fprintf(stderr, "\nERROR: %s file cannot be opened\n", filename);
        return false;
    }
    fread(width, sizeof(int), 1, fileres);
    fread(height, sizeof(int), 1, fileres);
    fread(obj_num, sizeof(int), 1, fileres);
    *obj_arr = (t_object *) malloc(*obj_num * sizeof(t_object));
    int j;
    for (j = 0; j < *obj_num && !feof(fileres); ++j) {
        fread(*obj_arr + j, sizeof(t_object), 1, fileres);
    }
    *obj_num = j;
    fclose(fileres);
    return true;
}

