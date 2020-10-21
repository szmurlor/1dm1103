#ifndef _BIBL_VEC_ARRAY_H
#define _BIBL_VEC_ARRAY_H

typedef struct _VecItem {
    double v;
    struct _VecItem * next;
} VectItem, *PVecItem;

typedef struct _Vec {
    int n;
    PVecItem head;
} Vec, *PVec;

#endif