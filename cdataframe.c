#include "cdataframe.h"
#include <stdlib.h>

CDATAFRAME* create_cdataframe(){
    CDATAFRAME * dataframe;
    dataframe = (CDATAFRAME*) malloc(sizeof(CDATAFRAME));
    dataframe->TP = 10;
    dataframe->TL = 0;
    dataframe->columns = NULL;
    return dataframe;
}

int insert_column(CDATAFRAME * cdataframe){
    if (cdataframe->columns == NULL){
        cdataframe->columns = (COLUMN *) malloc(256 * sizeof(COLUMN));
    }
    if (cdataframe->columns == NULL){
        return 0;
    }
    if (cdataframe->TL == cdataframe->TP){
        cdataframe->TP += REALOC_SIZE;
        realloc(cdataframe->columns, cdataframe->TP * sizeof(int));
    }
    if (cdataframe->TL < cdataframe->TP){
        cdataframe->columns[cdataframe->TL-1] = value;
        cdataframe->TL+=1;
        return 1;
    }
    return 0;
}

void read_cdataframe_user(CDATAFRAME * cdataframe) {
}