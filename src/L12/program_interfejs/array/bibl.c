#include "bibl.h"
#include "../../wspolne/utils.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

void free_vec(PVec v) {
    if (v->_size > 0)
        free(v->items);
    free(v);
}

PVec vec_new(int initial_size) {
    PVec v = (PVec) malloc(sizeof(Vec));
    v->n = initial_size;
    if (initial_size > 0)
        v->items = (double*) malloc(sizeof(double) * initial_size);
    v->_size = initial_size;

    return v;
}

void vec_append(PVec v, double d) {
    if (v->n == v->_size) {
        int newsize = v->_size == 0 ? 1 : v->_size * 2;
        double *newitems = (double*) malloc(sizeof(double) * newsize);
        printf("Nowa dlugość: %d\n", newsize);
        if (v->_size > 0) {
            memcpy(newitems, v->items, v->_size * sizeof(double));
            free(v->items);
        }
        v->items = newitems;
        v->_size = newsize;
    }

    v->items[ v->n ] = d;
    v->n += 1;
}



PVec read_vec(FILE * fin){
    double d;
    PVec v = vec_new(0);

    while ( fscanf(fin, "%lf", &d) == 1)
        vec_append(v, d);
    
    return v;
}


void save_2vecs(FILE * fout, PVec x, PVec y) {
    int i;
    for (i = 0; i < x->n; i++) {
        fprintf(fout, "%lf, %lf\n", x->items[i], y->items[i]);
    }
}

/*
 
 Funkcja oblicza wartość wielomianu, o współczynnikach w wektorze a.
 Stopień wielomianu wynika z rozmiaru wektora współczynników a.
 Wielomian jest postaci:

 p(x) = a[0] + a[1]*x + a[2]*x^2 + ... a[na] * x^(na-1)

*/


/*
Schemat Hornera - redukcja błędu zaookrągleń
*/
PVec polyval_horner(PVec a, PVec x ) {
    int i, j;    
    PVec f = vec_new(x->n);

    debug("Liczę schematem Hornera.\n");
    for (i=0; i < x->n; i++) {
        f->items[i] = a->items[a->n-1];
        for (j = a->n-2; j >=  0; j--) {
            f->items[i] = a->items[j] + x->items[i] * f->items[i];
        }
    }

    return f;
}

