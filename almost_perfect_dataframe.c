#include "almost_perfect_dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparate_string(char* string1, char* string2){
    int x = 0;
    while (string1[x] == string2[x] && string1[x] != '\0' && string2[x] != '\0')
        x++;
    if (string1[x] == '\0' && string2[x] == '\0')
        return 0; // les deux chaines de caractères sont égals
    else{
        if (string1[x] == '\0' || string1[x] < string2[x])
            return -1; // string1 est inférieur à string2
        else
            return 1; // string1 est supérieur à string2
    }
}

AP_COLUMN* AP_create_column(ENUM_TYPE type, char * title){
    AP_COLUMN * column;
    column = (AP_COLUMN*) malloc(sizeof(AP_COLUMN));
    column->title = (char *) malloc(sizeof(char) * (strlen(title) + 1));
    strcpy(column->title, title);
    column->TP = 0;
    column->TL = 0;
    column->column_type = type;
    column->data = NULL;
    column->index = NULL;
    column->valid_index = -1;
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
    if (value == NULL)
        return 0;

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
        allocation = 1;  // on va allouer de l'espace pour les valeurs des pointeurs
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
        allocation = 1; // on va allouer de l'espace pour les valeurs des pointeurs
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
        //value = (DATA_TYPE*) value; // on convertie le type de value
        //col->data[col->TL] = value; // on assigne le pointeur à la colonne
        //on assigne la valeur de ce pointeur au pointeur contenue dans la colonne
        switch (col->column_type) {
            case UINT:
                *(unsigned int *) col->data[col->TL] = *(unsigned int *) value;
                break;
            case INT:
                *(int *) col->data[col->TL] = *(int *) value;
                break;
            case CHAR:
                *(char *) col->data[col->TL] = *(char *) value;
                break;
            case FLOAT:
                *(float *) col->data[col->TL] = *(float *) value;
                break;
            case DOUBLE:
                *(double *) col->data[col->TL] = *(double *) value;
                break;
            case STRING:
                col->data[col->TL]->string_value = (char *) malloc(sizeof(char) * strlen(value));
                // on copie la chaine de caractaires value
                int i=0;
                while (* ((char*) value + i) != '\0' && i < 49){
                    *(col->data[col->TL]->string_value+i) = (* ((char*) value + i));
                    i++;
                }
                *(col->data[col->TL]->string_value+i) = '\0';
                break;
        }
        col->index[col->TL] = col->TL + 1; // on assigne un index à la valeur
        col->TL+=1;

        // Si la colonne était trié, on dit qu'elle ne l'est plus que partiellement
        if (col->valid_index == 1)
            col->valid_index = -1;

        return 1;
    }
    return 0;
}

void AP_delete_column(AP_COLUMN **col){
    printf("\nsupression...");
    free((*col)->title);
    for (int i = 0; i<(*col)->TP; i++){
        free((*col)->data[i]);
    }
    free((*col)->data);
    free(*col);
}

void AP_delete_column_from_dataframe(AP_CDATAFRAME * cdataframe, int col){
    if (col < 1 ||  col > cdataframe->TL) {
        printf("/!\\ERREUR : les indices entrées sont impossibles !");
    }
    else {
        AP_COLUMN* tmp = cdataframe->columns[col - 1];
        for (int i = col; i < cdataframe->TL; i++) {
            cdataframe->columns[i - 1] = cdataframe->columns[i];
        }
        cdataframe->TL -= 1;
        AP_delete_column(&tmp);
    }
}


void AP_delete_row(AP_CDATAFRAME * cdataframe, int row){
    if (row < 0 ||  row > cdataframe->columns[0]->TL) {
        printf("/!\\ERREUR : les indices entrées sont impossibles !");
    }
    else{
        for (int i=0; i<cdataframe->TL; i++){
            for (int j=row; j<cdataframe->columns[0]->TL; j++){
                cdataframe->columns[i]->data[j] = cdataframe->columns[i]->data[j+1];
            }
            cdataframe->columns[i]->TL-=1;
        }
    }
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
    printf("%s \n", col->title);
    int max_size = 50;
    char string[max_size];
    for (int i=0; i<col->TL; i++) {
        AP_convert_value(col->column_type, col->data[i], string, max_size);
        printf("[%llu] %s\n", col->index[i], string);
    }
}

