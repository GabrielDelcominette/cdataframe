#include "menu.h"
#include <stdio.h>
#include "column.h"

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
    else if (answ == 2) menu_AP_dataframe();
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
           "\n/val : affiche la valeur a i,j"
           "\n/searchval : recherche d'une valeur choisie"
           "\n/nbhival : nombre de valeurs superieures a celle choisie"
           "\n/nbloval : nombre de valeurs inferieurs a celle choisie"
           "\n/nbeqval : nombre de valeurs égales a celle choisie"
           "\n/changeval : change la valeur i,j par une choisie");
    do {
        printf("\n\n>Entrez une commande a effectuer : ");
        scanf(" %s", command);
        printf("\n");
        if (comparate_string(command,"/help") == 0) {
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
           "\n/val : affiche la valeur a i,j"
           "\n/searchval : recherche d'une valeur choisie"
           "\n/nbhival : nombre de valeurs >= a celle choisie"
           "\n/nbloval : nombre de valeurs <= a celle choisie"
           "\n/nbeqval : nombre de valeurs = a celle choisie"
           "\n/changeval : change la valeur i,j par une choisie");
        }
        else if (comparate_string(command,"/addcol") == 0) {
            char title[50];
            printf("\n>Entrez le titre de la nouvelle colonne : ");
            scanf(" %s", title);
            COLUMN* column = create_column(title);
            fill_column(column, cdataframe->columns[0]->TL);
            insert_column(cdataframe, column);
        }
        else if (comparate_string(command,"/addrow") == 0) {
            insert_row(cdataframe);
        }
        else if (comparate_string(command,"/delcol") == 0) {
            printf("\n>Saisir le numero de la colonne a supprimer : ");
            scanf(" %d", &indice);
            delete_column(cdataframe, indice);
        }
        else if (comparate_string(command,"/delrow") == 0) {
            printf("\n>Saisir l'indice de la ligne a supprimer : ");
            scanf(" %d", &indice);
            delete_row(cdataframe, indice);
        }
        else if (comparate_string(command,"/dataframe") == 0) {
            display_whole_cdataframe(cdataframe);
        }
        else if (comparate_string(command,"/dataframelimits") == 0) {
            printf("\n>Saisir les indices des colonnes et lignes de début, olonnes et lignes de fin "
                         "\n sous la forme :start_col start_row end_col end_row : ");
            scanf(" %d %d %d %d", &startcol, &startrow, &endcol, &endrow);
            display_cdataframe(cdataframe, startcol, startrow, endcol, endrow);
        }
        else if (comparate_string(command,"/rownb") == 0) {
            display_rows_number(cdataframe);
        }
        else if (comparate_string(command,"/colnb") == 0) {
            display_columns_number(cdataframe);
        }
        else if (comparate_string(command,"/titles") == 0) {
            display_titles(cdataframe);
        }
        else if (comparate_string(command,"/val") == 0) {
            printf("\n>Saisir les indices de recherche sous la forme: col row: ");
            scanf(" %d %d", &i, &j);
            printf("\n>Valeur : %d", find_value(cdataframe, i, j));
        }
        else if (comparate_string(command,"/searchval") == 0) {
            printf("\n>Saisir une valeur à rechercher : ");
            scanf(" %d", &value);
            is_value_in(cdataframe, value);
        }
        else if (comparate_string(command,"/nbhival") == 0) {
            printf("\n>Saisir une valeur à comparer : ");
            scanf(" %d", &value);
            n_higher_values(cdataframe, value);
        }
        else if (comparate_string(command,"/nbloval") == 0) {
            printf("\n>Saisir une valeur à comparer : ");
            scanf(" %d", &value);
            n_lower_values(cdataframe, value);
        }
        else if (comparate_string(command,"/nbeqval") == 0) {
            printf("\n>Saisir une valeur à comparer : ");
            scanf(" %d", &value);
            n_equals_values(cdataframe, value);
        }
        else if (comparate_string(command,"/changeval") == 0) {
            printf("\n>Saisir les indices de la valeur à changer sous la forme: col row: ");
            scanf(" %d %d", &i, &j);
            printf(">Saisir une valeur : ");
            scanf(" %d", &value);
            change_cell_value(cdataframe, value, i, j);
        }
    } while (comparate_string(command,"/quit") != 0);
    printf("\n==============================");
    main_menu();
}


void menu_AP_dataframe() {
    printf("\n\n\n");
    printf("\n*** DATAFRAME A TYPE MULTIPLE ***");
    printf("\n");
    printf("\nPour creer un nouveau cdataframe, appuyez sur 1 ");
    printf("\nPour quitter appuyez sur 2 ");
    printf("\n>>>");
    int answ = 0;
    scanf(" %d", &answ);
    if (answ == 1) menu_create_AP_dataframe();
    else if (answ == 2) main_menu();
    else {
        printf("/!\\ ERREUR, RETOUR AU MENU PRINCIPAL");
        main_menu();
    }
}


