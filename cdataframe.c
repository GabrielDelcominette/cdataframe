#include "cdataframe.h"
#include <stdlib.h>
#include <stdio.h>

#define REALLOC_COL_NUMBER 10

CDATAFRAME* create_cdataframe(){
    CDATAFRAME * dataframe;
    dataframe = (CDATAFRAME*) malloc(sizeof(CDATAFRAME));
    dataframe->TP = 0;
    dataframe->TL = 0;
    dataframe->columns = NULL;
    return dataframe;
}

int insert_column(CDATAFRAME * cdataframe, COLUMN * col){
    if (cdataframe->columns == NULL){
        printf("yooo\n");
        cdataframe->columns = (COLUMN **) malloc(REALLOC_COL_NUMBER * sizeof(COLUMN *));
        cdataframe->TP += REALLOC_COL_NUMBER;
    }
    printf("On regarde le premier avant insertion : %s - - adresse %X\n", (*cdataframe->columns)->title, *cdataframe->columns);
    if (cdataframe->columns == NULL){
        return 0;
    }
    if (cdataframe->TL == cdataframe->TP){
        printf("yiii \n");
        COLUMN ** tmp = cdataframe->columns; // variable temporaire au cas où realoc ne fonctionnerait pas
        tmp = (COLUMN **) realloc(tmp, (cdataframe->TP + REALLOC_COL_NUMBER) * sizeof(COLUMN *));
        if (tmp != NULL) {
            cdataframe->TP += REALLOC_COL_NUMBER;
            cdataframe->columns = tmp;
        }
        else
            return 0;
    }
    if (cdataframe->TL < cdataframe->TP){
        printf("Le TL est egal a : %d\n", cdataframe->TL);
        printf("Le premier titre est : %s\n", cdataframe->columns[0]->title);
        //*(cdataframe->columns + cdataframe->TL) = col;
        cdataframe->columns[cdataframe->TL] = col;
        cdataframe->TL+=1;
        return 1;
    }
    return 0;
}

void read_cdataframe_user(CDATAFRAME * cdataframe) {
    int C, L, value;
    char name[50];
    COLUMN* new_column = NULL;
    //new_column = (COLUMN**) malloc(sizeof(COLUMN **));
    //new_column= (COLUMN*) malloc(sizeof(COLUMN *));
    printf("saisissez le nombres de colonnes de la cdataframe : \n");
    scanf(" %d", &C);
    printf("saisissez le nombres de lignes de la cdataframe : \n");
    scanf(" %d", &L);
    printf("\t\t********** Entrez les titres des colonnes *********\n");
    for (int i=0; i<C; i++){
        printf("Saisissez le titre de la colonnes %d : \n", i+1);
        scanf(" %s", name);
        new_column = create_column(name); // création d'une nouvelle colonne ayant pour titre celui entré par l'utilisateur
        insert_column(cdataframe, new_column); // on ajoute la nouvelle colonne à la cdataframe
        printf("Voici la nouvelle colone %s en position %d - adresse %X\n", (cdataframe->columns[i])->title, i, cdataframe->columns[i]);
    }
    for (int i=0; i<C; i++){
        //printf("Voici la nouvelle colone %s en position %d\n", (cdataframe->columns[i])->title, i);
    }

    printf("\t\t ********* Entrez les valeurs dans les cellules ***********\n");
    for (int colonne=0; colonne<C; colonne++){
        for (int ligne=0; ligne<L; ligne++){
            printf("Saisissez la valeure de la ligne %d de la colonne %d : \n", ligne+1, colonne+1);
            scanf("%d", &value);
            insert_value(*(cdataframe->columns + colonne), value);
        }
    }
}

void write_cdataframe(CDATAFRAME * cdataframe) {
    printf("test01\n\n");
    for (int i=0; i<cdataframe->TL; i++){
        printf("%s %d\t", (*(cdataframe->columns + i))->title, i);
    }
    for (int j=0; j<(*cdataframe->columns)->TL; j++){
        printf("\n");
        for (int i = 0; i < cdataframe->TL; i++) {
            printf("%d\t", *((*(cdataframe->columns + j))->data + j));
        }
    }
}