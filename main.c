#include <stdio.h>
#include "column.h"
#include "cdataframe.h"

int main(void) {
    CDATAFRAME* cdataframe = create_cdataframe("my_cdataframe");
    CDATAFRAME* cdataframe2 = create_cdataframe("my_cdataframe2");

    // Remplissage par colonnes
    fill_cdataframe_l_by_l(cdataframe, 3, 2);
    print_all_cdataframe(*cdataframe);
    delete_line(cdataframe, 1);

    /**
    // Remplissage par colonnes
    fill_cdataframe_c_by_c(cdataframe2, 3, 2);
    print_all_cdataframe(*cdataframe2);
    delete_col_by_id(cdataframe2, 1);
    print_cdataframe_limit_col(*cdataframe2, 1);
    insert_value_line(cdataframe2);
    print_cdataframe_limit_line(*cdataframe2, 1);
    print_all_cdataframe(*cdataframe2);
    **/
    return 0;
}
