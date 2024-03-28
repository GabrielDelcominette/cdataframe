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
* @brief : Add a new value to a column
* @param1 : Pointer to a column
* @param2 : The value to be added
* @return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN* col, int value);


#endif //CDATAFRAME_CREATE_DATAFRAME_H
