#ifndef DATAFRAME_ALMOST_PERFECT_H

#define REALOC_SIZE 3
#define REALLOC_COL_NUMBER 10

// AP means Almost Perfect

enum enum_type
{
    UINT = 1, INT, CHAR, FLOAT, DOUBLE, STRING
};
typedef enum enum_type ENUM_TYPE;

typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}DATA_TYPE;

typedef struct{
    char *title;
    unsigned int TL; //logical size
    unsigned int TP; //physical size
    ENUM_TYPE column_type;
    DATA_TYPE **data; // array of pointers to stored data
    unsigned long long int *index; // array of integers
// index valid
// 0 : no index
// -1 : invalid index
// 1 : valid index
    int valid_index;
// direction de tri Ascendant ou Déscendant
// 0 : ASC
// 1 : DESC
    int sort_dir;
}AP_COLUMN;

typedef struct{
    int TP;
    int TL;
    AP_COLUMN ** columns; // liste de pointer vers des colonnes
} AP_CDATAFRAME;


/**
 *Comparate two string
 */
int comparate_string(char* string1, char* string2);

/**
* Create a new column
* @param1 : Column type
* @param2 : Column title
* @return : Pointer to the created column
*/
AP_COLUMN * AP_create_column(ENUM_TYPE type, char *title);
AP_CDATAFRAME* AP_create_cdataframe();
/**
* @brief: Insert a new value into a column
* @param1: Pointer to the column
* @param2: Pointer to the value to insert
* @return: 1 if the value is correctly inserted 0 otherwise
*/
int AP_insert_value(AP_COLUMN *col, void *value);

/**
* @brief: Free the space allocated by a column
* @param1: Pointer to the column
*/
void AP_delete_column(AP_COLUMN **col);

/**
* @brief: Convert a value into a string
* @param1: Pointer to the column
* @param2: Position of the value in the data array
* @param3: The string in which the value will be written
* @param4: Maximum size of the string
*/

void AP_convert_value(ENUM_TYPE type, DATA_TYPE * value, char *str, int size);

/**
* @brief: Display the content of a column
* @param: col to the column to display
*/
void AP_print_col(AP_COLUMN* col);

/**
* @brief: Permet d'inséré une colonne passé en paramètre, dans la cdataframe
* @param: cdataframe pointer to the cdataframe
* @param: col pointer to the column to display
*/
int AP_insert_column(AP_CDATAFRAME * cdataframe, AP_COLUMN * col);
/**
* @brief: Permet d'inséré dans la cdataframe, une ligne que l'utilisateur entre dans la console
* @param: cdataframe pointer to the cdataframe
*/
void AP_insert_row(AP_CDATAFRAME * cdataframe);
/**
* @brief: Permet à l'utilisateur de créer une cdataframe et d'entrer la valeur de chaque cellule dans la console / cette fonction fait appel à AP_create_cdataframe(); et AP_insert_row(AP_CDATAFRAME * cdataframe);
* @param: cdataframe pointer to the cdataframe
*/
void AP_read_cdataframe_user(AP_CDATAFRAME * cdataframe);

// affichage des cdataframe
/**
* @brief: Afficher les titres d'une cdataframe passé en paramètre
* @param: cdataframe pointer to the cdataframe
*/
void AP_display_titles(AP_CDATAFRAME * cdataframe);

/**
* @brief: Afficher la cdataframe passé en paramètre
* @param: cdataframe pointer to the cdataframe
*/
void AP_display_whole_cdataframe(AP_CDATAFRAME * cdataframe);

/**
* @brief: Afficher la cdataframe passé en paramètre, dans l'ordre du trie d'une colonne dont l'indice est passé en paramètre.
* @param: cdataframe pointer to the cdataframe
* @param: sorted_column indice de la colonne selon laquelle l'utilisateur souhaite que la cdataframe soit trié
*/
void AP_display_sorted_cdataframe(AP_CDATAFRAME * cdataframe, long long unsigned int sorted_column);

/**
* @brief: Afficher une ligne de la cdataframe
* @param: cdataframe pointer to the cdataframe
* @param: row_number indice de la ligne que l'on souhaite afficher
*/
void AP_display_row(AP_CDATAFRAME * cdataframe, long long unsigned int row_number);


/**
* @brief: Afficher une valeur de la cdataframe
* @param: cdataframe pointer to the cdataframe
* @param: ligne indice de la ligne dont l'on souhaite afficher la valeure
* @param: colonne indice de la colonne dont l'on souhaite afficher la valeure
*/
DATA_TYPE * AP_find_value(AP_CDATAFRAME * ap_cdataframe, int ligne, int colonne);

