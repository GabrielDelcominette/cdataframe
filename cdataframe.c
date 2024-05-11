#include"cdataframe.h"
#include<stdio.h>
#include<stdlib.h>


CDATAFRAME* create_cdataframe(char* title) {
    CDATAFRAME* cdataframe = (CDATAFRAME*) malloc(sizeof(CDATAFRAME));
    cdataframe->title = title;
    cdataframe->tl = 0;
    cdataframe->tp = 0;
    cdataframe->columns = NULL;
    return cdataframe;
}


int insert_column(CDATAFRAME* cdataframe, COLUMN* col) {
    // CAS MEMOIRE DEJA ALLOUEE
    if (cdataframe->columns != NULL && cdataframe->tl < cdataframe->tp) {
        cdataframe->columns[cdataframe->tl] = col;
        cdataframe->tl += 1;
        printf("\nmemoire suffisante > insertion reussie.");
        return 1;
    }
    // ALLOCATION
    if (cdataframe->columns == NULL) {
        printf("\nallocation... ");
        cdataframe->columns = (COLUMN**) malloc(sizeof(COLUMN*));
        // vérification que l'allocation a marché
        if (cdataframe->columns != NULL) {
            printf("allocation reussie ! ");
            cdataframe->columns[cdataframe->tl] = col;
            cdataframe->tl += 1;
            cdataframe->tp += 1;
            printf("> insertion reussie.");
            return 1;
        }
    }
    // REALLOCATION
    if (cdataframe->tl == cdataframe->tp) {
        printf("\nreallocation... ");
        // On doit utiliser un pointeur temporaire car si realloc ne peut pas allouer en plus,
        // le pointeur entré en paramètres est mis à NULL -> perte des données
        COLUMN** tmp = cdataframe->columns;
        tmp = (COLUMN**) realloc(tmp, (sizeof(COLUMN*)));
        // vérification que la réallocation a marché
        if (tmp != NULL) {
            printf("reallocation reussie ! ");
            cdataframe->tp += 1;
            cdataframe->tl += 1;
            cdataframe->columns = tmp;
            printf("> insertion reussie.");
            return 1;
        }
    }
    printf("\n/!\\ echec de l'insertion");
    return 0;
}