void AP_print_sorted_col(AP_COLUMN* col){
    int max_size = 50;
    char string[max_size];
    if (col->valid_index == 1){
        printf("\n\n%s\n", col->title);
        for (int i=0; i<col->TL; i++){
            AP_convert_value(col->column_type, col->data[col->index[i]], string, max_size);
            printf("%s\n", string);
        }
    }
}

int  AP_insert_column(AP_CDATAFRAME * cdataframe, AP_COLUMN * col){
    if (cdataframe->columns == NULL){
        cdataframe->columns = (AP_COLUMN **) malloc(REALLOC_COL_NUMBER * sizeof(AP_COLUMN *));
        cdataframe->TP += REALLOC_COL_NUMBER;
    }
    if (cdataframe->columns == NULL){
        return 0;
    }
    if (cdataframe->TL == cdataframe->TP){
        AP_COLUMN ** tmp = cdataframe->columns; // variable temporaire au cas où realloc ne fonctionnerait pas
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
                unsigned int value;
                printf(">Saisissez la valeure de la ligne %d de la colonne %d, dont le type est UNSIGNED INT : \\n", cdataframe->columns[colonne]->TL + 1, colonne+1);
                scanf(" %u", &value);
                AP_insert_value(cdataframe->columns[colonne], &value);
                break;}
            case INT:
            {
                int value;
                printf(">Saisissez la valeure de la ligne %d de la colonne %d, dont le type est INT : \n", cdataframe->columns[colonne]->TL + 1, colonne+1);
                scanf(" %d", &value);
                AP_insert_value(cdataframe->columns[colonne], &value);
                break;}
            case CHAR:
            {
                char value;
                printf(">Saisissez la valeure de la ligne %d de la colonne %d, dont le type est CHAR : \n", cdataframe->columns[colonne]->TL + 1, colonne+1);
                scanf(" %c", &value);
                AP_insert_value(cdataframe->columns[colonne], &value);
                break;}
            case FLOAT:
            {
                float value;
                printf(">Saisissez la valeure de la ligne %d de la colonne %d, dont le type est FLOAT : \n", cdataframe->columns[colonne]->TL + 1, colonne+1);
                scanf(" %f", &value);
                AP_insert_value(cdataframe->columns[colonne], &value);
                break;}
            case DOUBLE:
            {
                double value;
                printf(">Saisissez la valeure de la ligne %d de la colonne %d, dont le type est DOUBLE : \n", cdataframe->columns[colonne]->TL + 1, colonne+1);
                scanf(" %lf", &value);
                AP_insert_value(cdataframe->columns[colonne], &value);
                break;}
            case STRING:
            {
                char *value = NULL;
                printf(">Saisissez la valeure de la ligne %d de la colonne %d, dont le type est STRING : \n", cdataframe->columns[colonne]->TL + 1, colonne+1);
                scanf(" %s", &value);
                AP_insert_value(cdataframe->columns[colonne], &value);
                break;}
        }
        printf("%d \n", cdataframe->columns[colonne]->data[cdataframe->columns[colonne]->TL - 1]->int_value);
    }
    AP_display_whole_cdataframe(cdataframe);
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
        printf("Saisissez le type de la colonne :\n\t1 pour UNINT\n\t2 pour INT\n\t3 pour CHAR\n\t4 pour FLOAT\n\t5 pour DOUBLE\n\t6 pour STRING\n\n");
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
        printf("\n=== Saisir les valeurs de la ligne %d ===\n", ligne);
        AP_insert_row(cdataframe);
        printf("%d \n", cdataframe->columns[0]->data[ligne]->int_value);
    }
}

