#include "cdataframe.h"
#include <stdlib.h>
#include <stdio.h>

#define REALLOC_COL_NUMBER 10

CDATAFRAME* create_cdataframe(){
    CDATAFRAME * dataframe;
    dataframe = (CDATAFRAME*) malloc(sizeof(CDATAFRAME));
    dataframe->TP = 10;
    dataframe->TL = 0;
    dataframe->columns = NULL;
    return dataframe;
}

int insert_column(CDATAFRAME * cdataframe, COLUMN * col){
    if (cdataframe->columns == NULL){
        cdataframe->columns = (COLUMN **) malloc(REALLOC_COL_NUMBER * sizeof(COLUMN *));
    }
    if (cdataframe->columns == NULL){
        return 0;
    }
    if (cdataframe->TL == cdataframe->TP){
        COLUMN ** tmp = cdataframe->columns; // variable temporaire au cas où realoc ne fonctionnerait pas
        tmp = (COLUMN **) realloc(tmp, (cdataframe->TP + REALLOC_COL_NUMBER) * sizeof(COLUMN *));
        if (tmp != NULL) {
            cdataframe->TP += REALOC_SIZE;
            cdataframe->columns = tmp;
        }
        else
            return 0;
    }
    if (cdataframe->TL < cdataframe->TP){
        cdataframe->columns[cdataframe->TL] = col;
        cdataframe->TL+=1;
        return 1;
    }
    return 0;
}

void read_cdataframe_user(CDATAFRAME * cdataframe) {
    int C, L, value;
    char name[50];
    COLUMN * new_column;
    printf("saisissez le nombres de colonnes de la cdataframe : ");
    scanf("%d\n", &C);
    printf("saisissez le nombres de lignes de la cdataframe : ");
    scanf("%d\n", &L);
    printf("\t\t********** Entrez les titres des colonnes *********\n");
    for (int i=0; i<C; i++){
        printf("Saisissez le titre de la colonnes %d : ", i+1);
        scanf("%s", name);
        new_column = create_column(name); // création d'une nouvelle colonne ayant pour titre celui entré par l'utilisateur
        insert_column(cdataframe, new_column); // on ajoute la nouvelle colonne à la cdataframe
    }

    printf("\t\t ********* Entrez les valeurs dans les cellules ***********\n");
    for (int colonne=0; colonne<C; colonne++){
        for (int ligne=0; ligne<L; ligne++){
            printf("Saisissez la valeure de la ligne %d de la colonne %d", ligne+1, colonne+1);
            scanf("%d", &value);
            insert_value(*(cdataframe->columns + colonne), value);
        }
    }
}