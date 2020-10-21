#ifndef _BIBL_VEC_H
#define _BIBL_VEC_H

#include <stdio.h>
#include <math.h>

#ifdef VEC_LIST
    #include "bibl_vec_list.h"
#else
    #include "bibl_vec_array.h"
#endif

PVec vec_new(int size);
void vec_free(PVec v);
void vec_append(PVec v, double d);
PVec vec_read(FILE * fin);
void vec_print(FILE * stream, PVec vec);
void vec_save2(FILE * fout, PVec x, PVec y);
PVec polyval_horner(PVec a, PVec x);

#endif