1. Zaczęliśmy nasze zajęcia od standardowego 'boilerplatea' czyli plików nagłówkowych i funkcji main. Zadeklarowaliśmy struktrę student:

```c
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
```

Przyjrzyjmy się strukturze: imie, nazwisko i nr_albumu to napisy, które mogą mieć maksymalnie po 49 znaków (pamiętamy o `\0` na końcu :-)). Potem srednia - liczba zmienno przecinkowa, liczba_ocen - liczba całkowita wskazująca ile mamy wczytanych ocen z przedmiotó w kolejnych tablicach struktury. I, tak: tablica z miejscem na maksymalnie 20 ocen, 20 pól dotyczących punktów ects oraz po dwadzieścia napisów przedmioty oraz kto_wystwaił daną oceną. Każdy napis `przedmiot` i `kto_wystawil` moze analogicznie zawierać maksymalnie 49 znaków. 

2. Potem ustaliliśmy następujący scenariusz programu:
 
 * wczytujemy informacje o studentach i ich ocenach z pliku tekstowego,
 * wypisujemy na ekranie w czytelny dla użytkownika sposób zawartość naszej 'bazy danych studentów'.
 
3, Zaczęliśmy pisać funkcję `main()`, która zakłada, że jako pierwszy argument podczas uruchamiania skompilowanego programu użytkownik będzie podawać nazwę pliku. Otworzymy plik o wskazanej nazwie (`fopen`) oraz zapamiętamy uchwyt do niego w strukturze `FILE`, do któej będziemy przechowywać wskaźnik `FILE *fin`. Następnie wywołamy funkcję wczytującą, której przekażemy wskaźnik do tablicy struktur do której powinna onna wczytać informacje o studentach. Przypomnieliśmy przy tym jak odwołujemy się do tablic, za pomocą równoważnego zapisu. Dla przypomnienia: użycie samej nazwy tablicy `studenci` jest równoważne wskaźnikowi do jej pierwszego elementu: `&studenci[0]`.

```c
    /* n = wczytaj(argv[1], studenci); */
    n = wczytaj(argv[1], &studenci[0]);
```

4. Potem poświęciliśmy dużo czasu na napisanie długiej funkcji, której zadaniem było zinterpretowanie pliku tekstowego w odpowiedni sposób. W trakcie pisania co chwilę wyświetlaliśmy poszczególne wartości z pliku: najpierw w postaci orygialnego napisu, a potem już ze zmiennych w których przechowywane są wartości zinterpretowane. Najlepiej ilustruje to przykład:

```c
    w = fgets(bufor, 254, fin);
    printf("Wczytałem z pliku napis: %s\n", bufor);
    
    n = atoi(bufor);
    printf("Wczytałem z pliku liczbę: %d\n", n);
```

W pierwszych dwóch linijkach wczytujemy linijkę z pliku za pomocą funkcji `fgets`, któa wczyta całą linijkę do tablicy znaków wskazywanej przez wskaźnik!: `bufor`. Liczba `254` oznacza maksymalną długość jaką `fgets` może wczytać do bufora. Potem wyświetlamy na ekranie oryginalny napis (Można zwrócić uwagę, że napis ten zawiera również końcowy znak nowej linii.) Następnie konwertujemy napis w tej linijce na liczbę całkowitą typu `int` za pomocą funkcji `atoi`. W ostatniej linijce wyświetlamy wartość typu `%d` czyli liczbę całkowitą zinterpretowaną. Wyświetlając na ekranie sprawdzamy, czy nasz program poprawnie zinterpretował liczbę. 

Proszę zwrócić uwagę, że naszą funkcję wczytującą pisaliśmy przyrostowo, po kawałku, komiplując, uruchamiajać, edytując, kompilując, uruchamiając, itd. Dzięki temu było nam łatwiej wychwytywać ewentualne problemy i błędy w trakcie pisania. 

5. Przyjrzyjmy się dwum metodom interpretującym dane w poszczególnych linijkach:

a) metoda z uzyciem funkcji `sscanf()`, która potrafi 'wyłuskać' z napisu określone w napisie definiującym format (tzw. ang. 'format string') typy zmiennych:

```c
sscanf(bufor, "%s %s %s", studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_albumu);
```
W powyższej linijce funkcja `sscanf`, z napisu prechowywanego w zmiennej `bufor` wyciągnie trzy wyrazy (`%s %s %s`) i zapisze je do tablic znakowych imie, naziwsko i nr_albumu 'i-tej' struktury tablicy `studenci`.

Zwróciliśmy ponownie uwagę, że powyższy zapis jest równoważny zapisowi:

```c
sscanf(bufor, "%s %s %s", &studenci[i].imie[0], studenci[i].nazwisko, studenci[i].nr_albumu);
```
w którym jawnie podajemy, że chcemy zapisać wyniki w miejsca wskazywane przez adresy (`&`) pierwszych elementów `...[0]` tablic `imie`, `nawisko` i `nr_albumu`.