void AP_display_titles(AP_CDATAFRAME * cdataframe){
    printf("\n\n");
    for (int i=0; i<cdataframe->TL; i++){
        printf("%s\t\t", cdataframe->columns[i]->title);
    }
}

void AP_display_whole_cdataframe(AP_CDATAFRAME * cdataframe){
    AP_display_titles(cdataframe); // affichages des titles des colonnes en première ligne de la cdataframe
    for (int j=1; j<cdataframe->columns[0]->TL+1; j++) {
        printf("\n"); // avant d'afficher les valeurs de la ligne, on revient à la ligne
        AP_display_row(cdataframe, j);
    }
}

void AP_display_sorted_cdataframe(AP_CDATAFRAME * cdataframe, long long unsigned int sorted_column){
    if (cdataframe->columns[sorted_column-1]->index != NULL){
        AP_sort_column(cdataframe->columns[sorted_column-1], cdataframe->columns[sorted_column-1]->sort_dir);
        AP_display_titles(cdataframe); // affichages des titles des colonnes en première ligne de la cdataframe
        for (int j=0; j<cdataframe->columns[0]->TL; j++) {
            printf("\n"); // avant d'afficher les valeurs de la ligne, on revient à la ligne
            AP_display_row(cdataframe, cdataframe->columns[sorted_column - 1]->index[j]);
        }
    }
}


void AP_display_row(AP_CDATAFRAME * cdataframe, long long unsigned int row_number){
    for (int i = 0; i < cdataframe->TL; i++) { // pour chaque colonne de la ligne
        switch (cdataframe->columns[i]->column_type) {
            // On affiche la valeur en fonction de son type
            case UINT:
                printf("%u\t\t", *(unsigned int *) cdataframe->columns[i]->data[row_number - 1]);
                break;
            case INT:
                printf("%d\t\t", *(int *) cdataframe->columns[i]->data[row_number - 1]);
                break;
            case CHAR:
                printf("%c\t\t", *(char *) cdataframe->columns[i]->data[row_number - 1]);
                break;
            case FLOAT:
                printf("%f\t\t", *(float *) cdataframe->columns[i]->data[row_number - 1]);
                break;
            case DOUBLE:
                printf("%lf\t", *(double *) cdataframe->columns[i]->data[row_number - 1]);
                break;
            case STRING:
                printf("%s\t\t", cdataframe->columns[i]->data[row_number - 1]->string_value);
                break;
        }
    }
}

DATA_TYPE * AP_find_value(AP_CDATAFRAME * ap_cdataframe, int ligne, int colonne){
    return ap_cdataframe->columns[colonne-1]->data[ligne-1];
}

