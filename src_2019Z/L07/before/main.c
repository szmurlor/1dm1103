#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bibl.h"

int main(int argc, char *argv[]) {
    int n;
    struct Student studenci[20];


    /* n = wczytaj(argv[1], studenci); */
    n = wczytaj(argv[1], &studenci[0]);
    wypisz_na_ekran(studenci, n);

    printf("Rozmiar struktury Student to %ld\n", sizeof(struct Student));
    printf("Rozmiar struktury Ocena to %ld\n", sizeof(struct Ocena));

    return 0;
}