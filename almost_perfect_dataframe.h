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
* @brief: Delete a column from dataframe
* @param1: pointer of cdataframe
* @param2: indice of column to delete
*/
void AP_delete_column_from_dataframe(AP_CDATAFRAME * cdataframe, int col);

/**
* @brief: Delete a row from dataframe
* @param1: pointer of cdataframe
* @param2: indice of row to delete
*/
void AP_delete_row(AP_CDATAFRAME * cdataframe, int row);

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
* @param: Pointer to the column to display
*/
void AP_print_col(AP_COLUMN* col);

int AP_insert_column(AP_CDATAFRAME * cdataframe, AP_COLUMN * col);
void AP_insert_row(AP_CDATAFRAME * cdataframe);
void AP_read_cdataframe_user(AP_CDATAFRAME * cdataframe);

// affichage des cdataframe
void AP_display_titles(AP_CDATAFRAME * cdataframe);
void AP_display_whole_cdataframe(AP_CDATAFRAME * cdataframe);
void AP_display_sorted_cdataframe(AP_CDATAFRAME * cdataframe, long long unsigned int sorted_column);
void AP_display_row(AP_CDATAFRAME * cdataframe, long long unsigned int row_number);

DATA_TYPE * AP_find_value(AP_CDATAFRAME * ap_cdataframe, int ligne, int colonne);
int AP_n_equals_values(AP_CDATAFRAME * ap_cdataframe, void * value, ENUM_TYPE type);
int AP_n_higher_values(AP_CDATAFRAME * ap_cdataframe, void * value, ENUM_TYPE type);
int AP_n_lower_values(AP_CDATAFRAME * ap_cdataframe, void * value, ENUM_TYPE type);

void insertion_sort(AP_COLUMN * col, int ascending);
void insertion_string_sort(AP_COLUMN * col, int ascending);
void swap_index(AP_COLUMN * col, unsigned int i, unsigned int j);
void quicksort(AP_COLUMN * col, int left, int right, int ascending);
int partition(AP_COLUMN * col, int left, int right, int ascending);
void AP_sort_column(AP_COLUMN* col, int ascending);
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
