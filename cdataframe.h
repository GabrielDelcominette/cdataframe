#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include"column.h"

typedef struct {
    char* title;
    int tp;
    int tl;
    COLUMN** columns;
}CDATAFRAME;


#endif //CDATAFRAME_H
