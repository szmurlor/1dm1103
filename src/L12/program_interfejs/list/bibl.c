#include "bibl.h"
#include "../../wspolne/utils.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

void free_items(PVecItem i) {
    PVecItem t = i;
    while (t != NULL) {
        i = t;
        t = t->n;
        free(i);
    }
}

void free_vec(PVec v) {
    free_items(v->head);
    free(v);
}

PVecItem new_item(double d) {
    PVecItem i = (PVecItem) malloc(sizeof(VecItem));
    i->n = NULL;
    i->v = d;
    return i;
}

void vec_append(PVec v, double d) {
    // PVecItem head = v->head;
    if (v->head == NULL) {
        v->head = new_item(d);
        v->n = 1;
    }  else {
        PVecItem tmp = v->head;
        while (tmp->n != NULL)
            tmp = tmp->n;
        tmp->n = new_item(d);
        v->n += 1;
    }
}

void vec_insert(PVec v, double d, int j) {
    // zaimplementowac wstawianie na jtym miejscu
}

PVec vec_new() {
    printf("Tworzę nowy wektor w wariancie wariackim z listą!!!\n");
    PVec v = (PVec) malloc(sizeof(Vec));
    v->head = NULL;
    v->n = 0;
    return v;
}

PVec read_vec(FILE * fin){
    double d;
    PVec v = vec_new();

    while ( fscanf(fin, "%lf", &d) == 1)
        vec_append(v, d);
    
    return v;
}


void save_2vecs(FILE * fout, PVec x, PVec y) {
    int i;
    PVecItem xh = x->head;
    PVecItem yh = y->head;
    for (i = 0; i < x->n; i++) {
        fprintf(fout, "%lf, %lf\n", xh->v, yh->v);
        xh = xh->n;
        yh = yh->n;
    }
}

/*
 
 Funkcja oblicza wartość wielomianu, o współczynnikach w wektorze a.
 Stopień wielomianu wynika z rozmiaru wektora współczynników a.
 Wielomian jest postaci:

 p(x) = a[0] + a[1]*x + a[2]*x^2 + ... a[na] * x^(na-1)

*/

double get_item(PVec v, int i) {
    PVecItem t = v->head;
    int j = 0;
    for (j=0; j < i; j++) {
        t = t->n;
    }
    return t->v;
} 

/*
Schemat Hornera - redukcja błędu zaookrągleń
*/
PVec polyval_horner(PVec a, PVec x ) {
    int i, j;    
    PVec f = vec_new();

    debug("Liczę schematem Hornera.\n");
    for (i=0; i < x->n; i++) {
        double nf = get_item(a, a->n-1); //nowa wartość f
        for (j = a->n-2; j >=  0; j--) {
            nf = get_item(a,j) + get_item(x, i) * nf;
        }
        vec_append(f, nf) ;
    }

    return f;
}