b) Drugi sposob interpretacji danych w poszczególnych linijkach opierał się na wykorzystaniu funkcji `strtok`. `Strtok` potrafi podzielić napis na kolumny względem podanego jako argument rozdzielnika. Używając jej musimy być bardzo ostrożni, ponieważ niszczy ona oryginalny napis wstawiając znak `\0` w miejscu wystąpienia znaku rozdzielającego. Za pierwszym razem gdy wywołamy funkcję `strtok` i podamy wskaxnik do początku napisu wstawi ona `\0` w miejsce pirwszego wystąpienia rozdzielnika i zwróci jako swój wynik wskaźnik do początku napisu - czyli teraz to już będzie nie oryginalny napis ale pierwsza kolumna, bo 'nowy - ten sam' napis będzie się kończył w miejscu starego rozdzielnika. Za drugim, i kolejnymi razami wywołamy naszą funkcję podając jako pierwszy argument wartość `NULL`, któa informuje `strtok` aby kontynuował szukanie rozdzielników w dalszej części ostatnio przekazanego napisu. Gdy `strtok` nie znajdzie kolejnej kolumny to zwraca wartość NULL zamiast wskaźnika. 

Przykład:
Załóżmy napis:  
`char napis = "Ala ma; kota ;a kot ma Ale;";`
Po pierwszym wywołaniu `strtok(napis,";");`, zawartość napisu będzie równa:  
`char napis = "Ala ma\0 kota ;a kot ma Ale;";`
a `strtok` zwróci: `&napis[0]`
Po drugim wywołaniu `strtok(NULL,";");`, zawartość napisu będzie równa:  
`char napis = "Ala ma\0 kota \0a kot ma Ale;";`
a `strtok` zwróci: `&napis[7]`
Po trzecim wywołaniu `strtok(NULL,";");`, zawartość napisu będzie równa:  
`char napis = "Ala ma\0 kota \0a kot ma Ale\0";`
a `strtok` zwróci: `&napis[14]`
Po czwartym wywołaniu `strtok(NULL,";");`, zawartość napisu będzie nadal równa:  
`char napis = "Ala ma\0 kota \0a kot ma Ale\0";`
a `strtok` zwróci: `NULL`

6. Kolejną rzeczą o któej musiliśmy pamiętać używając `strtok` byla konieczność skopiowania napisu z bufora do pól struktury (przedmioty i kto_wystawil). Użyliśmy do tego funkcji `strcpy`.

```c
    strcpy(studenci[i].przedmioty[o], w);
```
gdzie `w` to wskaźnik do kolejnej kolumny zwrócony przez `strtok`.

7. Po napisaniu program wczytujący wyglądał następująco.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("Wczytałem z pliku napis: %s\n", bufor);
    
    n = atoi(bufor);
    printf("Wczytałem z pliku liczbę: %d\n", n);

    for (i = 0; i < n; i++) {
        fgets(bufor, 254, fin);
        printf("Wczytałem z pliku dane studenta: %s\n", bufor);
 
        /* sscanf(bufor, "%s %s %s", &studenci[i].imie[0], studenci[i].nazwisko, studenci[i].nr_albumu); */
        sscanf(bufor, "%s %s %s", studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_albumu);

        printf("Dane studenta w strukturze[%d]: imie: %s, nazwisko: %s, nr_albumu: %s\n", 
                    i, studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_albumu);
 
        fgets(bufor, 254, fin);
        studenci[i].liczba_ocen = atoi(bufor);   

        for (o = 0; o < studenci[i].liczba_ocen; o++) {
            fgets(bufor, 254, fin);
            printf("Wczytałem z pliku oceny[%d]: %s\n", o, bufor);
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

int main(int argc, char *argv[]) {
    int n;
    struct Student studenci[20];

    /* n = wczytaj(argv[1], studenci); */
    n = wczytaj(argv[1], &studenci[0]);
    wypisz_na_ekran(studenci, n);

    printf("Rozmiar tablicy to %ld\n", sizeof(struct Student));

    return 0;
}

```

8. W dalszej części zajęć rozmawialiśmy o **dyrektywach preprocesora**:
```c
#define DOWOLNANAZWA dowolna wartosc
```
które służą do sterowania procesem kompilacji.

Użyliśmy również 

```c
#ifdef DEBUG
cos tam
#endif
```
które oznacza, że fragment kodu wewnątrz bloku `ifdef` będzie uwzględniony w procesie kompilacji tylko wtedy jeżeli będzie zdefiniowana stała `DEBUG`.

9. Na koniec napisaliśmy funkcję wypisującą na ekranie.

10. Cały program z pierwszej części wyglądał tak:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define DEBUG */

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
```

11. Dalej postanowiliśmy stworzyć strukturę zagnieżdżoną wprwadzjąc prostą **refaktoryzację** kodu. Refaktoryzacja to proces modyfikacji kodu, który zmienia jego wewnętrzne działanie, ale nie zmienia jego funkcjonalności z punktu widzenia użytkownika. Na zewnątrz nie widać ządnej różnicy - program działa tak samo. Wewnętrznie wykorzystuje tylko inne struktury danych i funkcje. (UWAGA! Musicie wiedzieć co oznacza refaktoryzacja i musicie umieć podać jakiś prosty przykład, ponieważ na zaliczeniu mogą pojawić się o to pytania!)

12. Na sam koniec naszego spotkania, w szalonym tempie podzieliśmy nasz plik `main.c` na trzy mniejsze pliki:

```
main.c
bibl.c
bibl.h
```

W ten sposob w osobnyh plikach znalazły się osobne funkcjonalności naszej aplikacji - zaczęliśmy pisać proste moduły :-). Proces kompilacji programu skłądającego się z dwóch plikó wymagał od nas podania obydwu plików źródłowych tak:

```bash
cc main.c bibl.c -o main
```

c.d.n.

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

int posortuj_malejaco(FILE *fin, struct Student tab[50], int n) {
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
