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

void write_cdataframe(CDATAFRAME * cdataframe, int start_column, int start_row, int end_column, int end_row);

int insert_column(CDATAFRAME *, COLUMN *);
#endif //CDATAFRAME_CDATAFRAME_H
