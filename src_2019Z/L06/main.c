#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define DEBUG */

// #define PDEBUG(x) printf(x);

struct Student {
    char imie[50];
    char nazwisko[50];
    char nr_albumu[10];

    float srednia;

    int liczba_ocen;
    float oceny[20];
    int ects[20];
    char przedmioty[20][50];
    char kto_wystawil[20][50];
};

int wczytaj(char *fname, struct Student studenci[]) {
    int n = 0, i, o;
    FILE *fin = fopen(fname, "r");
    char bufor[255];
    char *w;

    w = fgets(bufor, 254, fin);

    #ifdef DEBUG
        printf("Wczytałem z pliku napis: %s\n", bufor);
    #endif

    n = atoi(bufor);

    #ifdef DEBUG
        printf("Wczytałem z pliku liczbę: %d\n", n);
    #endif

// float liczba;
// fscanf("%f", &liczba);

    for (i = 0; i < n; i++) {
        fgets(bufor, 254, fin);
        #ifdef DEBUG        
            printf("Wczytałem z pliku dane studenta: %s\n", bufor);
        #endif

        /* sscanf(bufor, "%s %s %s", &studenci[i].imie[0], studenci[i].nazwisko, studenci[i].nr_albumu); */
        sscanf(bufor, "%s %s %s", studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_albumu);

        #ifdef DEBUG
            printf("Dane studenta w strukturze[%d]: imie: %s, nazwisko: %s, nr_albumu: %s\n", 
                    i, studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_albumu);
        #endif

        fgets(bufor, 254, fin);
        studenci[i].liczba_ocen = atoi(bufor);   

        for (o = 0; o < studenci[i].liczba_ocen; o++) {
            fgets(bufor, 254, fin);
            #ifdef DEBUG        
                printf("Wczytałem z pliku oceny[%d]: %s\n", o, bufor);
            #endif
            w = strtok(bufor, ";");
            strcpy(studenci[i].przedmioty[o], w);
            w = strtok(NULL, ";");
            studenci[i].oceny[o] = atof(w);
            w = strtok(NULL, ";");
            studenci[i].ects[o] = atoi(w);
            w = strtok(NULL, ";");
            strcpy(studenci[i].kto_wystawil[o], w);
        }     
    }

    return n;
}

void wypisz_na_ekran(struct Student s[], int n) {
    int i,j;
    for (i=0; i < n; i++) {
        printf("%s %s - %s\n", s[i].imie, s[i].nazwisko, s[i].nr_albumu);
        for (j=0; j < s[i].liczba_ocen; j++) {
            printf("\t%s: %.0f (%d ECTS)\n", s[i].przedmioty[j], s[i].oceny[j], s[i].ects[j]);
        } 
    }
}

int main(int argc, char *argv[]) {
    int n;
    struct Student studenci[20];


    /* n = wczytaj(argv[1], studenci); */
    n = wczytaj(argv[1], &studenci[0]);
    wypisz_na_ekran(studenci, n);

    printf("Rozmiar tablicy to %ld\n", sizeof(struct Student));

    return 0;
}