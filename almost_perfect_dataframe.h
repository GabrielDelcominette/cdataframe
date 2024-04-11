#ifndef DATAFRAME_ALMOST_PERFECT_H

#define REALOC_SIZE 256

// AP means Almost Perfect

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
}DATA_TYPE;

struct column {
    char *title;
    unsigned int TL; //logical size
    unsigned int TP; //physical size
    ENUM_TYPE column_type;
    DATA_TYPE **data; // array of pointers to stored data
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
AP_COLUMN * create_AP_column(ENUM_TYPE type, char *title);

/**
* @brief: Insert a new value into a column
* @param1: Pointer to the column
* @param2: Pointer to the value to insert
* @return: 1 if the value is correctly inserted 0 otherwise
*/
int insert_AP_value(AP_COLUMN *col, void *value);

#define DATAFRAME_ALMOST_PERFECT_H

#endif //DATAFRAME_ALMOST_PERFECT_H
