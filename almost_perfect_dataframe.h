#ifndef DATAFRAME_ALMOST_PERFECT_H

enum enum_type
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

typedef union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}COL_TYPE;

struct column {
    char *title;
    unsigned int TL; //logical size
    unsigned int TP; //physical size
    ENUM_TYPE column_type;
    COL_TYPE **data; // array of pointers to stored data
    unsigned long long int *index; // array of integers
};
typedef struct column AP_COLUMN;

typedef struct{
    int TP;
    int TL;
    AP_COLUMN ** columns; // liste de pointer vers des colonnes
} CDATAFRAME;

typedef enum enum_type ENUM_TYPE;

/**
* Create a new column
* @param1 : Column type
* @param2 : Column title
* @return : Pointer to the created column
*/
COLUMN *create_column(ENUM_TYPE type, char *title);


#define DATAFRAME_ALMOST_PERFECT_H

#endif //DATAFRAME_ALMOST_PERFECT_H
