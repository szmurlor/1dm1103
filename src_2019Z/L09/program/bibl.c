#include "bibl.h"
#include <math.h>

int read_vec(FILE * fin, double *v, int max){
    double d;
    int i = 0;

    while ( (fscanf(fin, "%lf", &d) == 1)
            && (i < max) )
        v[i++] = d;
    return i;
}

void save_2vecs(FILE * fout, double *x, double *y, int n) {
    int i;
    for (i = 0; i < n; i++) {
        fprintf(fout, "%lf, %lf\n", x[i], y[i]);
    }
}

/*
 
 Funkcja oblicza wartość wielomianu, o współczynnikach w wektorze a.
 Stopień wielomianu wynika z rozmiaru wektora współczynników a.
 Wielomian jest postaci:

 p(x) = a[0] + a[1]*x + a[2]*x^2 + ... a[na] * x^(na-1)

*/
void polyval(double *a, int na, double *x, int nx, double *f ) {
    int i, j;
    printf("Liczę jawną implementacją z definicji.\n")
    for (i=0; i < nx; i++) {
        f[i] = 0;
        for (j = 0; j < na; j++) {
            f[i] += a[j] * pow(x[i], j);
        }
    }
}


/*
Schemat Hornera - redukcja błędu zaookrągleń
*/
void polyval_horner(double *a, int na, double *x, int nx, double *f ) {
    int i, j;    
    printf("Liczę schematem Hornera.\n")
    for (i=0; i < nx; i++) {
        f[i] = a[na-1];
        for (j = na-2; j >=  0; j--) {
            f[i] = a[j] + x[i] * f[i];
        }
    }
}

