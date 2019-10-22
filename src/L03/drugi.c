#include <stdio.h>
#include <stdlib.h>
double iloczyn(int n, double v[]) {
    int i;
    double p = 1;

    for (i = 0; i < n; i++) {
        p = p * v[i];
    }

    return p;
}


double suma(int n, double v[]) {
    int i;
    double s = 0;

    for (i = 0; i < n; i++) {
        s = s + v[i];
        /*p = p * v[i];*/
    }

   /* printf("W sumie: %lf\n", s); */

    return s;
}

void wypisz(int n, double v[]) {
    int i;
    for (i = 0; i < n; i++) {
        printf("v[%d] = %lf\n", i, v[i]);
    }
}

int main(int argc, char *argv[]) {
    int i;
    int n = argc-1;
    double v[n];

    /* Interpretacja danych użytkownika. */
    for (i = 0; i < n; i++) {
        v[i] = atof(argv[i+1]);
    }

    wypisz(n,v);
    printf("Suma = %lf\n", suma(n,v) );
    printf("Iloczyn = %lf\n", iloczyn(n,v) );

    return 0;
}