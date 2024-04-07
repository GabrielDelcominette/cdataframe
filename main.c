#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"


int main(){
    CDATAFRAME * cdf;
    COLUMN * column;

    column = create_column("cannard");
    insert_value(column, 2);
    insert_value(column, 4);
    printf("%s %d %d\n", column->title, *(column->data), *(column->data+1));

    printf("coucou ceci est un test\n");
    cdf = create_cdataframe();
    read_cdataframe_user(cdf);
    printf("%s %d\n", (*cdf->columns)->title, *((*cdf->columns)->data));
    printf("%s %d\n", (cdf->columns[1])->title, *((*cdf->columns)->data));
    printf("%s %d\n", (cdf->columns[0])->title, *((*cdf->columns)->data));
    printf("%s %d\n", (*(cdf->columns+1))->title, *((*cdf->columns)->data));
    display_cdataframe(cdf, 1, 1, 2, 2);
    return 0;
}