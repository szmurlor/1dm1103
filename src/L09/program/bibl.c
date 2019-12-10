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

void polyval(double *a, int na, double *x, int nx, double *f ) {
    int i, j;
    for (i=0; i < nx; i++) {
        f[i] = 0;
        for (j = 0; j < na; j++) {
            f[i] += a[j] * pow(x[i], j);
        }
    }
}
