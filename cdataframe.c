#include"cdataframe.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>


CDATAFRAME* create_cdataframe(char* title) {
    CDATAFRAME* cdataframe = (CDATAFRAME*) malloc(sizeof(CDATAFRAME));
    cdataframe->title = title;
    cdataframe->tl = 0;
    cdataframe->tp = 10;
    cdataframe->columns = NULL;
    return cdataframe;
}


int insert_columns(CDATAFRAME* cdataframe, char* title) {
    // CAS MEMOIRE DEJA ALLOUEE
    if ((cdataframe->columns[cdataframe->tl] != NULL) && (cdataframe->tl < cdataframe->tp)) {
        cdataframe->columns[cdataframe->tl] = create_column(strcpy(title));
        cdataframe->tl += 1;
        printf("\nmemoire suffisante > insertion reussie.");
        return 1;
    }
    // ALLOCATION
    if (cdataframe->columns[cdataframe->tl] == NULL) {
        printf("\nallocation... ");
        cdataframe->columns[cdataframe->tl] = (COLUMN*) malloc(10*sizeof(COLUMN));
        // vérification que l'allocation a marché
        if (cdataframe->columns != NULL) {
            printf("\n  allocation reussie ! ");
            cdataframe->columns[cdataframe->tl] = create_column(title);
            cdataframe->tl += 1;
            cdataframe->tp += 10;
            printf("\n  > insertion reussie.");
            return 1;
        }
    }
    // REALLOCATION
    if (cdataframe->tl == cdataframe->tp) {
        printf("\nreallocation... ");
        // On doit utiliser un pointeur temporaire car si realloc ne peut pas allouer en plus,
        // le pointeur entré en paramètres est mis à NULL -> perte des données
        COLUMN** tmp = cdataframe->columns;
        tmp = (COLUMN**) realloc(tmp, (10*sizeof(COLUMN*)));
        // vérification que la réallocation a marché
        if (tmp != NULL) {
            printf("\n  reallocation reussie ! ");
            cdataframe->tp += 10;
            cdataframe->tl += 1;
            cdataframe->columns = tmp;
            printf("\n  > insertion reussie.");
            return 1;
        }
    }
    printf("\n/!\\ echec de l'insertion");
    return 0;
}


void insert_value_line(CDATAFRAME* cdataframe){
    int x;
    for(int i = 0; i < cdataframe->tl; i++){
        printf("\n>Entrer la valeur de la colonne %s : ", cdataframe->columns[i]->title);
        scanf(" %d", &x);
        insert_value(cdataframe->columns[i], x);
    }
}


void add_lines_cdataframe(CDATAFRAME* cdataframe, int nb_lines){
    for (int i = 0; i < nb_lines; i++){
        insert_value_line(cdataframe);
    }
}


void print_cdataframe(CDATAFRAME cdataframe){
    int i, j;
    printf("\n");
    for (i=0; i<cdataframe.tl; i++){
        printf("%s   ", cdataframe.columns[i]->title);
    }
    for (i=0; i<cdataframe.columns[0]->tl; i++){
        printf("\n");
        for (j=1; j<cdataframe.tl; j++){
            printf("   %d   ", cdataframe.columns[j]->data[i]);
        }
    }
}