int AP_n_equals_values(AP_CDATAFRAME * ap_cdataframe, void * val, ENUM_TYPE type){
    int sum=0;
    int size = 50;

    // on peut comparer des nombres uniquement avec des nombres
    int is_digital; // booléen indiquant si val est digital ou bien si il correspond à des chaines de caractères.

    char str_val[size]; //initialisation d'une chaine de caractères associés à val

    // on associe à val, sa valeur en type double.
    double value;
    // on convertit val en fonction de son type
    switch (type) {
        case UINT:
            is_digital = 1; // True
            value = * (unsigned int *) val;
            break;
        case INT:
            is_digital = 1; // True
            value = * (int *) val;
            break;
        case FLOAT:
            is_digital = 1; // True
            value = * (float *) val;
            break;
        case DOUBLE:
            is_digital = 1; //True
            value = * (double *) val;
            break;
        case CHAR:
            is_digital = 0; //False
            str_val[0] = *(char *) val;
            str_val[1] = '\0';
            break;
        case STRING:
            is_digital = 0; // False
            int i=0;
            while (* ((char *) val + i) != '\0'){
                str_val[i] = * ((char *)val + i);
                if (i > 48){
                    printf("ERREUR : Chaine de caractères trop longue - max : 49 char");
                    return -1;
                }
                i++;
            }
            str_val[i] = '\0';
            break;
    }
    printf("conversion de la valeur\n");

    for (int i=0; i<ap_cdataframe->TL; i++) {
        switch (ap_cdataframe->columns[i]->column_type) {
            case (STRING):
                if (!is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {

                        printf("les caractères sont : %s et %s .\n",ap_cdataframe->columns[i]->data[j]->string_value, str_val);

                        // on compare les deux chaines de caractères
                        if (!comparate_string(ap_cdataframe->columns[i]->data[j]->string_value, str_val))
                            sum++;
                    }
                    break;
                }
            case UINT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if ((double) ap_cdataframe->columns[i]->data[j]->uint_value == value)
                            sum++;
                    }
                }
                break;
            case INT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        printf("les entiers sont : %lf  et %lf\n", (double) ap_cdataframe->columns[i]->data[j]->int_value, value);
                        if ((double) ap_cdataframe->columns[i]->data[j]->int_value == value)
                            sum++;
                    }
                }
                break;
            case CHAR:
                if (!is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        printf("les caractères sont : %c  et %c et la terminaise %c .\n", *(char *) ap_cdataframe->columns[i]->data[j], str_val[0], str_val[1]);
                        if (ap_cdataframe->columns[i]->data[j]->char_value == str_val[0] && str_val[1] == '\0')
                            sum++;
                    }
                }
                break;
            case FLOAT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if ((double) ap_cdataframe->columns[i]->data[j]->float_value == value)
                            sum++;
                    }
                }
                break;
            case DOUBLE:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if (ap_cdataframe->columns[i]->data[j]->double_value == value)
                            sum++;
                    }
                }
                break;
        }
    }
    return sum;
}

int AP_n_lower_values(AP_CDATAFRAME * ap_cdataframe, void * val, ENUM_TYPE type){
    int sum=0;
    int size = 50;

    // on peut comparer des nombres uniquement avec des nombres
    int is_digital; // booléen indiquant si val est digital ou bien si il correspond à des chaines de caractères.

    char str_val[size]; //initialisation d'une chaine de caractères associés à val

    // on associe à val, sa valeur en type double.
    double value;
    // on convertit val en fonction de son type
    switch (type) {
        case UINT:
            is_digital = 1; // True
            value = * (unsigned int *) val;
            break;

        case INT:
            is_digital = 1; // True
            value = * (int *) val;
            break;

        case FLOAT:
            is_digital = 1; // True
            value = * (float *) val;
            break;

        case DOUBLE:
            is_digital = 1; //True
            value = * (double *) val;
            break;

        case CHAR:
            is_digital = 0; //False
            str_val[0] = *(char *) val;
            str_val[1] = '\0';
            break;

        case STRING:
            is_digital = 0; // False
            int i=0;
            while (* ((char *) val + i) != '\0'){
                str_val[i] = * ((char *)val + i);
                if (i > 48){
                    printf("ERREUR : Chaine de caractères trop longue - max : 49 char");
                    return -1;
                }
                i++;
            }
            str_val[i] = '\0';
            break;
    }

    for (int i=0; i<ap_cdataframe->TL; i++) {
        switch (ap_cdataframe->columns[i]->column_type) {

            case (STRING):
                if (!is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {

                        printf("les caractères sont : %s et %s .\n",ap_cdataframe->columns[i]->data[j]->string_value, str_val);

                        // on compare les deux chaines de caractères
                        if (comparate_string(ap_cdataframe->columns[i]->data[j]->string_value, str_val) == -1)
                            sum++;
                    }
                    break;
                }

            case UINT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if ((double) ap_cdataframe->columns[i]->data[j]->uint_value < value)
                            sum++;
                    }
                    break;
                }

            case INT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if ((double) ap_cdataframe->columns[i]->data[j]->int_value < value)
                            sum++;
                    }
                    break;
                }

            case CHAR:
                if (!is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if (ap_cdataframe->columns[i]->data[j]->char_value < str_val[0] ||
                            (ap_cdataframe->columns[i]->data[j]->char_value == str_val[0] && str_val[1] != '\0'))
                            sum++;
                    }
                    break;
                }

            case FLOAT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if ((double) ap_cdataframe->columns[i]->data[j]->float_value < value)
                            sum++;
                    }
                    break;
                }

            case DOUBLE:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if (ap_cdataframe->columns[i]->data[j]->double_value < value)
                            sum++;
                    }
                    break;
                }
        }
    }
    return sum;
}

