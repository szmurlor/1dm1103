#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bibl.h"
/*
Uwaga! Zadanie domowe:

Proszę napisać i użyć w main() funkcję, która dla każdego studenta obliczy wartość średniej ważonej punktami ECTS 
i zapisze ją w polu 'srednia' struktury danego studenta.

Dodatkowo, proszę zmodyfikować funkcję wypisującą na ekranie bazę danych o studentach tak aby
wyświetlała również informację o średniej ważonej punktami ECTS, np. tak:

Maria Curie Skłodowska, 234589
    Matematyka: 5.0 (4 ECTS)
    Język obcy: 4.0 (2 ECTS)
    Średnia ważona ECTS: 4.666


Średnia ważona ECTS powinna być obliczona ze wzoru:
srednia = suma( ocena * ects ) / suma(ects)

Czyli dla powyzszego przykładu:
srednia = (5*4 + 4*2)/6 = 4.666

Zastanów się jakie argumenty nowa funkcja powinna dostawać i ewentualnie czy potrzebuje 
zwracać jakikolwiek wynik za pomocą 'return'.
*/

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
        s[i].srednia = sumaoc / sumaects;
    }
}
