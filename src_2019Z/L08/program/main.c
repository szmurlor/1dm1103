#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibl.h"

int main(int argc, char *argv[]) {
    int n;
    /*struct Student astudenci[20];*/
    struct Student *studenci;
    studenci = (struct Student*) malloc(20 * sizeof(struct Student));

    if (argc < 2) {
        printf("Użycie programu:\n\t./main [NAZWA PLIKU Z DANYMI]\n");
        exit(1);
    }

    /* n = wczytaj(argv[1], studenci); */
    n = wczytaj(argv[1], &studenci[0]);
    oblicz_srednie(studenci, n);
    // sortuj_babelkowo_rosnaco(studenci, n);
    sortuj_babelkowo_kierunek_naiwnie(studenci, n, MALEJACO);
    sortuj_babelkowo_kierunek_naiwnie(studenci, n, ROSNACO);
    sortuj_babelkowo_kierunek(studenci, n, MALEJACO);
    wypisz_na_ekran_srednie(studenci, n);

    printf("Rozmiar struktury Student to %ld\n", sizeof(struct Student));
    printf("Rozmiar struktury Ocena to %ld\n", sizeof(struct Ocena));

    return 0;
}