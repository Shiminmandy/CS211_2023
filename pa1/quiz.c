#include <stdlib.h>
#include <stdio.h>

int* function( int* pointer ) {

    pointer = malloc ( sizeof(int) );
    pointer[0] = 1;
    return pointer;

}

int main() {

    int* array = NULL;

    function( array );

    printf ( "%d\n", array[0] );

    return 0;

}