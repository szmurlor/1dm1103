1. Rozszerzymy program o sortowanie po średniej (najpierw naiwne - bąbelkowe, potem użyjemy qsort)

    Dodamy funkcję `sortuj_babelkowo(...)` do pliku nagłówkowego oraz pliku źródłowego. Chcemy liczyć ile wykonamy porównań wartości. (counter++)

    Póżniej dodamy dwie wersje funkcji sortującej: rosnąco i malejąco.
    
    Musieliśmy dodać nowy wpis do pliku nagłówkowego, skopiować i wkleić funkcje wykonując drobną zmianę - MAMY ZDUPLIKOWANY KOD. To jest zła metodyka programowania! Powinniśmy to poprawić.
    
2. Dodamy argument wskazujący czy sortować malejąco czy rosnąco. Tylko jak to zautomatyzować? Zacznijmy od wersji naiwnej - czyli `if ... else`.

```c
/* 
    kierunek = 1 oznacza sortowanie rosnaco
    kierunek = -1 oznacza sortowanie malejaco
 */
int sortuj_babelkowo_kierunek(struct Student *studenci, int n, int kierunek) {
    int changed = 0;
    int counter = 0;
    struct Student tmp;
    int i, j;

    for (i=0; i < (n-1); i++) {
        for (j = 0; j < (n-1); j++) {
            counter++;
            if (kierunek == 1) {
                if (studenci[j].srednia < studenci[j+1].srednia) {
                    changed = 1;
                    tmp = studenci[j];
                    studenci[j] = studenci[j+1];
                    studenci[j+1] = tmp;
                }
            } else {
                if (studenci[j].srednia > studenci[j+1].srednia) {
                    changed = 1;
                    tmp = studenci[j];
                    studenci[j] = studenci[j+1];
                    studenci[j+1] = tmp;
                }
            }
        }
        if (changed == 0)
            break;
    }

    return counter;
}
```

   Problemy: mamy zduplikowany kod - musimy gdzie w komentarzu opisać co znaczy -1 i 1.
   
   Najpierw poprawmy konieczność pamiętania `-1` i `1`. Dodamy stałe wykorzystując makrodyrektywy `#define`. Poniważ wartosci te będziemy wykorzystywać zarówno w naszym pliku `bibl.c` jak i `main.c` najlepszym miejscem będzie zatem plik nagłówkowy `bibl.h`.
   
```c
#define ROSNACO 1
#define MALEJACO -1
```
   
   Druga spraw to zduplikowany kod. Hmmm... użyjmy do pozbycia się zduplikowanego kodu trochę matematyki :-). Przyjmijmy dane, jak poniżej:
   
```   
   Ala Kowalska: 3.5
   Jak Ronowski: 2.0
``` 

   Gdy odejmiemy `3.5` - `2.0` to otrzymamy wartość dodatnią gdy pierwszy element jest większy od drugiego. Zatem wyrażenie:
   
```c
	if (studenci[i].srednia > studenci[i].srednia) { ...	}
```

    możemy zastąpić
    
```c
	if ((studenci[i].srednia - studenci[i].srednia) > 0) { ...	}
```
    a teraz idąc dalej, aby odwrócić porównanie możemy analogicznie:

```c
	if (studenci[i].srednia < studenci[i].srednia) { ...	}
```

    możemy zastąpić
    
```c
	if ((studenci[i].srednia - studenci[i].srednia) < 0) { ...	}
```

    albo jeszcze inaczej :-):

```c
	if (studenci[i].srednia < studenci[i].srednia) { ...	}
```

    możemy zastąpić
    
```c
	if ( -1 * (studenci[i].srednia - studenci[i].srednia) > 0) { ...	}
```

   Jak można zauwazyć, teraz możemy łatwo sterować kierunkiem sortowania użyając zmiennej kierunek, która specjalnie przyjmuje wartości `1` i `-1`. Zatem ostatecznie możemy napisać:
   
```c
/* 
    kierunek = 1 oznacza sortowanie rosnaco
    kierunek = -1 oznacza sortowanie malejaco
 */
int sortuj_babelkowo_kierunek(struct Student *studenci, int n, int kierunek) {
    int changed = 0;
    int counter = 0;
    struct Student tmp;
    int i, j;

    for (i=0; i < (n-1); i++) {
        for (j = 0; j < (n-1); j++) {
            counter++;
            
   	    if ( kierunek*(studenci[j+1].srednia - studenci[j].srednia) > 0) {
	        changed = 1;
	        tmp = studenci[j];
	        studenci[j] = studenci[j+1];
	        studenci[j+1] = tmp;
	    }
        }
        if (changed == 0)
            break;
    }

    return counter;
}
```   
   
3. Teraz poprawimy nasze sortowanie i użyjemy lepszego algorytmu - sortowanie przez wybieranie.

```c
int sortuj_wybieranie_kierunek(struct Student *studenci, int n, int kierunek) {
    int counter = 0;
    struct Student tmp;
    int imax = 0;
    int i, j;

    for (i=0; i < (n-1); i++) {
        imax = i;
        for (j = i+1; j < n; j++) {
            counter++;
            if (kierunek * (studenci[j].srednia - studenci[imax].srednia) > 0) {
                imax = j;
            }
        }
        tmp = studenci[i];
        studenci[i] = studenci[imax];
        studenci[imax] = tmp;
    }

    return counter;
}
```

4. Przejdziemy do pełnej dynamicznej alokacji pamięci. teraz nasza struktura będzie dynamiczna. Wygodnie będzie podzielić nasz program na funkcje tworzące nowe wektory i dodające nowych studentów do tablicy studentów.


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

Scenariusz:
* najpierw napiszemy będziemy `mallocować` wszędzie w funkcji wczytującej.
* Potem napiszemy funkcję, która będzie tworzyć studenta na podstawie przekazanych danych.
* Potem napiszemy funkcję, która będzie zwalniać pamięć :-) `free`.

5. Sprawdźmy ile zajmuje pamięci nasz program po i przed poprawkami. Do sprawdzania pamięci uzyjemy narzędzia jakim jest `valgrind`.

Będziemy dalej pracować na danych przykładowych.

```
6
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
Ewa Chotomska 234569
2
Matematyka dyskretna;5.0;4;Prof.Sasin
Podstawy informatyki;4.0;2;Prof.Starzyński
Tomek Sawyer 234571
3
Matematyka dyskretna;5.0;6;Prof.Sasin
Podstawy informatyki;4.5;2;Prof.Starzyński
Algebra;4.0;1;Prof.Multarzyński
Iza Góralska 234572
3
Matematyka dyskretna;4.0;6;Prof.Sasin
Podstawy informatyki;4.5;2;Prof.Starzyński
Algebra;4.0;1;Prof.Multarzyński
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
