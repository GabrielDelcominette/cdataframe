#include "almost_perfect_dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparate_string(char* string1, char* string2){
    int x = 0;
    while (string1[x] == string2[x] && string1[x] != '\0' && string2[x] != '\0')
        x++;
    if (string1[x] == '\0' && string2[x] == '\0')
        return 0;
    else{
        if (string1[x] == '\0' || string1[x] < string2[x])
            return -1;
        else
            return 1;
    }
}

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
    column->valid_index = 0;
    column->sort_dir = 0;
    return column;
}

AP_CDATAFRAME* AP_create_cdataframe(){
    AP_CDATAFRAME * dataframe;
    dataframe = (AP_CDATAFRAME*) malloc(sizeof(AP_CDATAFRAME));
    dataframe->TP = 0;
    dataframe->TL = 0;
    dataframe->columns = NULL;
    return dataframe;
}

int AP_insert_value(AP_COLUMN *col, void *value){
    int allocation = 0; // booléen, correspond à si l'on alloue de l'espace mémoire en plus
    if (col->data == NULL){
        // allocation du tableau de pointeur et du tableau d'indice
        col->data = (DATA_TYPE **) malloc(REALOC_SIZE * sizeof(DATA_TYPE*));
        col->index = (unsigned long long int *) malloc(REALOC_SIZE * sizeof(unsigned long long int));
        if (col->data == NULL || col->index == NULL){ // dans le cas où une des deux allocation a échoué
            free(col->data);
            free(col->index); // on libère les deux tableaux car un a peut-être de l'espace alloué
            col->data = NULL; // on réassigne la valeur NULL aux pointeurs dont l'allocation a échoué
            col->index = NULL;
            return 0;}
        allocation = 1;
        col->TP += REALOC_SIZE;
    }

    if (col->TL == col->TP){
        // variable temporaire au cas où realoc ne fonctionnerait pas
        DATA_TYPE ** tmp = col->data;
        unsigned long long int * tmp2 = col->index;
        tmp = (DATA_TYPE **) realloc(tmp, (col->TP + REALOC_SIZE) * sizeof(DATA_TYPE*));
        tmp2 = (unsigned long long int *) realloc(tmp2, (col->TP + REALOC_SIZE) * sizeof(unsigned long long int));
        if (tmp == NULL || tmp2 == NULL){ // si une des deux allocations a échoué
            return 0;}
        allocation = 1;
        col->TP += REALOC_SIZE;
        col->data = tmp;
        col->index = tmp2;
    }

    // allocation des tableaux sur lesquels pointent les pointeurs (col->data)
    if (allocation) {
        for (unsigned int i = col->TP - REALOC_SIZE; i < col->TP; i++) {
            col->data[i] = (DATA_TYPE *) malloc(sizeof(DATA_TYPE));
        }
    }

    if (col->TL < col->TP){
        value = (DATA_TYPE*) value; // on convertie le type de value
        col->data[col->TL] = value;
        col->index[col->TL] = col->TL; // on assigne un index à la valeur
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

int AP_insert_column(AP_CDATAFRAME * cdataframe, AP_COLUMN * col){
    if (cdataframe->columns == NULL){
        cdataframe->columns = (AP_COLUMN **) malloc(REALLOC_COL_NUMBER * sizeof(AP_COLUMN *));
        cdataframe->TP += REALLOC_COL_NUMBER;
    }
    if (cdataframe->columns == NULL){
        return 0;
    }
    if (cdataframe->TL == cdataframe->TP){
        AP_COLUMN ** tmp = cdataframe->columns; // variable temporaire au cas où realoc ne fonctionnerait pas
        tmp = (AP_COLUMN **) realloc(tmp, (cdataframe->TP + REALLOC_COL_NUMBER) * sizeof(AP_COLUMN *));
        if (tmp != NULL) {
            cdataframe->TP += REALLOC_COL_NUMBER;
            cdataframe->columns = tmp;
        }
        else
            return 0;
    }
    if (cdataframe->TL < cdataframe->TP){
        //*(cdataframe->columns + cdataframe->TL) = col;
        cdataframe->columns[cdataframe->TL] = col;
        cdataframe->TL+=1;
        return 1;
    }
    return 0;
}

void AP_insert_row(AP_CDATAFRAME * cdataframe){
    for (int colonne=0; colonne<cdataframe->TL; colonne++){
        switch (cdataframe->columns[colonne]->column_type) {
            case UINT:
            {
                unsigned int * value = NULL;
                printf("Saisissez la valeure de la colonne %d : \n", colonne+1);
                scanf("%u", value);
                AP_insert_value(cdataframe->columns[colonne], value);
                break;}
            case INT:
            {
                int * value = NULL;
                printf("Saisissez la valeure de la colonne %d : \n", colonne+1);
                scanf("%d", value);
                AP_insert_value(cdataframe->columns[colonne], value);
                break;}
            case CHAR:
            {
                char * value = NULL;
                printf("Saisissez la valeure de la colonne %d : \n", colonne+1);
                scanf("%c", value);
                AP_insert_value(cdataframe->columns[colonne], value);
                break;}
            case FLOAT:
            {
                float * value = NULL;
                printf("Saisissez la valeure de la colonne %d : \n", colonne+1);
                scanf("%f", value);
                AP_insert_value(cdataframe->columns[colonne], value);
                break;}
            case DOUBLE:
            {
                double * value = NULL;
                printf("Saisissez la valeure de la colonne %d : \n", colonne+1);
                scanf("%lf", value);
                AP_insert_value(cdataframe->columns[colonne], value);
                break;}
            case STRING:
            {
                char * value = NULL;
                printf("Saisissez la valeure de la colonne %d : \n", colonne+1);
                scanf("%s", value);
                AP_insert_value(cdataframe->columns[colonne], value);
                break;}
        }
    }
}

void AP_read_cdataframe_user(AP_CDATAFRAME * cdataframe) {
    int C, L;
    char name[50];
    AP_COLUMN* new_column = NULL;
    //new_column = (COLUMN**) malloc(sizeof(COLUMN **));
    //new_column= (COLUMN*) malloc(sizeof(COLUMN *));
    printf("saisissez le nombres de colonnes de la cdataframe : \n");
    scanf(" %d", &C);
    printf("saisissez le nombres de lignes de la cdataframe : \n");
    scanf(" %d", &L);
    printf("\t\t********** Entrez les titres et les types des colonnes *********\n");
    for (int i=0; i<C; i++){
        int tmp_type;
        printf("Saisissez le type de la colonne :\n\t1 pour UNINT\n\t2 pour INT\n\t3 pour CHAR\n\t4 pour FLOAT\n\t5 pour DOUBLE\n\t6 pour STRING");
        scanf(" %d", &tmp_type);
        printf("Saisissez le titre de la colonnes %d : \n", i+1);
        scanf(" %s", name);
        new_column = AP_create_column(tmp_type, name); // création d'une nouvelle colonne ayant pour titre celui entré par l'utilisateur
        AP_insert_column(cdataframe, new_column); // on ajoute la nouvelle colonne à la cdataframe
    }
    for (int i=0; i<C; i++){
        //printf("Voici la nouvelle colone %s en position %d\n", (cdataframe->columns[i])->title, i);
    }

    printf("\t\t ********* Entrer les valeurs dans les cellules ***********\n");
    for (int ligne=1; ligne<L+1; ligne++){
        printf("***** Saisir les valeurs de la ligne %d *****\n", ligne + 1);
        AP_insert_row(cdataframe);
    }
}

void AP_display_titles(AP_CDATAFRAME * cdataframe){
    for (int i=0; i<cdataframe->TL; i++){
        printf("%s\t", cdataframe->columns[i]->title);
    }
}


void AP_display_whole_cdataframe(AP_CDATAFRAME * cdataframe){
    AP_display_titles(cdataframe); // affichages des titles des colonnes en première ligne de la cdataframe
    for (int j=0; j<cdataframe->columns[0]->TL; j++) {
        printf("\n"); // avant d'afficher les valeurs de la ligne, on revient à la ligne
        for (int i = 0; i < cdataframe->TL; i++) { // pour chaque colonne de la ligne
            switch (cdataframe->columns[i]->column_type) {
                // On affiche la valeur en fonction de son type
                case UINT:
                    printf("%u\t\t", *(unsigned int*) cdataframe->columns[i]->data[j]);
                    break;
                case INT:
                    printf("%d\t\t", *(int*) cdataframe->columns[i]->data[j]);
                    break;
                case CHAR:
                    printf("%c\t\t", *(char*) cdataframe->columns[i]->data[j]);
                    break;
                case FLOAT:
                    printf("%f\t\t", *(float*) cdataframe->columns[i]->data[j]);
                    break;
                case DOUBLE:
                    printf("%lf\t\t", *(double*) cdataframe->columns[i]->data[j]);
                    break;
                case STRING:
                    printf("%s\t\t", (char*) cdataframe->columns[i]->data[j]);
                    break;
            }
        }
    }
}

DATA_TYPE * AP_find_value(AP_CDATAFRAME * ap_cdataframe, int ligne, int colonne){
    return ap_cdataframe->columns[colonne-1]->data[ligne-1];
}

int AP_n_equals_values(AP_CDATAFRAME * ap_cdataframe, DATA_TYPE * value){
    int sum=0;
    int size = 50;
    char str_value[size]; //initialisation d'une chaine de caractères associés à value
    AP_convert_value(STRING, value, str_value, size);
    for (int i=0; i<ap_cdataframe->TL; i++) {
        switch (ap_cdataframe->columns[i]->column_type) {
            case (STRING):
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    // on compare les deux chaines de caractères
                    if (!comparate_string((char*) ap_cdataframe->columns[i]->data[j], str_value))
                        sum++;}
                break;
            case UINT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (unsigned int*) ap_cdataframe->columns[i]->data[j] == * (unsigned int*) value)
                        sum++;
                }
                break;
            case INT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (int*) ap_cdataframe->columns[i]->data[j] == * (int*) value)
                        sum++;
                }
                break;
            case CHAR:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (char*) ap_cdataframe->columns[i]->data[j] == * (char *) value)
                        sum++;
                }
                break;
            case FLOAT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (float*) ap_cdataframe->columns[i]->data[j] == * (float*) value)
                        sum++;
                }
                break;
            case DOUBLE:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (double*) ap_cdataframe->columns[i]->data[j] == * (double *) value)
                        sum++;
                }
                break;
        }
    }
    return sum;
}

