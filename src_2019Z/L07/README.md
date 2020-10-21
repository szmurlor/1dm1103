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

Zadanie zostało wgrane na githuba do pliku zadanie_zaszyfrowane.txt. Opis zadania został zaszyfrowany banalnym szyfrem Cezara (https://pl.wikipedia.org/wiki/Szyfr_Cezara) z przesunięciem o JEDEN do przodu. Uwaga, szyfr został zrobiony w ten sposób, że przesuwane o jeden w tablicy ASCII są tylko znaki z alfabetu angielskiego czyli 'a',...,'z' oraz 'A',...,'Z' z pominięciem polskich znaków, które pozostały w 'zaszyfrowanym' pliku bez zmian. Innymi słowy jawne 'a' staje się w zaszyfrowanym pliku 'b', 'A' staje się 'B', a litera 'z' i 'Z' stają się odpowiednio 'a' i 'A' (następuje rotacja). Aby poznać treść zadania należy najpierw napisać sobie programik do odszyfrowywania. Proszę nie udostępniać jawnej tresci zadania innym osobom z grupy! Potraktujmy to jako dobrą zabawę (mam nadzieję :-)).

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

