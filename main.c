#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
#include "almost_perfect_dataframe.h"


int main(){
    AP_CDATAFRAME * cdf;
    AP_COLUMN* column2, *column1;
    ENUM_TYPE type = 2, type2 = 3;

    int val1 = 2, val2 = 4, val3 = 7, val4=31, val5=23;
    char val6 = 'c', val7 = 'g', val8 = 'q', val9 = 'e', val10 = 'f';

    printf("coucou ceci est un test\n");
    column1 = AP_create_column(type, "cannard");
    printf("created\n");
    AP_insert_value(column1, &val1);
    printf("premiere valeur, insere\n");
    AP_insert_value(column1, &val2);
    printf("deuxième valeur insere\n");
    AP_insert_value(column1, &val3);
    printf("troisième valeur insere\n");
    AP_insert_value(column1, &val4);
    AP_insert_value(column1, &val5);

    column2 = AP_create_column(type2, "ching");
    printf("created\n");
    AP_insert_value(column2, &val6);
    printf("premiere valeur, insere\n");
    AP_insert_value(column2, &val7);
    printf("deuxième valeur insere\n");
    AP_insert_value(column2, &val8);
    printf("troisième valeur insere\n");
    AP_insert_value(column2, &val9);
    AP_insert_value(column2, &val10);

    cdf = AP_create_cdataframe();
    AP_insert_column(cdf, column1);
    AP_insert_column(cdf, column2);
    AP_display_whole_cdataframe(cdf);
    printf("\n");
    printf("%c \n", AP_find_value(cdf, 4, 2)->char_value);

    char valeur = 'e';
    printf("La valeur apparait %d fois \n", AP_n_equals_values(cdf, &valeur));
    return 0;
}