int AP_n_lower_values(AP_CDATAFRAME * ap_cdataframe, DATA_TYPE * value){
    int sum=0;
    int size = 50;
    char str_value[size]; //initialisation d'une chaine de caractères associés à value
    AP_convert_value(STRING, value, str_value, size);
    for (int i=0; i<ap_cdataframe->TL; i++) {
        switch (ap_cdataframe->columns[i]->column_type) {
            case (STRING):
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    // on compare les deux chaines de caractères obtenues
                    if (comparate_string((char*) ap_cdataframe->columns[i]->data[j], str_value) == -1)
                        sum++;
                }
                break;
            case UINT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (unsigned int*) ap_cdataframe->columns[i]->data[j] < * (unsigned int*) value)
                        sum++;
                }
                break;
            case INT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (int*) ap_cdataframe->columns[i]->data[j] < * (int*) value)
                        sum++;
                }
                break;
            case CHAR:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (char*) ap_cdataframe->columns[i]->data[j] < * (char *) value)
                        sum++;
                }
                break;
            case FLOAT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (float*) ap_cdataframe->columns[i]->data[j] < * (float*) value)
                        sum++;
                }
                break;
            case DOUBLE:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (double*) ap_cdataframe->columns[i]->data[j] < * (double *) value)
                        sum++;
                }
                break;
        }
    }
    return sum;
}

