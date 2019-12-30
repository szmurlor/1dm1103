#include <stdio.h>
#include <stdlib.h>
#include "bibl_struct.h"


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
    PVec a, x, f;

    if (argc < 4) 
        print_help_and_exit(argv[0]);

    fa = open_with_exit(argv[1], "ze współczynnikami", "r");
    fx = open_with_exit(argv[2], "z wektorem współczynników x", "r");
    fwynik = open_with_exit(argv[3], "do zapisania wyników", "w");

    a = vec_read(fa);
    x = vec_read(fx);

    vec_print(stdout, a);
    vec_print(stdout, x);

    f = polyval_horner(a, x);
    vec_print(stdout, f);
    vec_save2(fwynik, x, f);

    vec_free(a);
    vec_free(x);
    vec_free(f);

    fclose(fa);
    fclose(fx);
    fclose(fwynik);

    return 0;
}