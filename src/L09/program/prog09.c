#include <stdio.h>
#include <stdlib.h>
#include "bibl.h"

#define MAX_SIZE 50

void print_help_and_exit(char *pname) {
    printf("Użycie programu:\n"
           "\t%s a x wynik\n"
           "gdzie:\n"
           "\t * a - nazwa pliku ze współczynnikami a\n"
           "\t * x - nazwa pliku z wektorem współrzędnych x\n"
           "\t * wynik - nazwa pliku gdzie maja zostac wypisane wyniki\n"
           , pname);
           
    exit(-1);
}

FILE * open_with_exit(char *fname, char *description, char *mode) {
    FILE * res = fopen(fname, mode);
    if (res == NULL) {
        printf("Nie mogę otworzyć pliku %s o nazwie %s w trybie [%s].\n", fname, description, mode);
        exit(-1);
    }
    return res;
}

int main(int argc, char ** argv) {
    FILE *fa, *fx, *fwynik;
    double a[MAX_SIZE];
    double x[MAX_SIZE];
    double f[MAX_SIZE];

    int na;
    int nx;

    if (argc < 4) 
        print_help_and_exit(argv[0]);

/*
    if ((fa = fopen(argv[1], "r")) == NULL) {
        printf("Nie mogę otworzyć pliku ze współczynnikami %s\n.", argv[1])
        exit(-1);
    }
*/
    fa = open_with_exit(argv[1], "ze współczynnikami", "r");
    fx = open_with_exit(argv[2], "z wektorem współczynników x", "r");
    fwynik = open_with_exit(argv[3], "do zapisania wyników", "w");

    na = read_vec(fa, a, MAX_SIZE);
    nx = read_vec(fx, x, MAX_SIZE);
    polyval(a, na, x, nx, f);
    //save_2vecs(fwynik, x, f, nx);
    save_2vecs(fwynik, x, f, nx);

    fclose(fa);
    fclose(fx);
    fclose(fwynik);

    return 0;
}