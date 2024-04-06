#include "dataframe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

COLUMN* create_column(char* title){
    COLUMN * column;
    column = (COLUMN*) malloc(sizeof(COLUMN));
    column->title = (char *) malloc(sizeof(char *) * (strlen(title) + 1));
    strcpy(column->title, title);
    column->TP = 0;
    column->TL = 0;
    column->data = NULL;
    return column;
}

int insert_value(COLUMN* col, int value){
    if (col->data == NULL){
        col->data = (int*) malloc(REALOC_SIZE * sizeof(int));
        col->TP += REALOC_SIZE;
    }
    if (col->data == NULL){
        return 0;
    }
    if (col->TL == col->TP){
        int * tmp = col->data; // variable temporaire au cas où realoc ne fonctionnerait pas
        tmp = (int *) realloc(tmp, (col->TP + REALOC_SIZE) * sizeof(int));
        if (tmp != NULL) {
            col->TP += REALOC_SIZE;
            col->data = tmp;
        }
        else
            return 0;
    }
    if (col->TL < col->TP){
        col->data[col->TL] = value;
        col->TL+=1;
        return 1;
    }
    return 0;
}

void delete_column(COLUMN** col){
    for (int i=0 ; i<(*col)->TP ; i++)
        free((*col)->data + i);
    free(*col);
}

int occurence(COLUMN * col, int value){
    int number = 0;
    for (int i=0; i<col->TL; i++){
        if (value==*(col->data + i))
            number++;
    }
    return number;
}

int find_value(COLUMN * col, int pos){
    return *(col->data + pos);
}

void print_col(COLUMN* col){
    for (int i=0; i<col->TL; i++)
        printf("[%d] %d", i, *(col->data + i));
}

int n_taller_values(COLUMN * col, int value){
    int number = 0;
    for (int i=0; i<col->TL; i++)
        if (value<=*(col->data + i))
            number++;
    return number;
}

int n_smaller_values(COLUMN * col, int value){
    int number = 0;
    for (int i=0; i<col->TL; i++)
        if (value>=*(col->data + i))
            number++;
    return number;
}

int n_equals_values(COLUMN * col, int value){
    return occurence(col, value);
}