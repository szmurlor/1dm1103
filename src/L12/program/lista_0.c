#include <stdio.h>
#include <stdlib.h>

typedef struct _Lista {
    double v;
    struct _Lista *n;
} Lista, *PLista;

PLista nowy(double v) {
    PLista e = (PLista) malloc(sizeof(Lista));
    e->n = NULL;
    e->v = v;
    return e;
}

// PLista === struct _Lista *

PLista dodaj(PLista head, double v) {
    if (head == NULL)
        return nowy( v );
    else {
        PLista tmp = head;
        while (tmp->n != NULL)
            tmp = tmp->n;
        tmp->n = nowy( v );
    }
    return head;
}

void wypisz(PLista head) {
    PLista tmp = head;
    int i = 0;
    while (tmp != NULL) {
        printf("lista[%d] = %lf\n", i++, tmp->v);
        tmp = tmp->n;
    }
}

void zwolnij(PLista head) {
    PLista tmp = head;
    while (tmp != NULL) {
        head = tmp;
        tmp = tmp->n;
        free(head);
    }
}

/**
* Wywołanie:
  ./lista_0 -1.3 2 3 4 4.1
*/
int main(int argc, char **argv) {
    PLista head = NULL;
    int i;

    for (i = 1; i < argc; i++ )
        head = dodaj(head, atof(argv[i]));

    wypisz(head);    
    zwolnij(head);

    return 0;
}