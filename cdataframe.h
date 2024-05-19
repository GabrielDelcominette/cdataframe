#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include"column.h"

#define REALLOC_COL_NUMBER 10

typedef struct {
    char* title;
    int tp;
    int tl;
    COLUMN** columns;
}CDATAFRAME;

CDATAFRAME* create_cdataframe(char* title);


int insert_columns(CDATAFRAME* cdataframe, COLUMN* column);


void print_cdataframe(CDATAFRAME cdataframe);


void add_lines_cdataframe(CDATAFRAME* cdataframe, int nb_lines);


void insert_value_line(CDATAFRAME* cdataframe);

#endif //CDATAFRAME_H
