/**
 * Uruchomienie programu lista_4 niestety zwraca komunikaty o wycieku pamięci...
 *
 * ```
szmurlor:program_przed$ valgrind ./lista_4 1 2 3 4 3 4
==15004== Memcheck, a memory error detector
==15004== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==15004== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==15004== Command: ./lista_4 1 2 3 4 3 4
==15004==
lista[0] = 1.000000
lista[1] = 2.000000
lista[2] = 3.000000
lista[3] = 4.000000
lista[4] = 3.000000
lista[5] = 4.000000
==15004==
==15004== HEAP SUMMARY:
==15004==     in use at exit: 96 bytes in 6 blocks
==15004==   total heap usage: 7 allocs, 1 frees, 1,120 bytes allocated
==15004==
==15004== LEAK SUMMARY:
==15004==    definitely lost: 16 bytes in 1 blocks
==15004==    indirectly lost: 80 bytes in 5 blocks
 * 
 * `Leak summary` - pokazuje, że tracimy w sumie 96 bajtów...
 *
 */

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

void zwolnij(PLista head) {
	PLista tmp = head;
	while (tmp != NULL) {
		tmp = tmp->n;
		free(head);
		head = tmp;
	}
}

int main(int argc, char ** argv) {
	int i;
	PLista head = NULL;
	for (i = 1; i < argc; i++) 
		head = dodaj(head, atof( argv[i] ));

	wypisz(head);

	zwolnij(head);

	return 0;
}

