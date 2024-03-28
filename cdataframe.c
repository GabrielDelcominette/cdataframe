#include "cdataframe.h"
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
=======
>>>>>>> Etienne
#include <stdlib.h>

CDATAFRAME* create_cdataframe(){
    CDATAFRAME * dataframe;
    dataframe = (CDATAFRAME*) malloc(sizeof(CDATAFRAME));
    dataframe->TP = 10;
    dataframe->TL = 0;
    dataframe->columns = NULL;
    return dataframe;
}

<<<<<<< HEAD
void read_cdataframe_user(CDATAFRAME * cdataframe){
    
}
>>>>>>> Stashed changes
=======
void read_cdataframe_user(CDATAFRAME *){
    
}
>>>>>>> Etienne
