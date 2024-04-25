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
    int C, L;
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

    printf("\t\t ********* Entrer les valeurs dans les cellules ***********\n");
    for (int ligne=1; ligne<L+1; ligne++){
        printf("***** Saisir les valeurs de la ligne %d *****\n", ligne + 1);
        insert_row(cdataframe);
    }
}

void insert_row(CDATAFRAME * cdataframe){
    int value;
    for (int colonne=0; colonne<cdataframe->TL; colonne++){
        printf("Saisissez la valeure de la colonne %d : \n", colonne+1);
        scanf("%d", &value);
        insert_value(cdataframe->columns[colonne], value);
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


void display_rows_number(CDATAFRAME * cdataframe){
    printf("Il y a %d lignes dans la cdataframe.\n", cdataframe->columns[0]->TL);
}

void display_columns_number(CDATAFRAME * cdataframe){
    printf("Il y a %d colonnes dans la cdataframe.\n", cdataframe->TL);
}

void cdataframe_rename_column(CDATAFRAME * cdataframe, char * new_title, int i_column){
    rename_column(cdataframe->columns[i_column - 1], new_title);
}

int is_value_in(CDATAFRAME * cdataframe, int value){
    for (int i=0; i<cdataframe->TL; i++){
        for (int j=0; j<cdataframe->columns[0]->TL; j++){
            if (cdataframe->columns[i]->data[i] == value){
                return 1;
            }
        }
    }
    return 0;
}

int n_equals_values(CDATAFRAME * cdataframe, int value){
    int sum=0;
    for (int i=0; i<cdataframe->TL; i++){
        sum += column_n_equals_values(cdataframe->columns[i], value);
    }
    return sum;
}

int n_lower_values(CDATAFRAME * cdataframe, int value){
    int sum=0;
    for (int i=0; i<cdataframe->TL; i++){
        sum += column_n_lower_values(cdataframe->columns[i], value);
    }
    return sum;
}

int n_higher_values(CDATAFRAME * cdataframe, int value){
    int sum=0;
    for (int i=0; i<cdataframe->TL; i++){
        sum += column_n_higher_values(cdataframe->columns[i], value);
    }
    return sum;
}

int find_value(CDATAFRAME * cdataframe, int col, int row){
    return cdataframe->columns[col]->data[row];
}

void change_cell_value(CDATAFRAME * cdataframe, int new_value, int col, int row){
    cdataframe->columns[col-1]->data[row-1] = new_value;
}

void delete_column(CDATAFRAME * cdataframe, int col){
    if (col < 1 ||  col > cdataframe->TL) {
        printf("ERREUR : les indices entrées sont impossibles !");
    }
    else {
        COLUMN* tmp = cdataframe->columns[col - 1];
        for (int i = col; i < cdataframe->TL; i++) {
            cdataframe->columns[i - 1] = cdataframe->columns[i];
        }
        free_column(tmp);
    }
}

void delete_row(CDATAFRAME * cdataframe, int row){
    if (row < 1 ||  row > cdataframe->columns[0]->TL) {
        printf("ERREUR : les indices entrées sont impossibles !");
    }
    else{
        for (int i=0; i<cdataframe->TL; i++){
            for (int j=row; j<cdataframe->columns[0]->TL; j++){
                cdataframe->columns[i]->data[j-1] = cdataframe->columns[i]->data[j];
            }
            cdataframe->columns[i]->TL--;
        }
    }
}