#include "bibl_vec.h"
#include <utils.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PVec vec_new(int size) {
    debug("Tworzę nowy wektor zgodnie z implmentacją LISTY JEDNOKIERUNKOWEJ\n");

    int i;

    PVec v = (PVec) malloc(sizeof(Vec));
    v->n = 0;
    v->head = NULL;

    for (i=0; i < size; i++)
        vec_append(v, 0.0);

    return v;
} 

void vec_free(PVec vec) {
    PVecItem cur = vec->head;
    PVecItem next;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }

    free(vec);
}

void vec_debug(PVec v) {
    printf("DEBUG: v: n=%d, head=%p\n", v->n, v->head);
}

void vec_append(PVec v, double d) {
    // najpierw utworzymy nowy element
    PVecItem item = (PVecItem) malloc(sizeof(VectItem));
    item->next = NULL;
    item->v = d;

    // a potem go podepniemy albo na poczatek 'kolejki' albo na 'koniec'
    if (v->head == NULL) {
        v->head = item;
    } else {
        PVecItem cur = v->head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = item;
    }    
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
    PVecItem cur = vec->head;
    fprintf(out, "[");
    while (cur != NULL) {
        fprintf(out, "%f%s", cur->v, i < (vec->n-1) ? "," : "");
        cur = cur->next;
        i++;
    }
    fprintf(out, "]\n");
}

void vec_save2(FILE * fout, PVec v1, PVec v2) {
    int i;
    PVecItem cur1 = v1->head;
    PVecItem cur2 = v2->head;
    for (i = 0; i < MIN(v1->n, v2->n); i++) {
        fprintf(fout, "%lf, %lf\n", cur1->v, cur2->v);
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
}

double get_item(PVec vec, int i) {
    if (i < vec->n) {
        PVecItem cur = vec->head;
        while (i > 0) {
            cur = cur->next;
            i--;
        }
        return cur->v;
    } else {
        /* Jakie to programowanie: ofensywne czy defensywne? */
        fprintf(stderr, "Uwaga! Przekroczony zakres wektora %d (maks: %d)\n", i, vec->n);
        return 0.0;
    }
}

void set_item(PVec vec, int i, double d) {
    if (i < vec->n) {
        PVecItem cur = vec->head;
        while (i > 0) {
            cur = cur->next;
            i--;
        }
        cur->v = d;
    } else {
        /* Jakie to programowanie: ofensywne czy defensywne? */
        fprintf(stderr, "Uwaga! Przekroczony zakres wektora %d (maks: %d)\n", i, vec->n);
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
        set_item(f,i, get_item(a, a->n-1)); // f[i] = a[a->n-1]
        for (j = a->n - 2; j >=  0; j--) {
            set_item(f, i, get_item(a,j) + get_item(x,i) * get_item(f, i)); // f[i] = a[j] + x[i]*f[i]
        }
    }

    return f;
}
