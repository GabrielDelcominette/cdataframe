#include<stdlib.h>
#include<stdio.h>
#include"column.h"
#include"string.h"


COLUMN* create_column(char* title){
    COLUMN * column;
    column = (COLUMN*) malloc(sizeof(COLUMN));
    column->title = (char *) malloc(sizeof(char *) * (strlen(title) + 1));
    strcpy(column->title, title);
    column->tp = 0;
    column->tl = 0;
    column->data = NULL;
    return column;
}


int insert_value(COLUMN* col, int value) {
    // CAS MEMOIRE DEJA ALLOUEE
    if (col->data != NULL && col->tl < col->tp) {
        col->data[col->tl] = value;
        col->tl += 1;
        printf("\nmemoire suffisante > insertion reussie.");
        return 1;
    }
    // ALLOCATION
    if (col->data == NULL) {
        printf("\nallocation... ");
        col->data = (int*) malloc(sizeof(int)*REALLOC_SIZE);
        // vérification que l'allocation a marché
        if (col->data != NULL) {
            printf("allocation reussie ! ");
            col->data[col->tl] = value;
            col->tl += 1;
            col->tp += REALLOC_SIZE;
            printf("> insertion reussie.");
            return 1;
        }
    }
    // REALLOCATION
    if (col->tl == col->tp) {
        printf("\nreallocation... ");
        // On doit utiliser un pointeur temporaire car si realloc ne peut pas allouer en plus,
        // le pointeur entré en paramètres est mis à NULL -> perte des données
        int* tmp = col->data;
        tmp = (int*) realloc(tmp, (REALLOC_SIZE + col->tp) * sizeof(int));
        // vérification que la réallocation a marché
        if (tmp != NULL) {
            printf("reallocation reussie ! ");
            col->tp += REALLOC_SIZE;
            col->tl += 1;
            col -> data = tmp;
            printf("> insertion reussie.");
            return 1;
        }
    }
    printf("\n/!\\ echec de l'insertion");
    return 0;
}


void delete_column(COLUMN* col) {
    free(col->data);
    free(col->title);
    free(col);
}


void print_col(COLUMN* col) {
    int i;
    printf("\n%s", col->title);
    for (i=0; i<col->tl; i++) {
        printf("\n[%d] %d", i, col->data[i]);
    }
}


int occurrence_x(COLUMN col, int x) {
    int occur = 0, i;
    for (i=0; i<col.tl; i++) {
        if (x == col.data[i]) {
            occur += 1;
        }
    }
    return occur;
}


int position_x(COLUMN col, int pos) {
    if (pos>=0 && pos <= col.tl) {
        return col.data[pos];
    }
    return -1;
}


int superior_x(COLUMN col, int x) {
    int occur_sup = 0, i;
    for (i=0; i<col.tl; i++) {
        if (x > col.data[i]) {
            occur_sup += 1;
        }
    }
    return occur_sup;
}


int inferior_x(COLUMN col, int x) {
    int occur_inf = 0, i;
    for (i=0; i<col.tl; i++) {
        if (x < col.data[i]) {
            occur_inf += 1;
        }
    }
    return occur_inf;
}


