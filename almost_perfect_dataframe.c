#include "almost_perfect_dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


AP_COLUMN* create_AP_column(ENUM_TYPE type, char * title){
    AP_COLUMN * column;
    column = (AP_COLUMN*) malloc(sizeof(AP_COLUMN));
    column->title = (char *) malloc(sizeof(char *) * (strlen(title) + 1));
    strcpy(column->title, title);
    column->TP = 0;
    column->TL = 0;
    column->column_type = type;
    column->data = NULL;
    column->index = NULL;
    return column;
}

int insert_AP_value(AP_COLUMN *col, void *value){
    int allocation = 0; // booléen, correspond à si l'on alloue de l'espace mémoire en plus
    if (col->data == NULL){
        // allocation du tableau de pointeur
        col->data = (DATA_TYPE **) malloc(REALOC_SIZE * sizeof(DATA_TYPE*));
        if (col->data == NULL) // dans le cas où l'allocation a échoué
            return 0;
        allocation = 1;
        col->TP += REALOC_SIZE;
    }

    if (col->TL == col->TP){
        DATA_TYPE ** tmp = col->data; // variable temporaire au cas où realoc ne fonctionnerait pas
        tmp = (DATA_TYPE **) realloc(tmp, (col->TP + REALOC_SIZE) * sizeof(DATA_TYPE*));
        if (tmp == NULL)
            return 0;
        allocation = 1;
        col->TP += REALOC_SIZE;
        col->data = tmp;
    }

    // allocation des tableaux sur lesquels pointes les pointeurs
    if (allocation) {
        for (int i = 0; i < REALOC_SIZE; i++) {
            col->data[i] = (DATA_TYPE *) malloc(sizeof(DATA_TYPE));
        }
    }

    if (col->TL < col->TP){
        value = (DATA_TYPE*) value; // on convertie le type de value
        col->data[col->TL] = value;
        col->TL+=1;
        return 1;
    }
    return 0;
}


void delete_column(AP_COLUMN **col){
    free((*col)->title);
    for (int i = 0; i<(*col)->TP; i++){
        free((*col)->data[i]);
    }
    free((*col)->data);
    free(*col);
    free(col);
}