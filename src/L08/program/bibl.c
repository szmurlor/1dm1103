#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bibl.h"

int wczytaj(char *fname, struct Student studenci[]) {
    int n = 0, i, o;
    FILE *fin;
    char bufor[255];
    char *w;
    int p;

    if ((fin = fopen(fname, "r")) == NULL) {
        printf("Nie mogę otworzyć pliku %s\n", fname);
        exit(2);
    }

    w = fgets(bufor, 254, fin);
    n = atoi(bufor);

    for (i = 0; i < n; i++) {
        if (feof(fin)) {
            printf("Nieoczekiwane zakończenie pliku %s dla studenta %d (oczekiwałem %d studentów)\n", fname, i, n);
            exit(3);
        }
        if (fgets(bufor, 254, fin) == NULL) {
            printf("Nie udało mi się wczytać linijki z informacją o studencie %s dla studenta %d (oczekiwałem %d studentów)\n", fname, i, n);
            exit(4);
        };
        if (3 != (p = sscanf(bufor, "%s %s %s", studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_albumu))) {
            printf("Niewłaściwa liczba kolumn w linijce o studencie "
            "(oczekiwałem 3 słów otrzymałem %d) "
            " dla studenta %d\n", p, i);
            exit(4);
        };

        if (fgets(bufor, 254, fin) == NULL) {
            printf("Oczekiwałem liczby ocen a nastąpił koniec pliku.\n");
            exit(5);
        };
        studenci[i].liczba_ocen = atoi(bufor);   
        studenci[i].srednia = 0;

        for (o = 0; o < studenci[i].liczba_ocen; o++) {
            fgets(bufor, 254, fin);

            w = strtok(bufor, ";");
            strcpy(studenci[i].oceny[o].przedmiot, w);
            w = strtok(NULL, ";");
            studenci[i].oceny[o].ocena = atof(w);
            w = strtok(NULL, ";");
            studenci[i].oceny[o].ects = atoi(w);
            w = strtok(NULL, ";");
            strcpy(studenci[i].oceny[o].kto_wystawil, w);
        }     
    }

    return n;
}

void wypisz_na_ekran_srednie(struct Student s[], int n) {
    int i;
    struct Ocena *o;
    for (i=0; i < n; i++) {
        printf("%s %s - %s = %f\n", s[i].imie, s[i].nazwisko, s[i].nr_albumu, s[i].srednia);
    }
}

void wypisz_na_ekran(struct Student s[], int n) {
    int i,j;
    // struct Ocena o;
    struct Ocena *o;
    for (i=0; i < n; i++) {
        printf("%s %s - %s\n", s[i].imie, s[i].nazwisko, s[i].nr_albumu);
        for (j=0; j < s[i].liczba_ocen; j++) {
            o = &s[i].oceny[j];
            printf("\t%s: %.1f (%d ECTS)\n", o->przedmiot, o->ocena, o->ects);
        } 
        printf("\tśrednia ważona: %f\n", s[i].srednia);
    }
}

void oblicz_srednie(struct Student s[], int n) {
    int i;
    for (i=0; i < n; i++) {
        float sumaoc = 0, sumaects = 0;
        int j;
        for (j=0; j < s[i].liczba_ocen; j++) {
            sumaoc += s[i].oceny[j].ocena * s[i].oceny[j].ects;
            sumaects += s[i].oceny[j].ects; 
        } 
        if (sumaects == 0)
            s[i].srednia = 0;
        else
            s[i].srednia = sumaoc / sumaects;
        
        s[i].srednia = (sumaects == 0 ? 0 : sumaoc / sumaects);
    }
}

void sortuj_babelkowo(struct Student s[], int n) {
    int i,j;
    struct Student tmp;

    for (i=0; i < (n-1); i++) {
        for (j=0; j < (n-1); j++) {
            if (s[j].srednia < s[j+1].srednia) {
                tmp = s[j];
                s[j] = s[j+1];
                s[j+1] = tmp;
            }
        }
    }
}

void sortuj_babelkowo_rosnaco(struct Student s[], int n) {
    int i,j;
    struct Student tmp;

    for (i=0; i < (n-1); i++) {
        for (j=0; j < (n-1); j++) {
            if (s[j].srednia > s[j+1].srednia) {
                tmp = s[j];
                s[j] = s[j+1];
                s[j+1] = tmp;
            }
        }
    }
}

void _zamien(struct Student *s1, struct Student *s2) {
    struct Student tmp;
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

/*
  kierunek=1 - sortowanie malejaco 
  kierunek=-1 - sortowanie rosnaco 
*/
void sortuj_babelkowo_kierunek_naiwnie(struct Student s[], int n, int kierunek) {
    int i,j;
    struct Student tmp;

    for (i=0; i < (n-1); i++) {
        for (j=0; j < (n-1); j++) {
            if (kierunek == MALEJACO) {
                if (s[j].srednia < s[j+1].srednia) {
                    // tmp = s[j];
                    // s[j] = s[j+1];
                    // s[j+1] = tmp;
                    _zamien(&s[j], &s[j+1]);
                }
            } else {
                if (s[j].srednia > s[j+1].srednia) {
                    // tmp = s[j];
                    // s[j] = s[j+1];
                    // s[j+1] = tmp;
                    _zamien(&s[j], &s[j+1]);
                }
            }
        }
    }
}

void sortuj_babelkowo_kierunek(struct Student s[], int n, int kierunek) {
    int i,j;
    struct Student tmp;

    for (i=0; i < (n-1); i++)
        for (j=0; j < (n-1); j++)
            if ( kierunek*(s[j+1].srednia - s[j].srednia) > 0 )
                _zamien(&s[j], &s[j+1]);
}