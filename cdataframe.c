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

void read_cdataframe_user(CDATAFRAME *){
    
}