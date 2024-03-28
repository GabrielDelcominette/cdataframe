#include "Create_dataframe.h"
#include <stdlib.h>
#include <stdio.h>

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
    for (int i=0 ; i<(*col)->TP ; i++)
        free((*col)->data + i);
    free(*col);
}

void print_col(COLUMN* col){
    for (int i=0; i<col->TL; i++)
        printf("[%d] %d", i, *(col->data + i));
}