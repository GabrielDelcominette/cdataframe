#ifndef CDATAFRAME_CREATE_DATAFRAME_H
#define CDATAFRAME_CREATE_DATAFRAME_H

#define REALOC_SIZE 256;

typedef struct {
    char * title;
    int TP;
    int TL;
    int * data;
}COLUMN;

COLUMN* create_column(char* title);

/**
* @brief : Free allocated memory
* @param1 : Pointer to a column
*/
void delete_column(COLUMN **col);

/**
@brief : Add a new value to a column
@param1 : Pointer to a column
@param2 : The value to be added
@return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN* col, int value);

/**
* @brief: Print a column content
* @param: col - Pointer to a column
*/
void print_col(COLUMN* col);

/**
 * @brief: return the number of occurences of value in the column
 * @param : col - Pointer to a column
 * @param : int - value that we search in the column
 */
int occurence(COLUMN * col, int value);

/**
 * @brief: return the value at position pos
 * @param : col - Pointer to a column
 * @param2 : position of the value
*/
int find_value(COLUMN * col, int pos);

int n_taller_values(COLUMN * col, int value);

int n_smaller_values(COLUMN * col, int value);

int n_equals_values(COLUMN * col, int value);
#endif //CDATAFRAME_CREATE_DATAFRAME_H