int AP_n_higher_values(AP_CDATAFRAME * ap_cdataframe, DATA_TYPE * value){
    int sum=0;
    int size = 50;
    char str_value[size]; //initialisation d'une chaine de caractères associés à value
    AP_convert_value(STRING, value, str_value, size);
    for (int i=0; i<ap_cdataframe->TL; i++) {
        switch (ap_cdataframe->columns[i]->column_type) {
            case (STRING):
                for (int j=0; j<ap_cdataframe->columns[0]->TL; j++){
                    // on compare les deux chaines de caractères obtenues
                    if (comparate_string((char*) ap_cdataframe->columns[i]->data[j], str_value) == 1)
                        sum++;
                }
                break;
            case UINT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (unsigned int*) ap_cdataframe->columns[i]->data[j] > * (unsigned int*) value)
                        sum++;
                }
                break;
            case INT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (int*) ap_cdataframe->columns[i]->data[j] > * (int*) value)
                        sum++;
                }
                break;
            case CHAR:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (char*) ap_cdataframe->columns[i]->data[j] > * (char *) value)
                        sum++;
                }
                break;
            case FLOAT:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (float*) ap_cdataframe->columns[i]->data[j] > * (float*) value)
                        sum++;
                }
                break;
            case DOUBLE:
                for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                    if (* (double*) ap_cdataframe->columns[i]->data[j] > * (double *) value)
                        sum++;
                }
                break;
        }
    }
    return sum;
}


// définition d'une macro permettant de faire le trie par insertion d'une colonne quelque soit son type
// cette macro ne peut être appeler que dans insertion_sort()

