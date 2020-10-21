#include "bibl.h"
#include <math.h>
#include "utils.h"

double * append(double *v, int n, double d) {
    double *vn = (double*) malloc(sizeof(double)*(n+1));
    int j;

    for (j = 0; v != NULL && j < n; j++)
        vn[j] = v[j];
    
    vn[n++] = d;
    
    if (v != NULL)
        free(v);
    
    return vn;
}

int read_vec(FILE * fin, double **v) {
    double d;
    int n = 0;
    double *vn = NULL;

    while ( (fscanf(fin, "%lf", &d) == 1) ) {
        vn = append(vn, n, d);
        n++;
    }

    *v = vn;
    return n;
}
/*
int read_vec(FILE * fin, double **v) {
    double d;
    int n = 0, j;
    double *vn, *vo = NULL;

    while ( (fscanf(fin, "%lf", &d) == 1) ) {                
        vn = (double*) malloc(sizeof(double)*(n+1));
        for (j = 0; vo != NULL && j < n; j++)
            vn[j] = vo[j];
        
        vn[n++] = d;
        
        if (vo != NULL)
            free(vo);
        
        vo = vn;
    }

    *v = vn;

    return n;
}
*/

void save_2vecs(FILE * fout, double *x, double *y, int n) {
    int i=0;
    for (i = 0; i < n; i++) {
        fprintf(fout, "%lf, %lf\n", x[i], y[i]);
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

    debug("Obliczam wartości wielomianu zgodnie wzorem definicyjnym.\n");
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
void polyval_horner(double *a, int na, double *x, int nx, double **f ) {    
    int i, j;    
    *f = (double*) malloc(sizeof(double)*nx);
    
    debug("Obliczam wartości wielomianu zgodnie ze schematem hornera.\n");
    for (i=0; i < nx; i++) {
        (*f)[i] = a[na-1];
        for (j = na-2; j >=  0; j--) {
            (*f)[i] = a[j] + x[i] * (*f)[i];
        }
    }
}