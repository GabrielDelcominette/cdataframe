#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"
#include "almost_perfect_dataframe.h"


int main(){
    AP_CDATAFRAME * cdf;
    AP_COLUMN* column2, *column1, *column3, *column4;
    ENUM_TYPE type = 5, type2 = 3, type3=2, type4 = 6;

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
    char* val16 = "stroumf", * val17 = "machin", * val18 = "truc", * val19="e", * val20 = "machin";

    printf("coucou ceci est un test\n");
    column1 = AP_create_column(type3, "Canard");
    AP_insert_value(column1, &val1);
    AP_insert_value(column1, &val2);
    AP_insert_value(column1, &val3);
    AP_insert_value(column1, &val4);
    AP_insert_value(column1, &val5);
    AP_print_col(column1);

    column2 = AP_create_column(type2, "Kong");
    AP_insert_value(column2, &val6);
    AP_insert_value(column2, &val7);
    AP_insert_value(column2, &val8);
    AP_insert_value(column2, &val9);
    AP_insert_value(column2, &val10);
    AP_print_col(column2);

    column3 = AP_create_column(type, "Gabriel");
    AP_insert_value(column3, &val11);
    AP_insert_value(column3, &val12);
    AP_insert_value(column3, &val13);
    AP_insert_value(column3, &val14);
    AP_insert_value(column3, &val15);
    AP_print_col(column3);

    column4 = AP_create_column(type4, "Etienne");
    AP_insert_value(column4, val16);
    AP_insert_value(column4, val17);
    AP_insert_value(column4, val18);
    AP_insert_value(column4, val19);
    AP_insert_value(column4, val20);
    AP_print_col(column4);

    cdf = AP_create_cdataframe();
    AP_insert_column(cdf, column1);
    AP_insert_column(cdf, column2);
    AP_insert_column(cdf, column3);
    AP_insert_column(cdf, column4);
    AP_print_col(cdf->columns[3]);
    AP_display_whole_cdataframe(cdf);
    printf("\n");
    printf("%c \n", AP_find_value(cdf, 4, 2)->char_value);

    char valeur2 = 'e';
    double valeur = 2;
    int valeur3 = 2;
    char * valeur4 = "machin";
    char * valeur4bis = "e";
    printf("La valeur 1 apparait %d fois \n", AP_n_equals_values(cdf, &valeur, type));
    printf("La valeur 2 apparait %d fois \n", AP_n_equals_values(cdf, &valeur2, type2));
    printf("La valeur 3 apparait %d fois \n", AP_n_equals_values(cdf, &valeur3, type3));
    printf("La valeur 4 apparait %d fois \n", AP_n_equals_values(cdf, valeur4, type4));
    printf("La valeur 4bis apparait %d fois \n", AP_n_equals_values(cdf, valeur4bis, type4));

    AP_display_whole_cdataframe(cdf);
    AP_sort_dataframe(cdf, 1);
    AP_display_whole_cdataframe(cdf);
    AP_display_sorted_cdataframe(cdf, 1);
    AP_display_sorted_cdataframe(cdf, 2);
    AP_display_sorted_cdataframe(cdf, 3);
    AP_display_sorted_cdataframe(cdf, 4);

    return 0;
}