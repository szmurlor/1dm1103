#include <stdio.h>
#include <math.h>

typedef struct _Vec {
    int n;
    int _size;
    double *items;
} Vec, *PVec;

PVec vec_new(int size);
void vec_free(PVec v);
PVec vec_read(FILE * fin);
void vec_print(FILE * stream, PVec vec);
void vec_save2(FILE * fout, PVec x, PVec y);
PVec polyval_horner(PVec a, PVec x);

/*
PVec polyval(PVec a, PVec x);
*/