#include <stdio.h>
#include <stdlib.h>

/* Print VeCTor */
void pvct( double w[], int n ) 
{
        int i;
        printf( "[" );
        for( i= 0; i < n; i ++ )
                printf( " %g", w[i] );
        printf( " ]\n" );
}

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

        pvct(w,m);

        printf( "suma=%g\n", sum(w, m) );

        return 0;
}
