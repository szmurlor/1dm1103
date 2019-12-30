#include "bibl_vec_array.h"
// #include "../wspolne/utils.h"
// dzieki dodaniu w makefile'u argumentu podczas kompilacji -I../wspolne

#include <utils.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PVec vec_new(int size) {
    PVec v = (PVec) malloc(sizeof(Vec));
    v->n = size;
    if (size > 0)
        v->items = (double*) malloc(sizeof(double) * size);
    v->_size = size;

    return v;
} 

void vec_free(PVec vec) {
    free(vec->items);
    free(vec);
}

void vec_debug(PVec v) {
    printf("DEBUG: v: _size=%d, n=%d, items=%p\n", v->_size, v->n, v->items);
}

void vec_append(PVec v, double d) {
    if (v->_size == v->n) {
        int newsize = v->_size == 0 ? 1 : v->_size * 2;
        double * newitems = (double*) malloc(sizeof(double) * newsize);
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

PVec vec_read(FILE * fin){
    double d;
    PVec v = vec_new(0);

    while ( fscanf(fin, "%lf", &d) == 1 )
        vec_append(v, d);

    return v;
}

void vec_print(FILE * out, PVec vec) {
    int i;
    fprintf(out, "[");
    for (i=0; i < vec->n; i++) 
        fprintf(out, "%f%s", vec->items[i], i < (vec->n-1) ? "," : "");
    fprintf(out, "]\n");
}

void vec_save2(FILE * fout, PVec v1, PVec v2) {
    int i;
    for (i = 0; i < MIN(v1->n, v2->n); i++) {
        fprintf(fout, "%lf, %lf\n", v1->items[i], v2->items[i]);
    }
}

/*
Schemat Hornera - redukcja błędu zaookrągleń
*/
PVec polyval_horner(PVec a, PVec x) {
    int i, j;    
    PVec f = vec_new(x->n);

    debug("Liczę schematem Hornera.\n");
    for (i=0; i < x->n; i++) {
        f->items[i] = a->items[a->n - 1];
        for (j = a->n - 2; j >=  0; j--) {
            f->items[i] = a->items[j] + x->items[i] * f->items[i];
        }
    }

    return f;
}