int AP_n_higher_values(AP_CDATAFRAME * ap_cdataframe, void * val, ENUM_TYPE type){
    int sum=0;
    int size = 50;

    // on peut comparer des nombres uniquement avec des nombres
    int is_digital; // booléen indiquant si val est digital ou bien si il correspond à des chaines de caractères.

    char str_val[size]; //initialisation d'une chaine de caractères associés à val

    // on associe à val, sa valeur en type double.
    double value;
    // on convertit val en fonction de son type
    switch (type) {
        case UINT:
            is_digital = 1; // True
            value = * (unsigned int *) val;
            break;
        case INT:
            is_digital = 1; // True
            value = * (int *) val;
            break;
        case FLOAT:
            is_digital = 1; // True
            value = * (float *) val;
            break;
        case DOUBLE:
            is_digital = 1; //True
            value = * (double *) val;
            break;
        case CHAR:
            is_digital = 0; //False
            str_val[0] = *(char *) val;
            str_val[1] = '\0';
            break;
        case STRING:
            is_digital = 0; // False
            int i=0;
            while (* ((char *) val + i) != '\0'){
                str_val[i] = * ((char *)val + i);
                if (i > 48){
                    printf("ERREUR : Chaine de caractères trop longue - max : 49 char");
                    return -1;
                }
                i++;
            }
            str_val[i] = '\0';
            break;
    }
    printf("conversion de la valeur\n");

    for (int i=0; i<ap_cdataframe->TL; i++) {
        switch (ap_cdataframe->columns[i]->column_type) {
            case (STRING):
                if (!is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {

                        printf("les caractères sont : %s et %s .\n",ap_cdataframe->columns[i]->data[j]->string_value, str_val);

                        // on compare les deux chaines de caractères
                        if (comparate_string(ap_cdataframe->columns[i]->data[j]->string_value, str_val) == 1)
                            sum++;
                    }
                    break;
                }
            case UINT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if ((double) ap_cdataframe->columns[i]->data[j]->uint_value > value)
                            sum++;
                    }
                }
                break;
            case INT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        printf("les entiers sont : %lf  et %lf\n", (double) ap_cdataframe->columns[i]->data[j]->int_value, value);
                        if ((double) ap_cdataframe->columns[i]->data[j]->int_value > value)
                            sum++;
                    }
                }
                break;
            case CHAR:
                if (!is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        printf("les caractères sont : %c  et %c et la terminaise %c .\n", *(char *) ap_cdataframe->columns[i]->data[j], str_val[0], str_val[1]);
                        if (ap_cdataframe->columns[i]->data[j]->char_value > str_val[0])
                            sum++;
                    }
                }
                break;
            case FLOAT:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if ((double) ap_cdataframe->columns[i]->data[j]->float_value > value)
                            sum++;
                    }
                }
                break;
            case DOUBLE:
                if (is_digital) {
                    for (int j = 0; j < ap_cdataframe->columns[0]->TL; j++) {
                        if (ap_cdataframe->columns[i]->data[j]->double_value > value)
                            sum++;
                    }
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
            printf("Affichage de la colonne\n"); AP_print_col(col); \
            long long unsigned int tmp = col->index[i]; \
            int j = i - 1;\
            if (ascending){\
                while (j >= 0 && *(TYPE *)col->data[col->index[j]-1] > *(TYPE *) col->data[tmp-1]) { \
                    col->index[j + 1] = col->index[j];\
                    j = j - 1; \
            }\
            col->index[j + 1] = tmp;}\
            else{ \
                while (j >= 0 && *(TYPE *)col->data[col->index[j]-1] < *(TYPE *) col->data[tmp-1]) { \
                    col->index[j + 1] = col->index[j];\
                    j = j - 1; \
            }\
            col->index[j + 1] = tmp;}\
            }printf("Fin\n");

