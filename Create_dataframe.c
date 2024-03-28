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
void delete_column(COLUMN** col){
    free((*col)->data);
    free()
}