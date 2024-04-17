#include "almost_perfect_dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


AP_COLUMN* AP_create_column(ENUM_TYPE type, char * title){
    AP_COLUMN * column;
    column = (AP_COLUMN*) malloc(sizeof(AP_COLUMN));
    column->title = (char *) malloc(sizeof(char *) * (strlen(title) + 1));
    strcpy(column->title, title);
    column->TP = 0;
    column->TL = 0;
    column->column_type = type;
    column->data = NULL;
    column->index = NULL;
    return column;
}

int AP_insert_value(AP_COLUMN *col, void *value){
    int allocation = 0; // booléen, correspond à si l'on alloue de l'espace mémoire en plus
    if (col->data == NULL){
        // allocation du tableau de pointeur
        col->data = (DATA_TYPE **) malloc(REALOC_SIZE * sizeof(DATA_TYPE*));
        if (col->data == NULL) // dans le cas où l'allocation a échoué
            return 0;
        allocation = 1;
        col->TP += REALOC_SIZE;
    }

    if (col->TL == col->TP){
        DATA_TYPE ** tmp = col->data; // variable temporaire au cas où realoc ne fonctionnerait pas
        tmp = (DATA_TYPE **) realloc(tmp, (col->TP + REALOC_SIZE) * sizeof(DATA_TYPE*));
        if (tmp == NULL)
            return 0;
        allocation = 1;
        col->TP += REALOC_SIZE;
        col->data = tmp;
    }

    // allocation des tableaux sur lesquels pointes les pointeurs
    if (allocation) {
        for (int i = 0; i < REALOC_SIZE; i++) {
            col->data[i] = (DATA_TYPE *) malloc(sizeof(DATA_TYPE));
        }
    }

    if (col->TL < col->TP){
        value = (DATA_TYPE*) value; // on convertie le type de value
        col->data[col->TL] = value;
        col->TL+=1;
        return 1;
    }
    return 0;
}


void AP_delete_column(AP_COLUMN **col){
    free((*col)->title);
    for (int i = 0; i<(*col)->TP; i++){
        free((*col)->data[i]);
    }
    free((*col)->data);
    free(*col);
    free(col);
}

void AP_convert_value(ENUM_TYPE type, DATA_TYPE * value, char *str, int size){
    // Conversion de la valeur en chaîne de caractères en fonction de son type
    switch (type) {
        case UINT:
            snprintf(str, size, "%u", value->uint_value);
            break;
        case INT:
            snprintf(str, size, "%d", value->int_value);
            break;
        case CHAR:
            snprintf(str, size, "%c", value->char_value);
            break;
        case FLOAT:
            snprintf(str, size, "%f", value->float_value);
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", value->double_value);
            break;
        case STRING:
            strncpy(str, value->string_value, size - 1); // Copie de la chaîne dans le buffer
            str[size - 1] = '\0'; // Assure la terminaison de la chaîne
            break;
        default:
            snprintf(str, size, "Unsupported Type");
    }
}

void AP_print_col(AP_COLUMN* col){
    int max_size = 50;
    char string[max_size];
    for (int i=0; i<col->TL; i++) {
        AP_convert_value(col->column_type, col->data[i], string, max_size);
        printf("[%d] %s\n", i, string);
    }
}

DATA_TYPE * AP_find_value(AP_CDATAFRAME * ap_cdataframe, int ligne, int colonne){
    return ap_cdataframe->columns[colonne-1]->data[ligne-1];
}

int AP_n_equals_values(AP_CDATAFRAME * ap_cdataframe, DATA_TYPE * value){
    int sum=0;
    int size = 50;
    char str_value[size], str_col_value[size]; //initialisation des chaines de caractères associés à value et les valeurs des cellules
    for (int i=0; i<ap_cdataframe->TL; i++){
        AP_convert_value(ap_cdataframe->columns[i]->column_type, value, str_value, size);
        for (int j=0; j<ap_cdataframe->columns[0]->TL; j++){
            AP_convert_value(ap_cdataframe->columns[i]->column_type, ap_cdataframe->columns[i]->data[j], str_col_value, size);

            // on compare les deux chaines de caractères obtenues
            int x=0;
            while (str_col_value[x] == str_value[x] && str_col_value[x] != '\0' && str_value[x] != '\0')
                x++;
            if (str_col_value[x] == '\0' && str_value[x] == '\0')
                sum += 1;
        }
    }
    return sum;
}

int AP_n_lower_values(AP_CDATAFRAME * ap_cdataframe, DATA_TYPE * value){
    int sum=0;
    int size = 50;
    char str_value[size], str_col_value[size]; //initialisation des chaines de caractères associés à value et les valeurs des cellules
    for (int i=0; i<ap_cdataframe->TL; i++){
        AP_convert_value(ap_cdataframe->columns[i]->column_type, value, str_value, size);
        for (int j=0; j<ap_cdataframe->columns[0]->TL; j++){
            AP_convert_value(ap_cdataframe->columns[i]->column_type, ap_cdataframe->columns[i]->data[j], str_col_value, size);

            // on compare les deux chaines de caractères obtenues
            int x=0;
            while (str_col_value[x] == str_value[x] && str_col_value[x] != '\0' && str_value[x] != '\0')
                x++;
            if (str_col_value[x] == '\0'){
                if (str_value[x] != '\0'){
                    sum += 1;
                }
            }
            else{
                if (str_value[x] != '\0' && str_col_value[x] < str_value[x])
                    sum += 1;
            }
        }
    }
    return sum;
}

int AP_n_higher_values(AP_CDATAFRAME * ap_cdataframe, int value){
    int sum=0;
    int size = 50;
    char str_value[size], str_col_value[size]; //initialisation des chaines de caractères associés à value et les valeurs des cellules
    for (int i=0; i<ap_cdataframe->TL; i++){
        AP_convert_value(ap_cdataframe->columns[i]->column_type, value, str_value, size);
        for (int j=0; j<ap_cdataframe->columns[0]->TL; j++){
            AP_convert_value(ap_cdataframe->columns[i]->column_type, ap_cdataframe->columns[i]->data[j], str_col_value, size);

            // on compare les deux chaines de caractères obtenues
            int x=0;
            while (str_col_value[x] == str_value[x] && str_col_value[x] != '\0' && str_value[x] != '\0')
                x++;
            if (str_value[x] == '\0'){
                if (str_col_value[x] != '\0'){
                    sum += 1;
                }
            }
            else{
                if (str_col_value[x] != '\0' && str_col_value[x] > str_value[x])
                    sum += 1;
            }
        }
    }
    return sum;
}
