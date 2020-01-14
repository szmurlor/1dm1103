Seminarium 12

Plan:

## Powtórzmy jeszcze raz listę jednokierunkową od samego początku. 

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct _Lista {
	double v;
	struct _Lista * n;
} Lista, *PLista;

int main(int argc, char ** argv) {
	int i;
	PLista head = NULL;
	for (i = 1; i < argc; i++) {
		if (head == NULL) {
			// lista pusta
			head = (PLista) malloc(sizeof(Lista));
			head->n = NULL;
			head->v = atof( argv[i] );
		} else {
			// lista już coś ma, idziemy na koniec i dodajemy
			PLista tmp = head;
			while (tmp->n != NULL)
				tmp = tmp->n;
			tmp->n = (PLista) malloc(sizeof(Lista));
			tmp->n->v = atof( argv[i] );
			tmp->n->n = NULL;
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
```

Zrefaktorujemy teraz kod. Naprawimy problemy metodologiczne:

1. Widzimy, że mamy fragmenty kodu tworzącego nowy element (ten z malloc), prawie takie same. Warto napisać funkcję tworzącą nowy element listy. Na przykład tak:

   ```c
   PLista nowy(double v) {
   	PLista n = (PLista) malloc(sizeof(Lista));
   	n->n = NULL;
   	n->v = v;
   
   	return n;
   }
   ```

2. Potem napiszemy funkcję do dodawania nowego elementu do listy.

   ```c
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
   
   ```

3. Potem napiszemy funkcję wypisującą na ekran.

   ```c
   void wypisz(PLista head) {
   	PLista tmp = head;
   	int i = 0;
   	while (tmp != NULL) {
   		printf("lista[%d] = %lf\n", i++, tmp->v);
   		tmp = tmp->n;
   	}
   }
   ```

   

4. Na koniec napiszemy funkcję zwalniająca pamięć.

   ```c
   void zwolnij(PLista head) {
   	PLista tmp = head;
   	while (tmp != NULL) {
   		tmp = tmp->n;
   		free(head);
   		head = tmp;
   	}
   }
   ```

5. Ostatecznie nasza funkcja  `main` będzie wyglądać:

   ```c
   int main(int argc, char ** argv) {
   	int i;
   	PLista head = NULL;
   	for (i = 1; i < argc; i++) 
   		head = dodaj(head, atof( argv[i] ));
   	wypisz(head);
   	zwolnij(head);
   
   	return 0;
   }
   
   ```



## Kończymy strukturę danych reprezentującą wektor danych za pomocą kolejki (lista liczb typu double),

To jest dokończenie seminarium 11.