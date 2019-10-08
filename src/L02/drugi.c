#include <stdio.h>
#include <stdlib.h>

/* Sumator: dodaje liczby podane jako argumenty wywołania */
int main( int argc, char *argv[] ) {
        double s;
        double w[1000];
        int m = 0;
        int i;

        for( i= 1; i < argc; i++ )
                w[m++]= atof( argv[i] );

        for( i= 0; i < m; i++ )
                s = s + w[i];

        printf( "suma=%g\n", s );

        return 0;
}
