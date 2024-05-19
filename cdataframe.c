#include"cdataframe.h"
#include<stdio.h>
#include<stdlib.h>


CDATAFRAME* create_cdataframe(char* title) {
    CDATAFRAME* cdataframe = (CDATAFRAME*) malloc(sizeof(CDATAFRAME));
    cdataframe->title = title;
    cdataframe->tl = 0;
    cdataframe->tp = 10;
    cdataframe->columns = NULL;
    return cdataframe;
}


int insert_columns(CDATAFRAME * cdataframe, COLUMN * col){
    printf("\ninsertion de la colonne");
    if (cdataframe->columns == NULL){
        printf("\nallocation");
        cdataframe->columns = (COLUMN **) malloc((REALLOC_COL_NUMBER) * sizeof(COLUMN *));
        cdataframe->tp += REALLOC_COL_NUMBER;
    }
    if (cdataframe->columns == NULL){
        return 0;
    }
    if (cdataframe->tl == cdataframe->tp){
        COLUMN ** tmp = cdataframe->columns; // variable temporaire au cas où realoc ne fonctionnerait pas
        tmp = (COLUMN **) realloc(tmp, (cdataframe->tp + REALLOC_COL_NUMBER) * sizeof(COLUMN *));
        if (tmp != NULL) {
            cdataframe->tp += REALLOC_COL_NUMBER;
            cdataframe->columns = tmp;
        }
        else
            return 0;
    }
    if (cdataframe->tl < cdataframe->tp){
        printf("\ninsertion directe");
        cdataframe->columns[cdataframe->tl] = col;
        cdataframe->tl+=1;
        return 1;
    }
    return 0;
}


void insert_value_line(CDATAFRAME* cdataframe){
    int x;
    for(int i = 0; i < cdataframe->tl; i++){
        printf("\n\n>Entrer la valeur de la colonne %s : ", cdataframe->columns[i]->title);
        scanf(" %d", &x);
        insert_value(cdataframe->columns[i], x);
    }
}


void fill_cdataframe(CDATAFRAME* cdataframe, int nb_lines){
    for (int i = 0; i < nb_lines; i++){
        insert_value_line(cdataframe);
    }
}

void delete_line(CDATAFRAME* cdataframe, int num_line) {
    if (num_line < cdataframe->columns[0]->tl) {
        printf("\n> supression de la ligne %d...", num_line);
        for (int line = num_line; line < cdataframe->tl; line++) {
            for (int col=0; col < cdataframe->tl; col++) {
                cdataframe->columns[col]->data[line] = cdataframe->columns[col]->data[line+1];
            }
        }
        for (int col=0; col < cdataframe->tl; col++) {
            cdataframe->columns[col]->data[cdataframe->columns[col]->tl];
            cdataframe->columns[col]->tl -= 1;
        }
    }
    else printf("\n> /!\\ Supression impossible");
}

void print_cdataframe(CDATAFRAME cdataframe){
    int i, j;
    printf("\n#%s : ", cdataframe.title);
    printf("\n%d", cdataframe.tl);
    for (i=0; i<cdataframe.tl; i++){
        printf("%s   ", cdataframe.columns[i]->title);
    }
    for (i=0; i<cdataframe.columns[0]->tl; i++){
        printf("\n");
        for (j=0; j<cdataframe.tl; j++){
            printf("   %d   ", cdataframe.columns[j]->data[i]);
        }
    }
}

