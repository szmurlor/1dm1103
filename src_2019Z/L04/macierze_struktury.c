#include <stdio.h>
#include <stdlib.h>



/* Zadanie: wczytaj dwa wektory z plików, oblicz sume 
i zapisz wynik do trzeciego pliku. */

/* Magic numbers :-) */
#define MAX 100

typedef struct _Wektor {
    int n;
    float v[MAX];
} Wektor;

void wczytaj(Wektor *w, char nazwa_pliku[]) {
    FILE * fin = fopen(nazwa_pliku, "r");
    int liczba;
    int i;
    float wartosc;
    fscanf(fin, "%d", &liczba);
    w->n = liczba;

    for (i=0; i< liczba;i++) {
        fscanf(fin, "%f", &wartosc);
        w->v[i] = wartosc;
    }
    fclose(fin);
}


void wypisz(Wektor w) {
    int i;
    for (i = 0; i < w.n; i++) {
        printf("v[%d] = %f\n", i, w.v[i]);
    }
}

void suma(Wektor v1, Wektor v2, Wektor *vs) {
    int i;
    for (i = 0; i <v1.n; i++) {
        vs->v[i] = v1.v[i] + v2.v[i];
    }
    vs->n = v1.n;
}

void zapisz(Wektor w, char nazwa_pliku[]) {
    FILE * fout = fopen(nazwa_pliku, "w");
    fprintf(fout, "%d\n", w.n);
    int i;
    for (i = 0; i < w.n; i++) {
        fprintf(fout, "%f\n", w.v[i]);
    }
    fclose(fout);
}

int main(int argc, char *argv[]) {
    Wektor v1;
    Wektor v2;
    Wektor v3;

    wczytaj(&v1, argv[1]);
    wczytaj(&v2, argv[2]);

    suma(v1,v2,&v3);

    zapisz(v3, argv[3]);

    wypisz(v1);
    wypisz(v2);
    wypisz(v3);

    printf("To jest inna wersja tego samego programu.\n");

    return 0;
}