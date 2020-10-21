#include <stdio.h>
#include <stdlib.h>

struct Lista {
    double v;
    struct Lista * nast;
};

struct Lista * nowy(double v) {
    struct Lista * n = (struct Lista*) malloc(sizeof(struct Lista));
    n->v = v;
    n->nast = NULL;

    return n;
}

void wypisz(struct Lista * h) {
    while (h != NULL) {
        printf("Kolejna wartość listy to: %lf\n", h->v);
        h = h->nast;
    }
}

struct Lista * get(struct Lista *h, int i) {

    while ( i > 0) {
        h = h->nast;
        i--;
    }

    return h;
}

int main(int argc, char** argv) {
    struct Lista * head = nowy(1.1);
    head->nast = nowy(-1.4);
    head->nast->nast = nowy(4.1);
    head->nast->nast->nast = nowy(53.87);

    wypisz(head);

    // pamiętajmy, że w C indeksujemy od 0, czyli 'ludzki' pierwszy w C jest 0
    printf("Trzeci element listy to: %f\n", get(head, 2)->v);
    return 0;
}