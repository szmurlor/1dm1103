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

int main(int argc, char ** argv) {
	int i;
	PLista head = NULL;
	for (i = 1; i < argc; i++) {
		if (head == NULL) {
			// lista pusta
			head = nowy( atof(argv[i]) );
		} else {
			// lista już coś ma, idziemy na koniec i dodajemy
			PLista tmp = head;
			while (tmp->n != NULL)
				tmp = tmp->n;
			tmp->n = nowy( atof(argv[i]) );
		}
	}

	PLista tmp = head;
	i = 0;
	while (tmp != NULL) {
		printf("lista[%d] = %lf\n", i++, tmp->v);
		tmp = tmp->n;
	}

	return 0;
}

