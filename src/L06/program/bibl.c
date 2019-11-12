#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bibl.h"

int wczytaj(char *fname, struct Student studenci[]) {
    int n = 0, i, o;
    FILE *fin = fopen(fname, "r");
    char bufor[255];
    char *w;

    w = fgets(bufor, 254, fin);
    n = atoi(bufor);

    for (i = 0; i < n; i++) {
        fgets(bufor, 254, fin);
        sscanf(bufor, "%s %s %s", studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_albumu);

        fgets(bufor, 254, fin);
        studenci[i].liczba_ocen = atoi(bufor);   

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

void wypisz_na_ekran(struct Student s[], int n) {
    int i,j;
    // struct Ocena o;
    struct Ocena *o;
    for (i=0; i < n; i++) {
        printf("%s %s - %s\n", s[i].imie, s[i].nazwisko, s[i].nr_albumu);
        for (j=0; j < s[i].liczba_ocen; j++) {
            // o = s[i].oceny[j];
            // printf("\t%s: %.0f (%d ECTS)\n", o.przedmiot, o.ocena, o.ects);
            o = &s[i].oceny[j];
            printf("\t%s: %.0f (%d ECTS)\n", o->przedmiot, o->ocena, o->ects);
        } 
    }
}