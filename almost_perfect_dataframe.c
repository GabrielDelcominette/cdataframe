#include "almost_perfect_dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AP_COLUMN* create_column(ENUM_TYPE type, char * title){
    AP_COLUMN * column;
    column = (AP_COLUMN*) malloc(sizeof(AP_COLUMN));                                                                                                                                                                                                                                                                                                                                                                                                             COLUMN));
    column->title = (char *) malloc(sizeof(char *) * (strlen(title) + 1));
    strcpy(column->title, title);
    column->TP = 0;
    column->TL = 0;
    column->column_type = type;
    column->data = NULL;
    column->index = NULL;
    return column;
}