void insertion_sort(AP_COLUMN * col, int ascending){
    printf("on est sensé être dans la fonction \n");
    printf("début \n");
    switch (col->column_type){
        case INT:
            printf("là \n");
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
        long long unsigned int tmp = col->index[i];
        int j = i - 1;

        if (ascending){
            while (j >= 0 && comparate_string(*(char **) col->data[col->index[j] - 1], *(char**) col->data[tmp - 1]) == 1) {
                col->index[j + 1] = col->index[j];
                j = j - 1;
            }
            col->index[j + 1] = tmp;
        }
        else{
            while (j >= 0 && comparate_string(*(char **) col->data[col->index[j] - 1], *(char**) col->data[tmp - 1]) == -1) {
                col->index[j + 1] = col->index[j];
                j = j - 1;
            }
            col->index[j + 1] = tmp;
        }
    }
}

void swap_index(AP_COLUMN * col, unsigned int i, unsigned int j){
    printf("Swap_index \n");
    unsigned long long int tmp2 = col->index[i];
    col->index[i] = col->index[j];
    col->index[j] = tmp2;
    printf("fin de la fonction swap_value\n");
}

int partition(AP_COLUMN * col, int left, int right, int ascending) {
    printf("\n\nPartition beggining  left %d right %d ascending %d\n", left, right, ascending);
    DATA_TYPE* pivot = col->data[col->index[right]-1];
    int i = left - 1;

    for (unsigned int j = left; j < right; j++) {
        printf("j %d %d column type : %d\n", j, right, col->column_type);
        switch (col->column_type) {
            case UINT:
                if ((ascending && *(unsigned int*)col->data[col->index[j]-1] <= *(unsigned int*)pivot) || (!ascending && *(unsigned int*)col->data[col->index[j]-1] >= *(unsigned int*)pivot)){
                    i++;
                    swap_index(col, i, j);}
                break;
            case INT:
                printf("Dans le int %d, %d, %d\n", *(int*)col->data[col->index[j]-1], *(int*)pivot, ascending);
                if ((ascending && *(int*)col->data[col->index[j]-1] <= *(int*)pivot) || (!ascending && *(int*)col->data[col->index[j]-1] >= *(int*)pivot)){
                    printf("Swap \n");
                    i++;
                    swap_index(col, i, j);}
                break;
            case CHAR:
                printf("Dans le char %c, %c, %d\n", *(char *)col->data[col->index[j]-1], *(char *)pivot, ascending);
                if ((ascending && *(char*)col->data[col->index[j]-1] <= *(char*)pivot) || (!ascending && *(char*)col->data[col->index[j]-1] >= *(char*)pivot)){
                    i++;
                    swap_index(col, i, j);}
                break;
            case FLOAT:
                if ((ascending && *(float*)col->data[col->index[j]-1] <= *(float*)pivot) || (!ascending && *(float*)col->data[col->index[j]-1] >= *(float*)pivot)){
                    i++;
                    swap_index(col, i, j);
                }
                break;
            case DOUBLE:
                if ((ascending && *(double*)col->data[col->index[j]-1] <= *(double*)pivot) || (!ascending && *(double*)col->data[col->index[j]-1] >= *(double*)pivot)){
                    i++;
                    swap_index(col, i, j);
                }
                break;
            case STRING:
                printf("Partition dans les strings, %s et %s\n", *(char**)col->data[col->index[j]-1], *(char**)pivot);
                if ((ascending && comparate_string(*(char**)col->data[col->index[j]-1], *(char**)pivot) <= 0) || (!ascending && comparate_string(*(char**)col->data[col->index[j]-1], *(char**)pivot) >= 0)){
                    printf("Swap \n");
                    i++;
                    swap_index(col, i, j);}
                break;
        }
    }
    printf("voici l'indice avant le swap : %d \n", i+1);
    swap_index(col, right, i + 1);
    printf("voici l'indice avant le return : %d \n", i+1);
    printf("voici l'indice avant le return : %d \n", i);
    return i + 1;
}

