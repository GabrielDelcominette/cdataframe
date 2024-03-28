#ifndef CDATAFRAME_CREATE_DATAFRAME_H
#define CDATAFRAME_CREATE_DATAFRAME_H

typedef struct {
    char * title;
    int TP;
    int TL;
    int * data;
}COLUMN;

COLUMN* create_column(char* title);

#endif //CDATAFRAME_CREATE_DATAFRAME_H
