#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
#include "almost_perfect_dataframe.h"


int main(){
    AP_CDATAFRAME * cdf;
    AP_COLUMN* column2, *column1, *column3;
    ENUM_TYPE type = 2, type2 = 3, type3=5;

    DATA_TYPE *data_type;
    data_type = (DATA_TYPE*) malloc(sizeof(DATA_TYPE));

    data_type->int_value = 5;
    data_type->double_value = 9.56;
    printf("OK\n");
    printf("Data_type : %d \n", * (int *) data_type);
    printf("Data_type : %lf \n", * (double *) data_type);

    int val1 = 2, val2 = 4, val3 = 7, val4=2, val5=23;
    char val6 = 'e', val7 = 'g', val8 = '2', val9 = 'e', val10 = 'f';
    double val11 = 2.0, val12 = 28.76, val13 = 7.8, val14 = 4.5, val15 = 4.5;

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
    AP_print_col(column1);

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
    AP_print_col(column2);

    column3 = AP_create_column(type3, "gabriel");
    printf("created\n");
    AP_insert_value(column3, &val11);
    printf("premiere valeur, insere\n");
    AP_insert_value(column3, &val12);
    printf("deuxième valeur insere\n");
    AP_insert_value(column3, &val13);
    printf("troisième valeur insere\n");
    AP_insert_value(column3, &val14);
    AP_insert_value(column3, &val15);
    AP_print_col(column3);

    cdf = AP_create_cdataframe();
    AP_insert_column(cdf, column1);
    AP_insert_column(cdf, column2);
    AP_insert_column(cdf, column3);
    AP_display_whole_cdataframe(cdf);
    printf("\n");
    printf("%c \n", AP_find_value(cdf, 4, 2)->char_value);

    char valeur = 'e';
    double valeur2 = 2;
    int valeur3 = 2;
    printf("La valeur apparait %d fois \n", AP_n_equals_values(cdf, &valeur3, type));
    return 0;
}