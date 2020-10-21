#include <stdio.h>
#include <math.h>

int read_vec(FILE * fin, double *v, int max);
void save_2vecs(FILE * fout, double *x, double *y, int n);
void polyval(double *a, int na, double *x, int nx, double *f );
void polyval_horner(double *a, int na, double *x, int nx, double *f );
