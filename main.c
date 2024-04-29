#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
#include "almost_perfect_dataframe.h"


int main(){
    AP_CDATAFRAME * cdf;
    AP_COLUMN * column;
    ENUM_TYPE type = 2;

    int val1 = 2, val2 = 4;

    column = AP_create_column(type, "cannard");
    AP_insert_value(column, &val1);
    AP_insert_value(column, &val2);
    printf("%s %d %d\n", column->title, column->data[0]->int_value, column->data[1]->int_value);

    printf("coucou ceci est un test\n");
    cdf = AP_create_cdataframe();
    AP_read_cdataframe_user(cdf);
    AP_
    return 0;
}