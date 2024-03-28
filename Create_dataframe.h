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

#endif //CDATAFRAME_CREATE_DATAFRAME_H