#define INSERTION_SORT(TYPE) \
    for (int i = 1; i < col->TL; ++i) { \
        TYPE k = *((TYPE *)col->data[i]); \
        int j = i - 1;       \
        if (ascending){                  \
            while (j >= 0 && *((TYPE *)col->data[j]) > k) { \
                col->data[j + 1] = col->data[j];            \
                j = j - 1; \
        } \
        col->data[j + 1] = (DATA_TYPE *)&k;}            \
        else{                \
            while (j >= 0 && *((TYPE *)col->data[j]) < k) { \
                col->data[j + 1] = col->data[j];            \
                j = j - 1; }}}

void insertion_sort(AP_COLUMN * col, int ascending){
    switch (col->column_type){
        case INT:
            INSERTION_SORT(int)
            break;
        case UINT:
            INSERTION_SORT(unsigned int)
            break;
        case CHAR:
            INSERTION_SORT(char)
            break;
        case FLOAT:
            INSERTION_SORT(float)
            break;
        case DOUBLE:
            INSERTION_SORT(double)
            break;
        default:
            return;
    }
}

void insertion_string_sort(AP_COLUMN * col, int ascending){
    for (int i = 1; i < col->TL; ++i) {
        DATA_TYPE *k = col->data[i];
        int j = i - 1;

        if (ascending){
            while (j >= 0 && comparate_string((char *) col->data[j], (char*) k) == 1) {
                col->data[j + 1] = col->data[j];
                j = j - 1;
            }
            col->data[j + 1] = k;
        }
        else{
            while (j >= 0 && comparate_string((char *) col->data[j], (char*) k) == -1) {
                col->data[j + 1] = col->data[j];
                j = j - 1;
            }
            col->data[j + 1] = k;
        }
    }
}

void swap_values(AP_COLUMN * col, unsigned int i, unsigned int j){
    DATA_TYPE *tmp = col->data[i];
    col->data[i] = col->data[j];
    col->data[j] = tmp;
}

unsigned int partition(AP_COLUMN * col, unsigned int left, unsigned int right, unsigned int ascending) {
    DATA_TYPE* pivot = col->data[right];
    unsigned int i = left - 1;

    for (unsigned int j = left; j < right; j++) {
        switch (col->column_type) {
            case UINT:
                if ((ascending && *(unsigned int*)col->data[j] >= *(unsigned int*)pivot) || (!ascending && *(unsigned int*)col->data[j] <= *(unsigned int*)pivot))
                    swap_values(col, i, j);
                break;
            case INT:
                if ((ascending && *(int*)col->data[j] >= *(int*)pivot) || (!ascending && *(int*)col->data[j] <= *(int*)pivot))
                    swap_values(col, i, j);
                break;
            case CHAR:
                if ((ascending && *(char*)col->data[j] >= *(char*)pivot) || (!ascending && *(char*)col->data[j] <= *(char*)pivot))
                    swap_values(col, i, j);
                break;
            case FLOAT:
                if ((ascending && *(float*)col->data[j] >= *(float*)pivot) || (!ascending && *(float*)col->data[j] <= *(float*)pivot))
                    swap_values(col, i, j);
                break;
            case DOUBLE:
                if ((ascending && *(double*)col->data[j] >= *(double*)pivot) || (!ascending && *(double*)col->data[j] <= *(double*)pivot))
                    swap_values(col, i, j);
                break;
            case STRING:
                if ((ascending && comparate_string((char*)col->data[j], (char*)pivot) >= 0) || (!ascending && comparate_string((char*)col->data[j], (char*)pivot) <= 0))
                    swap_values(col, i, j);
                break;
        }
    }
    swap_values(col, right, i+1);
    return i + 1;
}

void quicksort(AP_COLUMN * col, unsigned int left, unsigned int right, unsigned int ascending) {
    unsigned int pi;
    if (left < right) {
        pi = partition(col, left, right, ascending);
        quicksort(col, left, pi - 1, ascending);
        quicksort(col, pi + 1, right, ascending);
    }
}

void sort_column(AP_COLUMN* col, int  ascending){
    switch (col->column_type) {
        case STRING:
            if (col->index == 0)
                insertion_string_sort(col, ascending);
            else
                quicksort(col, 0, col->TL, ascending);
            col->sort_dir = 1;
            break;
        default:
            if (col->index == 0)
                insertion_sort(col, ascending);
            else
                quicksort(col, 0, col->TL, ascending);
            col->sort_dir = 1;
        }
    }
