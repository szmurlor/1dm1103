#include <stdio.h>
#include <stdlib.h>

typedef struct _Lista {
	double v;
	struct _Lista * n;
} Lista, *PLista;

PLista nowy(double v) {
	PLista n = (PLista) malloc(sizeof(Lista));
	n->n = NULL;
	n->v = v;

	return n;
}

PLista dodaj(PLista head, double v) {
	if (head == NULL) {
		// lista pusta
		head = nowy( v );
	} else {
		// lista już coś ma, idziemy na koniec i dodajemy
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

int main(int argc, char ** argv) {
	int i;
	PLista head = NULL;
	for (i = 1; i < argc; i++) 
		head = dodaj(head, atof( argv[i] ));

	wypisz(head);

	return 0;
}