void menu_create_AP_dataframe() {
    AP_CDATAFRAME* ap_cdataframe = AP_create_cdataframe();
    AP_read_cdataframe_user(ap_cdataframe);
    AP_display_whole_cdataframe(ap_cdataframe);
    commands_AP_dataframe(ap_cdataframe);
}


void commands_AP_dataframe(AP_CDATAFRAME* ap_cdataframe) {
    char command[50];
    int indice, i, j;
    int startcol, startrow, endcol, endrow;
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
           "\n/val : affiche la valeur a i,j"
           "\n/searchval : recherche d'une valeur choisie"
           "\n/nbhival : nombre de valeurs superieures a celle choisie"
           "\n/nbloval : nombre de valeurs inferieurs a celle choisie"
           "\n/nbeqval : nombre de valeurs égales a celle choisie"
           "\n/changeval : change la valeur i,j par une choisie");
    do {
        printf("\n\n>Entrez une commande a effectuer : ");
        scanf(" %s", command);
        printf("\n");
        if (comparate_string(command,"/help") == 0) {
            printf("\ncommandes existantes : "
           "\n/quit : retour au menu principal"
           "\n/help : affichage des commandes disponibles"
           "\n/addcol : ajoute une colonne au dataframe"
           "\n/addrow : ajoute une ligne au dataframe"
           "\n/delcol : supprime une colonne d'indice i"
           "\n/delrow : supprime une ligne d'indice i"
           "\n/dataframe : affiche le dataframe en entier"
           "\n/titles : affiche les titres des colonnes"
           "\n/sortdataframe : trie le dataframe");
        }
        else if (comparate_string(command,"/addcol") == 0) {
            char title[50];
            ENUM_TYPE type = 1;
            printf("\n>Entrez le titre de la colonne : ");
            scanf(" %s", title);
            printf("\n>Entrez le type de la colonne "
                   "\n(1 = UINT; 2 = INT; 3 = CHAR; 4 = FLOAT; 5 = DOUBLE; 6 = STRING");
            printf("\n>>>");
            scanf(" %d", &type);
            AP_COLUMN* column = AP_create_column(type, title);
            while (column->TL<ap_cdataframe->columns[0]->TL) {
                switch (column->column_type) {
                    case UINT: {
                        printf("\n>Saisir un entier non signe : ");
                        unsigned int value;
                        scanf(" %u", &value);
                        AP_insert_value(column, &value);
                        break;
                    }
                    case INT: {
                        printf("\n>Saisir un entier : ");
                        int value;
                        scanf(" %d", &value);
                        AP_insert_value(column, &value);
                        break;

                    }
                    case CHAR: {
                        printf("\n>Saisir un caractere : ");
                        char value;
                        scanf(" %c", &value);
                        AP_insert_value(column, &value);
                        break;
                    }
                    case FLOAT: {
                        printf("\n>Saisir un decimal : ");
                        float value;
                        scanf(" %f", &value);
                        AP_insert_value(column, &value);
                        break;
                    }
                    case DOUBLE: {
                        printf("\n>Saisir un double : ");
                        double value;
                        scanf(" %lf", &value);
                        AP_insert_value(column, &value);
                        break;
                    }
                    case STRING: {
                        printf("\n>Saisir une chaine de caracteres : ");
                        char value[50];
                        scanf(" %s", value);
                        AP_insert_value(column, value);
                        break;
                    }
                }
            }
            AP_insert_column(ap_cdataframe, column);
        }
        else if(comparate_string(command,"/dataframe") == 0) {
            AP_display_whole_cdataframe(ap_cdataframe);
        }
        else if(comparate_string(command,"/addrow") == 0) {
            AP_insert_row(ap_cdataframe);
        }
        else if (comparate_string(command,"/delcol") == 0) {
            printf("\n>Saisir le numero de la colonne a supprimer : ");
            scanf(" %d", &indice);
            AP_delete_column_from_dataframe(ap_cdataframe, indice);
        }
        else if (comparate_string(command,"/delrow") == 0) {
            printf("\n>Saisir l'indice de la ligne a supprimer : ");
            scanf(" %d", &indice);
            AP_delete_row(ap_cdataframe, indice);
        }
        else if (comparate_string(command,"/titles")==0) {
            AP_display_titles(ap_cdataframe);
        }
        else if (comparate_string(command,"/sortdataframe") == 0) {
            AP_sort_dataframe(ap_cdataframe, 1);
            AP_display_sorted_cdataframe(ap_cdataframe, 1);
        }

    } while (comparate_string(command,"/quit") != 0);
    printf("\n==============================");
    main_menu();
}

