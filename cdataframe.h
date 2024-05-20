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


void print_all_cdataframe(CDATAFRAME cdataframe);


void print_cdataframe_limit_col(CDATAFRAME cdataframe, int limit_col);


void print_cdataframe_limit_line(CDATAFRAME cdataframe, int limit_line);


void fill_cdataframe_l_by_l(CDATAFRAME* cdataframe, int nb_col, int nb_lines);


void fill_cdataframe_c_by_c(CDATAFRAME* cdataframe, int nb_col, int nb_line);


void insert_value_line(CDATAFRAME* cdataframe);


void delete_line(CDATAFRAME* cdataframe, int num_line);


int search_idcol_by_name(CDATAFRAME cdataframe, char* title);


void delete_col_by_id(CDATAFRAME* cdataframe, int id_col);



#endif //CDATAFRAME_H
