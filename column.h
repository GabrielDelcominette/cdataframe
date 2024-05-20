#ifndef CDATAFRAME_CREATE_DATAFRAME_H
#define CDATAFRAME_CREATE_DATAFRAME_H

#define REALOC_SIZE 256

typedef struct {
    char * title;
    int TP;
    int TL;
    int * data;
}COLUMN;

COLUMN* create_column(char* title);

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
* @brief : fill a column of values
* @param1 : Pointer to a column
* @param2 : The number of lines
*/
void fill_column(COLUMN* col, int nb_line);

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
int column_find_value(COLUMN * col, int pos);

int column_n_higher_values(COLUMN * col, int value);

int column_n_lower_values(COLUMN * col, int value);

int column_n_equals_values(COLUMN * col, int value);

int rename_column(COLUMN * col, char * string);

void free_column(COLUMN * col);

#endif //CDATAFRAME_CREATE_DATAFRAME_H
