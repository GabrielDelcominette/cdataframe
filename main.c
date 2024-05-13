#include <stdio.h>
#include "column.h"
#include "cdataframe.h"

int main(void) {
    char title[20];
    COLUMN * column = NULL;
    int i;
    CDATAFRAME* cdataframe = create_cdataframe("my_cdataframe");
    for (i = 0; i < 3; i++){
        printf("\nsaisir le nom de la nouvelle colonne : ");
        scanf(" %s ", title);
        column = create_column(title);
        insert_columns(cdataframe, column);
    }
    add_lines_cdataframe(cdataframe, 3);
    print_cdataframe(*cdataframe);
    return 0;
}
