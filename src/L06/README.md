1. Struktury. Struktura zawierająca studentów i tablicę ocen.

Struktura o statycznym rozmiarze.
```c
struct Student {
	char imie[50];
	char nazwisko[50];
	char nr_albumu[50];
	float srednia;
	int liczba_ocen;
	float oceny[20];
	int ects[20];
	char przedmioty[20][50];
	char kto_wystawil[20][50];
};	
```
Teraz napiszemy program, który z poniższego pliku wczyta informacje o studentach obliczy dla każdego średnią i wyświetli średnią całkowitą.

```
3
Jan Kowalski 234567
4
Matematyka dyskretna;4.5;4;Prof.Sasin
Podstawy informatyki;3.0;2;Prof.Starzyński
Fizyka;3.0;4;Prof.Starzyński
Język obcy;5.0;2;Prof.Słonimska
Aleksander Wielki 234568
2
Matematyka dyskretna;5.0;4;Prof.Sasin
Podstawy informatyki;2.0;2;Prof.Starzyński
Maria-Curie Skłodowska 234569
3
Matematyka dyskretna;5.0;4;Prof.Sasin
Podstawy informatyki;2.0;2;Prof.Starzyński
Teoria obwodów i sygnalów;4.0;4;Prof.Osowski
```

W trakcie pisania postaramy się najlepiej jak się da zabezpieczać program przed ewentualnymi błędami. Użyjemy funkcji:

```
fopen
strtok
fgets
fopen
strcpy
strncpy
```

Napiszemy następujące funkcje:

```c
int wczytaj_studentow(FILE *fin, struct Student tab[50]) {
    ...
}

int zapisz_zapisz(FILE *fin, struct Student tab[50], int n) {
    ...
}

int oblicz_srednie(struct Student tab[50], int n) {
    ...
}

int oblicz_srednia_calkowita(struct Student tab[50], int n) {
    ...
}

```



2. Podzielimy program na pliki. Wprowadzimy pliki nagłówkowe `(*.h)` i źródłowe `(*.c)`. Dodatkowo, aby nasz program było łatwiej kompilować utworzymy `Makefile`a.

Pliki ngałówkowe zawierają tylko **deklaracje** a pliki źródłowe **definicje** funkcji i zmiennych. Deklaracje to tylko opis jak będziemy mogli rozmawiać z funkcją (czyli jakich argumentów będzie funkcja potrzebować) oraz jakiego typu wartości funkcja będzie zwracać. Definicja to opis jak ma funkcja działać.

```
Makefile
main.c
baza.c
baza.h
test.c
```

Będziemy teraz wpisywać komendę:

```bash
make
```

3. Struktura dynamiczna. Teraz napiszemy ten sam program ale w wersji dynamicznej.

```c
struct Student {
	char *imie;
	char *nazwisko;
	char *nr_albumu;
	float srednia;
	int liczba_ocen;
	float *oceny;
	char **przedmioty;
	char **kto_wystawil;
};	
```

Struktura `Student` z zagnieżdżoną strukturą.

```c
struct Ocena {
	float oceny;
	char *przedmiot;
	char *kto_wystawil;
};

struct Student {
	char *imie;
	char *nazwisko;
	float srednia;
	int liczba_ocen;
	struct Ocena *oceny;
};	
```

Materiał fakultatywny:
----------------------

1. Czytanie z pliku. Zabezpieczanie programu przed błędami użytkownika. Ćwiczenie wskaźników do zmiennych.

```c
// czyta z pliku (albo z stdin gdy nie podano nazwy) pary liczb (u,i)
// i wypisuje do pliku (albo na stdout gdy nie podano nazwy)
// trójki liczb (u,i, u/i)

#include <stdio.h>

int main( int argc, char *argv[] ) {
        double u,i;
        FILE *in = argc > 1 ? fopen( argv[1], "r" ) : stdin;
        FILE *ou = argc > 2 ? fopen( argv[2], "w" ) : stdout;
        char *progname= argv[0];

        if( in == NULL ) {
                fprintf( stderr, "%s: Błąd: nie mogę otworzyć \"%s\" do czytania\n", progname, argv[1] );
                return 1;
        }

        if( ou == NULL ) {
                fprintf( stderr, "%s: Błąd: nie mogę otworzyć \"%s\" do pisania\n", progname, argv[2] );
                return 2;
        }

        while( fscanf( in, "%lf %lf", &u, &i ) == 2 )
                fprintf( ou, "%g\t%g\t%g\n", u, i, u/i );

        if( !feof(in) ) {
                fprintf( stderr, "Błąd: jakieś śmieci w pliku %s\n", argv[1] );
                return 3;
        }

        fclose( in );
        fclose( ou );

        return 0;
}
```

2. Test funkcji wczytującej.

