#include <stdio.h>
#include <math.h>

// int read_vec(FILE * fin, double *v, int max);
int read_vec(FILE * fin, double **v);
void save_2vecs(FILE * fout, double *x, double *y, int n);
double* polyval(double *a, int na, double *x, int nx);
double* polyval_horner(double *a, int na, double *x, int nx);