/**
* @brief: Renvoie le nombre de valeurs égales à la valeur *value passé en paramètre
* @param: cdataframe pointer to the cdataframe
* @param: value pointeur sur la valeur
* @param: type type de la valeur sur laquelle pointe value
*/
int AP_n_equals_values(AP_CDATAFRAME * ap_cdataframe, void * value, ENUM_TYPE type);

/**
* @brief: Renvoie le nombre de valeurs inférieures à la valeur *value passé en paramètre
* @param: cdataframe pointer to the cdataframe
* @param: value pointeur sur la valeur
* @param: type type de la valeur sur laquelle pointe value
*/
int AP_n_higher_values(AP_CDATAFRAME * ap_cdataframe, void * value, ENUM_TYPE type);

/**
* @brief: Renvoie le nombre de valeurs supérieures à la valeur *value passé en paramètre
* @param: cdataframe pointer to the cdataframe
* @param: value pointeur sur la valeur
* @param: type type de la valeur sur laquelle pointe value
*/
int AP_n_lower_values(AP_CDATAFRAME * ap_cdataframe, void * value, ENUM_TYPE type);


/**
* @brief: Tri les index de la colonne dans l'ordre croissant ou décroissant des valeurs auquels elles sont associés
* @param: col pointeur sur la colonne que l'on souhaite trier
* @param: acending 1 pour un tri croissant, 0 pour un tri décroissant
*/
void insertion_sort(AP_COLUMN * col, int ascending);

/**
* @brief: Tri les index de la colonne dans l'ordre croissant ou décroissant des valeurs auquels elles sont associés - fonctionne uniquement si le type de la colonne est STRING
* @param: col pointeur sur la colonne que l'on souhaite trier
* @param: acending 1 pour un tri croissant, 0 pour un tri décroissant
*/
void insertion_string_sort(AP_COLUMN * col, int ascending);

/**
* @brief: Echange la position de index dans une colonne
* @param: col pointeur sur la colonne
* @param: i indice du premier index
* @param: j indice du deuxième index
*/
void swap_index(AP_COLUMN * col, unsigned int i, unsigned int j);

/**
* @brief: Fonction de tri récursive, divisant les valeurs de la colonne en sous-colonne, permettant le tri des index de la colonne dans l'ordre croissant ou décroissant des valeurs auquels elles sont associés
 * Fonction faisant appel à la fonction partition(AP_COLUMN * col, int left, int right, int ascending); afin de réaliser le trie
* @param: col pointeur sur la colonne que l'on souhaite trier
* @param: acending 1 pour un tri croissant, 0 pour un tri décroissant
* @param: left indice du début de la sous-colonne
* @param: right indice de fin de la sous-colonne
*/
void quicksort(AP_COLUMN * col, int left, int right, int ascending);

/**
* @brief: Fonction réalisant le tri des sous-colonnes dans l'algorithme quicksort
* @param: col pointeur sur la colonne que l'on souhaite trier
* @param: acending 1 pour un tri croissant, 0 pour un tri décroissant
* @param: left indice du début de la sous-colonne
* @param: right indice de fin de la sous-colonne
*/
int partition(AP_COLUMN * col, int left, int right, int ascending);

/**
* @brief: Fonction réalisant le tri d'une colonne - La fonction fait appel aux différentes fonctions de tri précédentes en fonction du type de la colonne et de si elle est déjà partiellement trié
* @param: col pointeur sur la colonne que l'on souhaite trier
* @param: acending 1 pour un tri croissant, 0 pour un tri décroissant
*/
void AP_sort_column(AP_COLUMN* col, int ascending);

/**
* @brief: Fonction réalisant le tri de toutes les colonnes d'une cdataframe - La fonction fait appel aux différentes fonctions de tri précédentes en fonction du type de la colonne et de si elle est déjà partiellement trié
* @param: cdataframe pointeur sur la cdataframe que l'on souhaite trier
* @param: acending 1 pour un tri croissant, 0 pour un tri décroissant
*/
void AP_sort_dataframe(AP_CDATAFRAME * cdataframe, int  ascending);

/**
* @brief: Remove the index of a column
* @param1: Pointer to the column
*/
void erase_index(AP_COLUMN *col);

/**
* @brief: Check if an index is correct
* @param1: Pointer to the column
* @return: 0: index not existing,
-1: the index exists but invalid,
1: the index is correct
*/
int check_index(AP_COLUMN *col);

/**
* @brief: Check if a value exists in a column
* @param1: Pointer to the column
* @param2: Pointer to the value to search for
* @return: -1: column not sorted,
0: value not found
1: value found
*/
long long unsigned int search_value_in_column(AP_COLUMN *col, void *val);

#define DATAFRAME_ALMOST_PERFECT_H
#endif //DATAFRAME_ALMOST_PERFECT_H
