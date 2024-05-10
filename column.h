

#ifndef COLUMN_H
#define COLUMN_H

#define REALLOC_SIZE 256
typedef struct {
    char* title;
    int tp;
    int tl;
    int* data;
}COLUMN;


/**
* Create a column
* @param1 : Column title
* @return : Pointer to created column
*/
COLUMN *create_column(char* title);


/**
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : The value to be added
* @return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN* col, int value);


/**
* @brief : Free allocated memory
* @param1 : Pointer to a column
*/
void delete_column(COLUMN* col);


/**
* @brief: Print a column content
* @param: Pointer to a column
*/
void print_col(COLUMN* col);


/**
* @brief: count the occurrence of a value
* @param: column
* @param: value to count
* @return: occurrence of value
*/
int occurrence_x(COLUMN col, int x);


/**
* @brief: return the value of a position
* @param: column
* @param: position to search for
* @return: value to the postion
*/
int position_x(COLUMN col, int pos);


/**
* @brief: count the values in datas superior to x
* @param: column
* @param: value x
* @return: number of values superior to x
*/
int superior_x(COLUMN col, int x);


/**
* @brief: count the values in datas inferior to x
* @param: column
* @param: value x
* @return: number of values inferior to x
*/
int inferior_x(COLUMN col, int x);


#endif //COLUMN_H
