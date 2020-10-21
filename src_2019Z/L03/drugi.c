#include <stdio.h>
#include <stdlib.h>
double iloczyn(int n, double v[]) {
    int i;
    double p = 1;

/*    for (i = 0; i < n; i++) {
        p = p * v[i];
    }
*/
    i = 0;
    while(i < n) {
        p = p * v[i];
        i = i + 1;
        /* i += 1; */
        /* i++; */
        /*++i; */
    }
    
    /*
    i = 0;
    do {
        p = p * v[i];
        i = i + 1;
        v = (i++)*3
    } while(i < n);
    */

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

/* Interpretacja danych użytkownika. */
void wczytaj(int n, double v[], char *argv[]) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = atof(argv[i+1]);
    }
}

void zapisz(int n, double v[]) {
    int i;
    FILE * fout;
    fout = fopen("wektor.txt", "w");
    for (i = 0; i < n; i++) {
        fprintf(fout, "%lf\n", v[i]);
    }
    fclose(fout);
}

int main(int argc, char *argv[]) {
    int n = argc-1;
    double v[n];

    wczytaj(n,v,argv);
    wypisz(n,v);
    printf("Suma = %lf\n", suma(n,v) );
    printf("Iloczyn = %lf\n", iloczyn(n,v) );

    zapisz(n,v);

    return 0;
}