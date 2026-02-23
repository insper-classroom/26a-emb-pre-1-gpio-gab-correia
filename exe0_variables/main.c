#include <stdio.h>


void foo(int *a) {
    *a = *a + 1; // acessa variavel global
}

void main(void) {
    int a = 0; 

    while (1) {
        foo(&a);
        
        if (a > 5) {
            int b = 1;
            printf("%d",b);
        }
    }
}
