#include "map_loader.h"
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path)
{
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* data = malloc(size + 1);
    fread(data, 1, size, f);
    data[size] = 0;

    fclose(f);
    return data;
}
