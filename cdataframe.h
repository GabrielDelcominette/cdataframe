#include "dataframe.h"

#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H

typedef struct{
    int TP;
    int TL;
    COLUMN ** columns; // liste de pointer vers des colonnes
} CDATAFRAME;

CDATAFRAME* create_cdataframe();

void read_cdataframe_user(CDATAFRAME *);
void display_whole_cdataframe(CDATAFRAME * cdataframe);
void display_cdataframe(CDATAFRAME * cdataframe, int start_column, int start_row, int end_column, int end_row);

int insert_column(CDATAFRAME *, COLUMN *);

void display_rows_number(CDATAFRAME * cdataframe);
void display_columns_number(CDATAFRAME * cdataframe);
void cdataframe_rename_column(CDATAFRAME * cdataframe, char * new_title, int i_column);

void display_titles(CDATAFRAME * cdataframe);

#endif //CDATAFRAME_CDATAFRAME_H

