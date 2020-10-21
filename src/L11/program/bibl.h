#ifndef _AKUK_BIBL_H
#define _AKUK_BIBL_H

#include <stdio.h>
#include <math.h>

typedef struct _Vec {
    double *items;
    int _size;
    int n;
} Vec, *PVec;

// PVec p;
// struct _Vec * p;

// struct Vec * adres;

// int read_vec(FILE * fin, double *v, int max);
PVec read_vec(FILE * fin);
void save_2vecs(FILE * fout, PVec x, PVec y);
PVec polyval_horner(PVec a, PVec x);

void free_vec(PVec v);

#endif