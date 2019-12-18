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

int main(int argc, char** argv) {
    struct Lista * head = nowy(10.4);
    head->nast = nowy(11.1);

    wypisz(head);
    return 0;
}