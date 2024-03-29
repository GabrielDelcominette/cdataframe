#include "dataframe.h"

#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H

typedef struct{
    int TP;
    int TL;
    COLUMN * columns;
} CDATAFRAME;

CDATAFRAME* create_cdataframe();

void read_cdataframe_user(CDATAFRAME *);

int insert_column(CDATAFRAME *);
#endif //CDATAFRAME_CDATAFRAME_H
