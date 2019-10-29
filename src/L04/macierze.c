#include <stdio.h>
#include <stdlib.h>



/* Zadanie: wczytaj dwa wektory z plików, oblicz sume 
i zapisz wynik do trzeciego pliku. */

/* Magic numbers :-) */
#define MAX 100

void wczytaj(float v[], int *n, char nazwa_pliku[]) {
    FILE * fin = fopen(nazwa_pliku, "r");
    int liczba;
    int i;
    float wartosc;
    fscanf(fin, "%d", &liczba);
    *n = liczba;

    for (i=0; i< liczba;i++) {
        fscanf(fin, "%f", &wartosc);
        v[i] = wartosc;
    }
    fclose(fin);
}


void wypisz(int n, float v[]) {
    int i;
    for (i = 0; i < n; i++) {
        printf("v[%d] = %f\n", i, v[i]);
    }
}


int main(int argc, char *argv[]) {
    /* float v1[100]; */
    float v1[MAX];
    int n1;
    float v2[MAX];
    int n2;
    float v3[MAX];
    int n3;

    wczytaj(v1, &n1, argv[1]);
    /*
    wczytaj(v2, &n2, argv[2]);
    suma(v1,v2,v3,n1);
    zapisz(v3,n3, argv[3]);
    */
    wypisz(n1, v1);

    return 0;
}