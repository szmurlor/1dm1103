Plan zajęć L07:

1. Rozwiązujemy zadanie.
2. Omawiamy Makefile i pliki nagłówkowe w kontekście 'include guard' `#ifndef`

```makefile
CC=gcc
CFLAGS=-I.

hellomake: hellomake.o hellofunc.o
     $(CC) -o hellomake hellomake.o hellofunc.o
```

```makefile
CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: hellomake.o hellofunc.o 
	$(CC) -o hellomake hellomake.o hellofunc.o 
```

`$<` - pierwszy element z reguły make

```makefile
CC=gcc
CFLAGS=-I.
DEPS = hellomake.h
OBJ = hellomake.o hellofunc.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
```

```makefile
IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hellomake.o hellofunc.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
```
3. Zabezpieczamy nasz program przed ewentualnymi błędami (programowanie defensywne https://pl.wikipedia.org/wiki/Programowanie_defensywne, https://en.wikipedia.org/wiki/Defensive_programming, Programowanie ofensywne).
4. Postaramy się najlepiej jak się da zabezpieczać program przed ewentualnymi błędami. Użyjemy funkcji:
```
fopen - będziemy sprawdzać wynik
strtok - będziemy sprawdząć wynik
fgets - również wynik
fclose 
strcpy - możemy przekrosczyć bufor
strncpy - nie przekroczymy bufora ale program nie wstawi zera - mogą zostać śmieci.
```

## Klucz do zadania domowego :-)

Zadanie zostało wgrane na githuba do pliku zadanie_zaszyfrowane.txt. Opis zadania został zaszyfrowany banalnym szyfrem Cezara (https://pl.wikipedia.org/wiki/Szyfr_Cezara) z przesunięciem o JEDEN do przodu. Uwaga, szyfr został zrobiony w ten sposób, że przesuwane o jeden w tablicy ASCII są tylko znaki z alfabetu angielskiego czyli 'a',...,'z' oraz 'A',...,'Z' z pominięciem polskich znaków, które pozostały w 'zaszyfrowanym' pliku bez zmian. Innymi słowy 'a' staje się w nowym pliku 'b', 'A' staje się 'B', a litera 'z' i 'Z' stają się odpowiednio 'a' i 'A' (następuje rotacja). Aby poznać treść zadania należy najpierw napisać sobie programik do odszyfrowywania. Proszę nie udostępniać jawnej tresci zadania innym osobom z grupy! Potraktujmy to jako dobrą zabawę (mam nadzieję :-)).

Oto szkielet programu odszyfrowującego:

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *fin = fopen(argv[1],"r");
    char c;
    char c_po_odszyfrowaniu;
    while ((c = fgetc(fin)) != EOF) {
	  /* ... tutaj napiszcie kod odszyfrowujący u mnie ma on 10 linijek  ... */
	  printf("%c",c_po_odszyfrowaniu);
    }
    fclose(fin);
}
```


To zrobimy na następnych zajęciach... :-)

5. Rozszerzymy program o sortowanie po średniej (najpierw naiwne - bąbelkowe, potem użyjemy qsort)

6. Przejdziemy do dynamicznej alokacji pamięci. teraz nasza struktura będzie dynamiczna. Wygodnie będzie podzielić nasz program na funkcje tworzące nowe wektory i dodające nowych studentów do tablicy studentów.

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


1. Struktury. Struktura zawierająca studentów i tablicę ocen.

Struktura o statycznym rozmiarze.
```c
struct Ocena {
    float ocena;
    int ects;
    char przedmiot[50];
    char kto_wystawil[50];
};

struct Student {
    char imie[50];
    char nazwisko[50];
    char nr_albumu[10];

    float srednia;

    int liczba_ocen;
    struct Ocena oceny[20];
};
```

Będziemy dalej pracować na danych przykładowych.

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
