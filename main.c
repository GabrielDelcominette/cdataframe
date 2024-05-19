#include <stdio.h>
#include "column.h"
#include "cdataframe.h"

int main(void) {
    char title[20];
    COLUMN * column = NULL;
    int i;
    CDATAFRAME* cdataframe = create_cdataframe("my_cdataframe");
    CDATAFRAME* cdataframe2 = create_cdataframe("my_cdataframe2");
    /**
    // Remplissage par colonnes
    for (i = 0; i < 2; i++){
        printf("\nsaisir le nom de la nouvelle colonne : ");
        scanf(" %s", &title);
        column = create_column(title);
        insert_columns(cdataframe, column);
    }
    fill_cdataframe(cdataframe, 2);
    print_cdataframe(*cdataframe);
    delete_line(cdataframe, 1);
    print_cdataframe(*cdataframe);
    **/
    // Remplissage par lignes
    for (i = 0; i < 2; i++){
        printf("\nsaisir le nom de la nouvelle colonne : ");
        scanf(" %s", &title);
        column = create_column(title);
        fill_column(column, 2);
        insert_columns(cdataframe, column);
    }
    print_cdataframe(*cdataframe2);
    return 0;
}
