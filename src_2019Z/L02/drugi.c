#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;
    double s = 0;
    double p = 1;
    int n = argc-1;
    double v[n];

    /* Interpretacja danych użytkownika. */
    for (i = 0; i < n; i++) {
        v[i] = atof(argv[i+1]);
    }

    for (i = 0; i < n; i++) {
        /* double l = atof(argv[i]) ; 
        s = s + l;
        p = p * l;
        */
        s = s + v[i];
        p = p * v[i];
    }

    for (i = 0; i < n; i++) {
        printf("v[%d] = %lf\n", i, v[i]);
    }

    printf("Suma = %lf\n", s);
    printf("Iloczyn = %lf\n", p);

    return 0;
}