#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"


int main(){
    CDATAFRAME * cdf;
    printf("coucou ceci est un test");
    cdf = create_cdataframe();
    read_cdataframe_user(cdf);
    printf("%s %d", (*cdf->columns)->title, *((*cdf->columns)->data));
    return 0;
}