void quicksort(AP_COLUMN * col, int left, int right, int ascending) {
    int pi;
    printf("Start of function %d %d %d", left, right, ascending);
    if (left < right) {
        pi = partition(col, left, right, ascending);
        printf("fin de la partition %d \n", pi);
        quicksort(col, left, pi - 1, ascending);
        printf("fin du premier quicksort \n");
        quicksort(col, pi + 1, right, ascending);
    }
}

void AP_sort_column(AP_COLUMN* col, int ascending){
    if (col->valid_index != 1 || ascending != col->sort_dir){ // on ne trie la colonne, uniquement si elle n'est pas déjà trié
        switch (col->column_type) {
            case STRING:
                if (col->valid_index == -1){
                    printf("String insertion_sort\n");
                    insertion_string_sort(col, ascending);}
                else{
                    printf("String quick_sort\n");
                    quicksort(col, 0, col->TL - 1, ascending);}
                col->valid_index = 1;
                col->sort_dir = ascending;
                break;
            default:
                if (col->valid_index == -1){
                    printf("Default insertion_sort\n");
                    printf("Le ascending %d \n", ascending);
                    insertion_sort(col, ascending);
                }
                else{
                    printf("\n\nDefault quick_sort\n");
                    quicksort(col, 0, col->TL - 1, ascending);
                }
                col->valid_index = 1;
                col->sort_dir = ascending;
            }
        }
    }

void AP_sort_dataframe(AP_CDATAFRAME * cdataframe, int  ascending){
    for (int i=0; i<cdataframe->TL; i++){
        printf("Column number : %d \n", i);
        AP_sort_column(cdataframe->columns[i], ascending);
        AP_print_col(cdataframe->columns[i]);
    }
}

/**
* @brief: Remove the index of a column
* @param1: Pointer to the column
*/
void erase_index(AP_COLUMN *col){
    free(col->index);
    col->index = NULL;
    col->valid_index = 0;
}

int check_index(AP_COLUMN *col){
    if (col->index == NULL)
        return 0;
    if (col->valid_index == 1)
        return 1;
    return -1;
}

#define CONDITION(TYPE) \
    if (* (TYPE*) col->data[col->index[mid]] == * (TYPE*) val)\
        return col->index[mid];\
    if ((* (TYPE*) col->data[col->index[mid]] < * (TYPE*) val && col->sort_dir == 1) || (* (TYPE*) col->data[col->index[mid]] > * (TYPE*) val && col->sort_dir == 0)) \
        left = mid + 1;\
    else\
        right = mid - 1;

long long unsigned int search_value_in_column(AP_COLUMN *col, void *val){
    int mid, left, right;
    if (col->index != NULL){
        AP_sort_column(col, col->sort_dir);
        left = 0;
        right = col->TL;
        while (left < right){
            mid = left + (left-right) / 2;
            switch (col->column_type) {
                case UINT:
                    CONDITION(unsigned int)
                    break;
                case INT:
                    CONDITION(int)
                    break;
                case CHAR:
                    CONDITION(char)
                    break;
                case FLOAT:
                    CONDITION(float)
                    break;
                case DOUBLE:
                    CONDITION(double)
                    break;
                case STRING:
                    CONDITION(char *)
                    break;
            }
        }
    }
    return -1;
}