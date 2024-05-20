#include "menu.h"
#include"column.h"
#include "cdataframe.h"
#include "almost_perfect_dataframe.h"
#include <stdio.h>

int main_menu() {
    int answ = 0;
    printf("\n\n\n");
    printf("\n======================");
    printf("\n*** MENU PRINCIPAL ***");
    printf("\n======================");
    printf("\n");
    printf("\nPour un dataframe d'entiers, appuyez sur 1 ");
    printf("\nPour un dataframe de tous types, appuyez sur 2 ");
    printf("\nPour quitter, appuyez sur 3 ");
    printf("\n>>>");
    scanf(" %d", &answ);
    if (answ == 1) menu_dataframe();
    else if (answ == 2) return 0;
    else if (answ == 3) return 1;
    else {
        printf("/!\\ ERREUR, RETOUR AU MENU PRINCIPAL");
        main_menu();
    }
    return 0;
}


void menu_dataframe() {
    printf("\n\n\n");
    printf("\n*** DATAFRAME D'ENTIERS ***");
    printf("\n");
    printf("\nPour creer un nouveau cdataframe, appuyez sur 1 ");
    printf("\nPour quitter appuyez sur 2 ");
    printf("\n>>>");
    int answ = 0;
    scanf(" %d", &answ);
    if (answ == 1) menu_create_dataframe();
    else if (answ == 2) main_menu();
    else {
        printf("/!\\ ERREUR, RETOUR AU MENU PRINCIPAL");
        main_menu();
    }
}


void menu_create_dataframe() {
    int nb_line, nb_col;
    CDATAFRAME* cdataframe = create_cdataframe();
    printf("\n");
    printf("\nSaisir les dimensions du cdataframe: ");
    printf("\n>lignes : ");
    scanf(" %d", &nb_line);
    printf("\n>colonnes : ");
    scanf(" %d", &nb_col);
    printf("\n");
    fill_cdataframe_c_by_c(cdataframe, nb_col, nb_line);
    display_whole_cdataframe(cdataframe);
    commands_dataframe(cdataframe);
}


void commands_dataframe(CDATAFRAME* cdataframe) {
    char command[50];
    int indice;
    int startcol, startrow, endcol, endrow;
    int value;
    int i,j;
    printf("\ncommandes existantes : "
           "\n/quit : retour au menu principal"
           "\n/help : affichage des commandes disponibles"
           "\n/addcol : ajoute une colonne au dataframe"
           "\n/addrow : ajoute une ligne au dataframe"
           "\n/delcol : supprime une colonne d'indice i"
           "\n/delrow : supprime une ligne d'indice i"
           "\n/dataframe : affiche le dataframe en entier"
           "\n/dataframelimits : affiche le dataframe avec une limites de lignes et colonnes"
           "\n/rownb : affiche le nombre de lignes"
           "\n/colnb : affiche le nombre de colonnes"
           "\n/titles : affiche les titres des colonnes"
           "\n/val : affiche la valeur à i,j"
           "\n/searchval : recherche d'une valeur choisie"
           "\n/nbhival : nombre de valeurs superieures à celle choisie"
           "\n/nbloval : nombre de valeurs inferieurs à celle choisie"
           "\n/nbeqval : nombre de valeurs égales à celle choisie"
           "\n/changeval : change la valeur i,j par une choisie");
    do {
        printf("\n\n>Entrez une commande a effectuer : ");
        scanf(" %s", command);
        printf("\n");
        if (command == "/help") {
            printf("\ncommandes existantes : "
           "\n/quit : retour au menu principal"
           "\n/help : affichage des commandes disponibles"
           "\n/addcol : ajoute une colonne au dataframe"
           "\n/addrow : ajoute une ligne au dataframe"
           "\n/delcol : supprime une colonne d'indice i"
           "\n/delrow : supprime une ligne d'indice i"
           "\n/dataframe : affiche le dataframe en entier"
           "\n/dataframelimits : affiche le dataframe avec une limites de lignes et colonnes"
           "\n/rownb : affiche le nombre de lignes"
           "\n/colnb : affiche le nombre de colonnes"
           "\n/titles : affiche les titres des colonnes"
           "\n/val : affiche la valeur à i,j"
           "\n/searchval : recherche d'une valeur choisie"
           "\n/nbhival : nombre de valeurs superieures à celle choisie"
           "\n/nbloval : nombre de valeurs inferieurs à celle choisie"
           "\n/nbeqval : nombre de valeurs égales à celle choisie"
           "\n/changeval : change la valeur i,j par une choisie");
        }
        else if (command == "/addcol") {
            char title[50];
            COLUMN* column = create_column(title);
            fill_column(column, cdataframe->TL);
            insert_column(cdataframe, column);
        }
        else if (command == "/addrow") {
            insert_row(cdataframe);
        }
        else if(command == "/delcol") {
            printf("\n>Saisir le numero de la colonne a supprimer : ");
            scanf(" %d", &indice);
            delete_column(cdataframe, indice);
        }
        else if(command == "/delrow") {
            printf("\n>Saisir le numero de la ligne a supprimer : ");
            scanf(" %d", &indice);
            delete_row(cdataframe, indice);
        }
        else if(command == "/dataframe") {
            display_whole_cdataframe(cdataframe);
        }
        else if(command == "/dataframelimits") {
            printf("\n>Saisir les indices des colonnes et lignes de début, olonnes et lignes de fin "
                         "\n sous la forme :start_col start_row end_col end_row : ");
            scanf(" %d %d %d %d", &startcol, &startrow, &endcol, &endrow);
            display_cdataframe(cdataframe, startcol, startrow, endcol, endrow);
        }
        else if(command == "/rownb") {
            display_rows_number(cdataframe);
        }
        else if(command == "/colnb") {
            display_columns_number(cdataframe);
        }
        else if(command == "/title") {
            display_titles(cdataframe);
        }
        else if(command == "/val") {
            printf("\n>Saisir les indices de recherche sous la forme: col row: ");
            scanf(" %d %d", &i, &j);
            find_value(cdataframe, i, j);
        }
        else if(command == "/searchval") {
            printf("\n>Saisir une valeur à rechercher : ");
            scanf(" %d", &value);
            is_value_in(cdataframe, value);
        }
        else if(command == "/nbhival") {
            printf("\n>Saisir une valeur à comparer : ");
            scanf(" %d", &value);
            n_higher_values(cdataframe, value);
        }
        else if(command == "/nbloval") {
            printf("\n>Saisir une valeur à comparer : ");
            scanf(" %d", &value);
            n_lower_values(cdataframe, value);
        }
        else if(command == "/nbeqval") {
            printf("\n>Saisir une valeur à comparer : ");
            scanf(" %d", &value);
            n_equals_values(cdataframe, value);
        }
        else if(command == "/changeval") {
            printf("\n>Saisir les indices de la valeur à changer sous la forme: col row: ");
            scanf(" %d %d", &i, &j);
            printf(">Saisir une valeur : ");
            scanf(" %d", &value);
            change_cell_value(cdataframe, value, i, j);
        }
    } while (command!="/quit");
    main_menu();
}