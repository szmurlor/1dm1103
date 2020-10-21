#include "bibl.h"
#include "../wspolne/utils.h"
#include <math.h>
#include <stdlib.h>

int read_vec(FILE * fin, double **v){
    double d;
    int n = 0, j;
    double *vn; // v new
    double *vo = NULL; // v old

    while ( fscanf(fin, "%lf", &d) == 1 ) {
        vn = (double*) malloc( sizeof(double) * (n+1));
        for (j = 0; j < n; j++) {
            vn[j] = vo[j];
        }
        if (vo != NULL)
            free(vo);
        vn[n] = d;
        vo = vn;
        n++;
    }

    *v = vn;    
    return n;
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
double * polyval(double *a, int na, double *x, int nx) {
    int i, j;
    double *f = (double*) malloc(sizeof(double)*nx);

    debug("Liczę jawną implementacją z definicji.\n");
    /* debug(swiety turecki KUPA); */
    for (i=0; i < nx; i++) {
        f[i] = 0;
        for (j = 0; j < na; j++) {
            f[i] += a[j] * pow(x[i], j);
        }
    }

    return f;
}


/*
Schemat Hornera - redukcja błędu zaookrągleń
*/
double * polyval_horner(double *a, int na, double *x, int nx ) {
    int i, j;    
    double *f = (double*) malloc(sizeof(double)*nx);

    debug("Liczę schematem Hornera.\n");
    for (i=0; i < nx; i++) {
        f[i] = a[na-1];
        for (j = na-2; j >=  0; j--) {
            f[i] = a[j] + x[i] * f[i];
        }
    }

    return f;
}

