#ifndef _BIBL_VEC_ARRAY_H
#define _BIBL_VEC_ARRAY_H

typedef struct _Vec {
    int n;
    int _size;
    double *items;
} Vec, *PVec;

#endif