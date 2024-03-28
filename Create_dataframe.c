#include "Create_dataframe.h"
#include <stdlib.h>

COLUMN* create_column(char* title){
    COLUMN * column;
    column = (COLUMN*) malloc(sizeof(COLUMN));
    column->title = title;
    column->TP = REALOC_SIZE;
    column->TL = 0;
    column->data = NULL;
    return column;
}

int insert_value(COLUMN* col, int value){
    if (col->data == NULL){
        col->data = (int*) malloc(256* sizeof(int));
    }
    if (col->data == NULL){
        return 0;
    }
    if (col->TL == col->TP){
        col->TP += REALOC_SIZE;
        realloc(col->data, col->TP * sizeof(int));
    }
    if (col->TL < col->TP){
        col->data[col->TL-1] = value;
        col->TL+=1;
        return 1;
    }
    return 0;
}