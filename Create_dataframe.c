#include "Create_dataframe.h"
#include <stdlib.h>

COLUMN* create_column(char* title){
    COLUMN * column;
    column = (COLUMN*) malloc(sizeof(COLUMN));
    column->title = title;
    column->TP = 256;
    column->TL = 0;
    column->data = NULL;
    return column;
}
