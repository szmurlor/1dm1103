#include <stdio.h>
#include <stdlib.h>

/*Ten program jest tylko obrazowo. Pokazuje składnię funkcji. */

double sum( double v[], int n )
{
        double s = 0.0;
        int i;
        for( i= 0; i < n; i++ )
                s += v[i];

        return s;
}

int main( int argc, char *argv[] ) {
        double w[1000];
        int m = 0;
        int i;

        for( i= 1; i < argc; i++ )
                w[m++]= atof( argv[i] );

        printf( "suma=%g\n", sum(w, m) );

        return 0;
}
