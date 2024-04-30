#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
#include "almost_perfect_dataframe.h"


int main(){
    AP_CDATAFRAME * cdf;
    AP_COLUMN * column;
    ENUM_TYPE type = 2;

    int val1 = 2, val2 = 4, val3 = 7, val4=31, val5=23;

    printf("coucou ceci est un test\n");
    column = AP_create_column(type, "cannard");
    printf("created\n");
    AP_insert_value(column, &val1);
    printf("premiere valeur, insere\n");
    AP_insert_value(column, &val2);
    printf("deuxième valeur insere\n");
    AP_insert_value(column, &val3);
    printf("troisième valeur insere\n");
    AP_insert_value(column, &val4);
    AP_insert_value(column, &val5);
    printf("%s %d %d %d %d %d\n", column->title, column->data[0]->int_value, column->data[1]->int_value, column->data[2]->int_value, column->data[3]->int_value, column->data[4]->int_value);

    printf("coucou ceci est un test\n");
    cdf = AP_create_cdataframe();
    printf("cdf crééé\n");
    AP_read_cdataframe_user(cdf);
    printf("valeur inséréessss\n");
    printf("%d \n", cdf->columns[0]->data[1]->int_value);
    AP_display_whole_cdataframe(cdf);
    return 0;
}