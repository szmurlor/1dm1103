#include <stdio.h>
#include <stdlib.h>

/* Sumator: dodaje liczby podane jako argumenty wywołania */
int main( int argc, char *argv[] ) {
        double s = 0;
        int i;

        for( i= 1; i < argc; i++ )
                s = s + atof( argv[i] );

        printf( "suma=%g\n", s );

        return 0;
}
