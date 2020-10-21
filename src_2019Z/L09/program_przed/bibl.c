#include "bibl.h"

int read_vec(FILE * fin, double *v, int max){
    double d;
    int i = 0;
    while (fscanf(fin, "%lf", &d) == 1)
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

}
