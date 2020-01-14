#ifndef _AKUK_BIBL_H
#define _AKUK_BIBL_H

#include <stdio.h>
#include <math.h>

typedef struct _VecItem{
    double v;
    struct _VecItem *n;
} VecItem, *PVecItem;

typedef struct _Vec {
    PVecItem head;
    int n;
} Vec, *PVec;

PVec read_vec(FILE * fin);
void save_2vecs(FILE * fout, PVec x, PVec y);
PVec polyval_horner(PVec a, PVec x);

void free_vec(PVec v);

#endif