```c
// TYLKO TEST FUNKCJI WCZYTUJĄCEJ !!!

#include <stdio.h>

//czytanie danych
int czytajxy( FILE *in, double *x, double *y, int max ) {
        int n= 0;
        int bfs= 0;

        while( n < max && (bfs= fscanf( in, "%lf %lf", &x[n], &y[n] )) == 2 )
                n++;

        if( bfs == EOF || feof(in) )
                return n;
        else
                return -n;
}

#define MAX 10

int main( int argc, char **argv ) {
        double x[MAX];
        double y[MAX];

        FILE *in= argc > 1 ? fopen( argv[1], "r" ) : stdin;

        printf( "czytajxy zwróciła %d\n", czytajxy( in, x, y, MAX ) );

        return 0;
}
```

2. Dynamiczna alokacja pamięci - malloc, realloc.

```c
// Zwinne Czytanie - czytamy wektor o niewiadomo jakiej
// długości

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
        FILE *in= argc > 1 ? fopen(argv[1],"r") : stdin;

        int i= 0;  // ile liczb przeczytaliśmy
        
        double *w= malloc( 10 * sizeof(double) ); // tu przechowujemy
        int size = 10; // tyle mamy miejsca w w

        double x; // tymczasowa zmienna uzywana przy czytaniu

        if( in == NULL || w == NULL )
                return EXIT_FAILURE;

        while( fscanf( in, "%lf", &x ) == 1 ) {
                if( i == size ) {
                        double *tmp= realloc( w, 2*size*sizeof(double) );
      if( tmp == NULL ) {
                                fprintf( stderr, "Blad przy probie powiekszenia w do wielkosci %d\n", 2*size );
                                return EXIT_FAILURE;
                        }
                        w= tmp;
                        size *= 2;
                }
                w[i++]= x;
        }

        printf( "Przeczytano %d liczb, wektor w ma dlugosc = %d\n", i, size );
        return EXIT_SUCCESS;
}
```

3. Regresja liniowa

main.c:
```c
// regresja liniowa: czyta plik zawierający pary x_i, y_i
// wyznacza współczynniki a i b takie, aby zminimalizować
// błąd średniokwadratowy sum_i (ax_i+b - y_i)^2

#include <stdio.h>
#include "vlib.h"
#include "alib.h"

#define MAX 1000

int main( int argc, char **argv ) {
	double x[MAX];
	double y[MAX];
	int n;
	double a, b;

	FILE *in= argc > 1 ? fopen( argv[1], "r" ) : stdin;

	if( (n= czytajxy( in, x, y, MAX ))  <= 0 ) {
		fprintf( stderr, "%s: błędne dane - przeczytano %d par liczb i napotkano błąd.\n", argv[0], -n );
		return -1;
	}

#ifdef DEBUG
	printf( "W pliku wejsciowym znaleziono %d par liczb\n", n );
#endif

	reg_lin( x, y, n, &a, &b );

	printf( "Regresja liniowa danych: y = %g * x + %g\n", a, b );

	return 0;
}
```

vlib.c:
```c
// Prosta biblioteczka funkcji czytających i piszących wektory

#include <stdio.h>
#include "vlib.h"

//czytanie danych
int czytajxy( FILE *in, double *x, double *y, int max ) {
	int n= 0;
	int bfs= 0;
	double t1, t2;

	while( (bfs= fscanf( in, "%lf %lf", &t1, &t2 )) == 2 )
		if( n == max )
			return -max;
		else {
			x[n]= t1;
			y[n]= t2;
			n++;
		}

	if( bfs == EOF )
		return n;
	else
		return -n;
}
```

vlib.h:
```c
#ifndef __VLIB_H__
#define __VLIB_H__

#include <stdio.h>

int czytajxy( FILE *in, double *x, double *y, int max );

#endif
```

alib.c:
```c
#include "alib.h"

// wyznacza współczynniki a i b takie, aby zminimalizować
// błąd średniokwadratowy sum_i (ax_i+b - y_i)^2
void reg_lin( double *x, double *y, int n, double *a, double *b ) {
  int i;
	double sx= 0, sxx= 0, sxy= 0, sy= 0;

  *a= *b= 0;

  if( n < 2 )
    return;

  for( i= 0; i < n; i++ ) {
    sx+= x[i];
    sxx+= x[i]*x[i];
    sxy+= x[i]*y[i];
    sy+= y[i];
  }

  double w = n*sxx-sx*sx;

  *a= (n*sxy-sx*sy)/w;
  *b= (sxx*sy-sx*sxy)/w;
}
```

alib.h:

```c
#ifndef ALIB_H
#define ALIB_H

void reg_lin( double *x, double *y, int n, double *a, double *b );

#endif
```

Makefile:
```c
#DEBUGFLAGS= -DDEBUG

CFLAGS= -Wall $(DEBUGFLAGS)

rl: main.o vlib.o alib.o
        $(CC) $(COPT) main.o vlib.o alib.o -o rl

main.o: main.c vlib.h alib.h
vlib.o: vlib.h
alib.o: alib.h

test: rl ../flin
        ./rl ../flin
```
