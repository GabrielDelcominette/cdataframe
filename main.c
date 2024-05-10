#include <stdio.h>
#include "column.h"

int main(void) {
    COLUMN *mycol = create_column("title");
    int x=0, i=0, values[5] = {1,2,3,4,5};
    for (i = 0; i<5; i++) {
        x = insert_value(mycol, values[i]);
    }
    print_col(mycol);
    return 0;
}
