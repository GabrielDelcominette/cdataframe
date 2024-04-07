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
        cdataframe->columns = (COLUMN **) malloc(REALLOC_COL_NUMBER * sizeof(COLUMN *));
        cdataframe->TP += REALLOC_COL_NUMBER;
    }
    if (cdataframe->columns == NULL){
        return 0;
    }
    if (cdataframe->TL == cdataframe->TP){
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
            printf("On insère la valeur à %d, %d - %d - %d", colonne, ligne, cdataframe->columns[colonne]->data[ligne], value);
        }
    }
}

void display_titles(CDATAFRAME * cdataframe){
    for (int i=0; i<cdataframe->TL; i++){
        printf("%s\t", cdataframe->columns[i]->title);
    }
}


void display_whole_cdataframe(CDATAFRAME * cdataframe){
    display_titles(cdataframe); // affichages des titles des colonnes en première ligne de la cdataframe
    for (int j=0; j<cdataframe->columns[0]->TL; j++) {
        printf("\n");
        for (int i = 0; i < cdataframe->TL; i++) {
            printf("%d\t\t", cdataframe->columns[i]->data[j]);
        }
    }
}


void display_cdataframe(CDATAFRAME * cdataframe, int start_column, int start_row, int end_column, int end_row) {
    if (start_column < 1 || start_row < 1 || start_column>end_column || start_row>end_row || end_column > cdataframe->TL || end_row > cdataframe->columns[0]->TL){
        printf("ERREUR : les indices entrées sont impossibles !");
    }
    else{
        for (int i=start_column-1; i<end_column; i++){
            printf("%s\t", cdataframe->columns[i]->title);
        }
        for (int j=start_row-1; j<end_row-1; j++) {
            printf("\n");
            for (int i = start_column - 1; i < end_column; i++) {
                printf("%d\t\t", cdataframe->columns[i]->data[j]);
            }
        }
    }
}

void insert_row_cdataframe(CDATAFRAME * cdataframe){

}

void display_rows_number(CDATAFRAME * cdataframe){
    printf("Il y a %d lignes dans la cdataframe.\n", cdataframe->columns[0]->TL);
}

void display_columns_number(CDATAFRAME * cdataframe){
    printf("Il y a %d colonnes dans la cdataframe.\n", cdataframe->TL);
}

void cdataframe_rename_column(CDATAFRAME * cdataframe, char * new_title, int i_column){
    rename_column(cdataframe->columns[i_column - 1], new_title);
}