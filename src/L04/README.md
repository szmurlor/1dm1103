## Napisy (`char *napis`, `char napis[]`, `char *napis[]`)

Zaczęliśmy od próby uporządkowania trochę dotychczasowej wiedzy o Języku C w kontekście napisów.

1. Napis w języku C to tablica znaków. Każdy tablica znaków przechowująca napis w języku C kończy się wartością `0`.  Pamiętamy, że wszystkie wartości są zapamiętywane w komputerze w pamięci. standardowo, w języku C jeden znak zajmuje jeden bajt pamięci. Tablica znaków to fragment pamięci operacyjnej, w której kolejne bajty reprezentują kolejne znaki. Sama tablica znaków może w pamięci operacyjnej zajmować więcej miejsca, a napis może być krótszy. Po to właśnie jest ten znacznik `0` (zasadniczo w języku C powinniśmy używać słowa kluczowego `null`, które reprezentuje właśnie to zero).

   Oto przykładowy program w języku C inicjujący napis, znak po znaku:

   ```c
   #include <stdio.h>
   
   int main(int argc, char *argv[]) {
   	char napis[10];
   	napis[0] = 'A';
   	napis[1] = 'l';
   	napis[2] = 'a';
   	napis[3] = 0;
   	
   	printf("Wartość zmiennej napis = %s\n", napis);
   	
   	return 0;
   }
   ```

   Zwróćmy uwagę na deklarację tablicy znaków `char napis[10];`. Należy zaznaczyć, że to jest tablica znaków i nie jest jeszcze napisem. Napisem stanie się dopiero, gdy wpiszemy na którym miejscu `0`. Ta tablica ma zarezerwowane w pamięci 10 bajtów na 10 znaków. Zaraz! A gdzie będzie zero? Niestety, aby poprawni przechować napis w tablicy o rozmiarze 10 bajtów, sam napis może zawierać co najwyżej `9` znaków! Na dziesiątej pozycji tablicy znajdzie się wartość `0`.
   W kolejnych linijkach programu inicjujemy znak po znaku kolejne elementy tablicy. Proszę zwrócić uwagę, że używamy pojedynczego *apostrofa* do oznaczenia znaku! Wewnątrz pojedynczego apostrofu może być tylko jeden znak ponieważ jest to zmienna typu `char`. Na końcu inicjalizacji wstawiamy wartość `0`. Tuż przed `return` używamy funkcji `printf` do wyświetlenia napisu.

2. Uwaga! Posługiwanie się tablicami w języku C! Do pojedynczych elementów tablicy w języku C odwołujemy się używając nawiasu kwadratowego `[]`. Do całej tablicy jako tablicy odwólujemy się używając samej zmiennej i pomijając nawiasy kwadratowe. Przykład:

   ```c
   printf("Drugi znak napisu napis jest równy: %c\n", napis[1]);
   printf("Napis jest równy: %s\n", napis);
   ```

   `%c` w pierwszej linijce informuje funkcję `printf`, że pierwszą zmienną którą ma wyświetlić ma zinterpretować jako jeden znak. Dlatego używamy składni `napis[1]`. W drugiej linijce chcemy wyświetlić cały napis jako napis. Dlatego do funkcji `printf` przekazujemy `%s`, które oznacza, że zmienna ma być potraktowana jako tablica znaków zawierająca napis. (Uwaga, na kolejnych wykładach dowiemy się na ten więcej, gdy wprowadzimy pojęcie wartości zmiennej, wskaźnika do zmiennej, wskaźnika do tablicy, itp.)

3. W kolejnym etapie napisaliśmy prosty program, w którym zaczęliśmy *bawić się* napisami:

   ```c
   /* To jest komentarz. W języku C komentarze zaczynają się 'sleszem' i gwiazdką,
   a kończą gwiazdką i 'sleszem' zapisanymi w odwrotnej kolejności. */
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   
   int main(int argc, char *argv[]) {
       /* Poniżej mamy dwie linijki, które robią dokładnie to samo. Róznica jest
          w wyglądzie. Z punktu widzenia języka efekt będzie w 100% identyczny.
          Dlaczego? Odpowiemy sobie na to pytanie gdy wprowadzimy pojęcie wskaźników.
          */
       
   	/* char * napis = "Ala ma kota"; */
   	char napis[] = "Ala ma kota";
   	int i;
   
       /* Deklarujemy pętlę, która 'przeiteruje' po wszystkich elementach tablicy
          napis. */
   	for (i=0; i<strlen(napis);i++)
           
           /*Poniżej mamy różne wariacje na temat tego jak funkcja printf interpretuje
             format oraz dopasowuje do niego zmienną. Czasami wystąpią błędy,
             jak `Segmentation fault!` `Core dumped` wynikające z tego,
             będziemy do funkcji printf przekazywać zmiennego innego typu niż
             wyspecyfikowaliśmy wewnątrz tzw 'format stringu' :-)  */
           
   		/* printf("[%d] = %d\n", i, napis[i]); */
   		printf("[%d] = %c\n", i, napis[i]);
   /*
   	printf("Napis: %s\n", napis);
   	printf("Napis: %s\n", napis[0]);
   	printf("Napis: %c\n", napis[0]);
   	printf("Napis: %s\n", argv);
   	printf("Napis: %s\n", argv[0]);
   */
   
   /* Ten kod służy dp wyświetlania pierwszych 128 znaków tablicy ASCII.
      Tablica ASCII przyporządkowuje liczbom całkowitym w zakresie 0-255
      specjalne znaczenie w kontekście napisów. Sprawdźcie sami, od której liczby
      cąlkowitej zaczyna się alfabet.
      
   	for (i=0;i<128;i++) {
   		printf("[%d] = %c\n", i, i);
   	}
   */
   	return 0;
   }
   ```

   A co to jest `string.h` oraz `strlen`? Pierwszy to plik nagłówkowy dołączający bibliotekę umożliwiającą używanie funkcji operujących na napisach (czyli jeszcze raz powtórzmy tablicach znaków zakończonych zerami). Druga to funkcja obliczająca długość napisu. Funkcja działa w ten sposób, że zwraca liczbę kolejnych znaków od początku tablicy, które nie są zerem.

   Uwaga! Tu jest praca domowa! Proszę samodzielnie napisać funkcję, która oblicza długość napisu - czyli zwraca liczbę całkowitą (`int`) reprezentującą długość napisu! Działanie funkcji powinno być analogiczne do funkcji `strlen`. Proszę aby funkcja nazywała się `dlugosc_napisu` i jako argument pobierała *wskaźnik* do tablicy znaków zawierającej napis - czyli `char s[]`. Rozwiązanie w postaci programu zawierającego napisaną funkcję do obliczania długości oraz funkcję `main`, która będzie demonstrowała jej działanie proszę wgrać do ISODa.

4. Prześledźmy teraz warianty `printf` w *odchudzonej wersji* programu na czysto:

   ```c
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   
   int main(int argc, char *argv[]) {
   	char napis[] = "Ala ma kota";
   	int i;
   
   	for (i=0; i<strlen(napis);i++)
   		printf("[%d] = %c\n", i, napis[i]);
       
   	return 0;
   }
   ```

   `printf("[%d] = %d\n", i, napis[i]); ` - wariant w którym wartość na i-tej pozycji tablicy interpretujemy jako zwykłą liczbę (`%d`), - czyli zamiast znaków na ekranie wyświetlą się liczby z tablicy ASCII reprezentujące znaki `A`, `l`,`a`.

   `printf("[%d] = %c\n", i, napis[i]);` - wariant w którym w kolejnych linijka wypiszemy na ekranie pojedyncze znaki (`%c`).

   `printf("Napis: %s\n", napis);` - wypisujemy cały napis, czyli interpretując dosłownie - funkcja `printf` wyświetli kolejno zaczynając od początku tablicy wszystkie znaki dopóki nie napotka wartości `0`.
   `printf("Napis: %s\n", napis[0]);` - to zdziała, źle i w sposób nieprzewidywalny, ponieważ do funkcji `printf` zamiast napisu (czyli adresu początku tablicy - wrócimy do tego jeszcze przy okazji wskaźników :-) przekazujemy adres będący wartością ASCII pierwszego znaku tablicy `A`. Bardzo źle - prosimy funkcję `printf` aby wyświetliła napis, który ma sobie odczytać z początku pamięci operacyjnej komputera, która jest zarezerwowana do bardzo krytycznych dla działania komputera zadań. Wartości w tamtym obszarze pamięci na pewno nie są napisami!

   `printf("Napis: %c\n", napis[0]);` - lepiej. teraz wszystko działa jak należy, w sensie wypisujemy na ekranie pierwszy znak napisu. (Pamiętamy, że w języku C pierwszy element tablicy ma indeks równy `0`.)
   `printf("Napis: %s\n", argv);` - brrrrr, znowu źle! Niestety `argv` nie jest napisem, ale tablicą napisów! Znowu nasz program zachowa się w sposób nieprzewidywalny!
   `printf("Napis: %s\n", argv[0]);` - teraz dobrze. Wypiszemy na ekranie pierwszy napis z tablicy `argv`.

   Uwaga! Uzupełnienie pracy domowej :-) A teraz? Co należałoby napisać, aby wyświetlić na ekranie drugi znak drugiego napisu tablicy `argv`? Proszę uzupełnić program, z wcześniejszego zadania i tuż przed instrukcją `return 0;` proszę napisać jedną linijkę kodu wypisująca na ekranie drugi znak drugiego napisu tablicy `argv`. :-)

5. Ufff... odpocznijmy od napisów.

## Obsługa plików

Wracamy do tablic, a tak naprawdę, skupimy się na obsłudze plików w języku C. Postawmy dobie zadanie.

> Zadanie: wczytaj dwa wektory z plików, dodaj je do siebie w algebrze wektorowej i zapisz wynik do trzeciego pliku. Program powinien otrzymywać trzy argumenty: 1 - nazwę pliku z pierwszym wektorem, 2 - nazwę pliku z drugim wektorem, 3 - nazwę pliku do, którego powinien zostać zapisany wektor wynikowy.

Zacznijmy od napisania scenariusza działania programu - algorytmu głównego.

1. Program wczytuje pierwszy wektor z pliku do tablicy `v1`.

2. Program wczytuje drugi wektor z pliku do tablicy `v2`.

3. Program dodaje do siebie odpowiednie elementy wektorów `v1` i `v2` a wynik zapisuje do odpowiednich elementów wektora `v3`, zgodnie z wzorem:
   $$v_3 = [v_{1,0}+v_{2,0}, v_{1,1}+v_{2,1}, \ldots, v_{1,n}+v_{2,n}]$$,

   lub w innym zapisie:
   $$v_{3,i} = v_{1,i}+v_{2,i}$$ dla $$i \in 0,1,\ldots, n$$.

4. Program zapisuje wartości wektora `v3` do pliku wynikowego.

Zacznijmy od szkieletu programu. Na początku  standardowo pliki nagłówkowe. Potem deklarujemy sobie tzw. makrodyrektywę, czyli wartość  `100`, która przez *preprocesor* zostanie wstawiona wszędzie gdzie zostanie napotkany ciąg znaków `MAX`. *Preprocesor* przypominam to jest etap przed kompilacją programu, który polega na wykonaniu tekstowych modyfikacji oryginalnego programu. To jest tak jak tłumaczenie z języka polskiego na angielski itp. Tekstowe operacje modyfikacji zakończą się odrobinę inną wersją tekstową programu. W naszym przypadku. Wszędzie gdzie byłoby `MAX` zostanie wstawiony napis `100`. Po co to robimy? Po pierwsze aby poprawić czytelność programu - `MAX` jest bardziej znaczące niż sama liczba `100` (to się okaże później :-), po drugie w jednym miejscu będziemy mieli zdefiniowaną wartość `100`, a potem tylko symbolicznie będziemy się do niej odwoływać. 

```c
#include <stdio.h>
#include <stdlib.h>

/* Magic numbers :-) */
#define MAX 100

int main(int argc, char *argv[]) { 
    n1 = wczytaj(v1, argv[1]);
    n2 = wczytaj(v2, argv[2]);
    n3 = suma(v1,v2,v3, n1);
    zapisz(v3,n3, argv[3]);
    return 0;
}
```

Funkcja `main` nie jest jeszcze skończona. Zawiera scenariusz, ale nie ma jeszcze zadeklarowanych zmiennych dotyczących tablic, do których będziemy wczytywać wartości wektorów. Uzupełnijmy te deklaracje dodając sześć zmiennych: trzy tablice liczb zmiennoprzecinkowych `float v1[]; float v2[]; float v[3];` oraz trzy zmienne reprezentujące liczby całkowite przechowujące trzy długości wektorów: `int n1; int n2; int n3;`, co możemy zapisać skrótowo:

```c
#include <stdio.h>
#include <stdlib.h>

/* Magic numbers :-) */
#define MAX 100

int main(int argc, char *argv[]) { 
    float v1[], v2[], v3[];
    int n1,n2,n3;
    n1 = wczytaj(v1, argv[1]);
    n2 = wczytaj(v2, argv[2]);
    n3 = suma(v1,v2,v3, n1);
    zapisz(v3,n3, argv[3]);
    return 0;
}
```

Dodajmy teraz do naszego programu kolejno funkcje ze scenariusza. Zacznijmy od wczytywania. Zwróćmy uwagę, że oczekujemy aby funkcja wczytująca zwracała liczbę elementów wczytanego wektora. Zatem:

```c
int wczytaj(float v[], char nazwa_pliku[]) {
    FILE * fin = fopen(nazwa_pliku, "r");
    int n;
    int i;
    float wartosc;
    fscanf(fin, "%d", &n);
    
    for (i=0; i< n;i++) {
        fscanf(fin, "%f", &wartosc);
        v[i] = wartosc;
    }
    
    fclose(fin);
    return n;
}
```

W kolejnych linijkach:

1. Otwieramy plik o nazwie podanej jako drugi argument funkcji i zapisujemy uchwyt do tego pliku w zmiennej `FILE * fin`. Uchwyt do pliku pozwoli nam wczytywać z tego pliku. Proszę zwrócić uwagę na argument `"r"` który instruuje funkcję `fopen` aby otworzyła plik do czytania (ang. *read*).
2. Następnie deklarujemy zmienne pomocnicze, wśród których jest liczba `n`, która będzie zawierać długość wektora.
3. Proszę zwrócić uwagę na funkcje `fscanf`, które wczytują wartości z pliku o zadanym typie (formacie). Za pierwszym razem wczytujemy liczbę całkowitą (`"%d"` - ang. *decimal*) i zapisujemy wynik do zmiennej `&n`. Znak *ampersand* (ósemki z ogonkiem) jest konieczny aby przekazać do funkcji `fscanf` lokalizację naszej zmiennej `n`. Wrócimy do tego zagadnienia dokładnie na kolejnym wykładzie gdy będziemy rozmawiać o wskaźnikach. Na dzień dzisiejszy zapamiętajmy, że zmienne widoczne są tylko w obrębie lokalnych bloków i inne bloki (np. funkcje) nie mogą modyfikować tych wartości. Dlatego musimy w specjalny sposób przekazać lokalizację naszej lokalnej zmiennej do funkcji `fscanf`. Robimy to właśnie poprzedzając jej nazwę znakiem `&`. Następnym razem gdy będziemy używać funkcji `fscanf` użyjemy formatu `"%f"`, który instruuje funkcję `fscanf`, że ma wczytać z pliku  kolejną liczbę zmienno-przecinkową.
4. Operację wczytywania kolejnych elementów wektora wykonujemy w pętli `n` razy.
5. Na koniec zamykamy plik zwalniając uchwyt do pliku `fclose(fin);` oraz jako wynik naszej funkcji wczytującej zwracamy liczbę wczytanych elementów.

Kolejną funkcją, którą napiszemy jest funkcja sumująca.

```c
int suma(float v1[], float v2[], float vs[], int n) {
    int i;
    for (i = 0; i <n; i++) {
        vs[i] = v1[i] + v2[i];
    }
    return n;
}
```

Funkcja otrzymuje cztery argumenty - trzy referencje do tablic przechowujące elementy wektorów oraz ich długość. Funkcja sumująca jest zdefiniowana matematycznie wyłącznie jeżeli długości wszystkich wektorów jest jednakowa. Dlatego przekazujemy tą długość za pomocą jednej zmiennej `int n` :-)

Tylko dla wygody zwracamy długość `n` jako wynik.

Zapiszmy teraz wektor do pliku. Napiszemy funkcję zapisującą

```c

void zapisz(float v[], int n, char nazwa_pliku[]) {
    FILE * fout = fopen(nazwa_pliku, "w");
    fprintf(fout, "%d\n", n);
    int i;
    for (i = 0; i < n; i++) {
        fprintf(fout, "%f\n", v[i]);
    }
    fclose(fout);
}
```

Funkcja otrzymuje trzy argumenty: wektor, długość i nazwę pliku do którego ma zostać zapisany. Po kolei:

1. Otwieramy plik o wskazanej nazwie do zapisu `"w"` (ang. *write*) i zapamiętujemy uchwyt do tego pliku w zmiennej `fout`. Plik zostanie automatycznie utworzony gdy nie istniał.
2. Zapisujemy w pierwszej linijce pliku liczbę elementów. Zwróć uwagę na `f` przed `printf`, czyli `fprintf`. Ta funkcja zakłada, że pierwszym argumentem jest uchwyt do pliku do którego należy zapisać sformatowaną wartość - wnaszym przypadku liczbę całkowitą `"%d\n"`.
3. Potem wykonujemy `n` razy blok kodu zapisują w poszczególnych linijkach pliku wartość wektora `v[]` przekazanego jako parametr funkcji.
4. Na koniec zamykamy plik zwalniając jego uchwyt: `fclose(fout)`.

Aby sprawdzić działanie naszego programu dodaliśmy również banalną funkcję wypisującą wektor na ekranie.

```c
void wypisz(int n, float v[]) {
    int i;
    for (i = 0; i < n; i++) {
        printf("v[%d] = %f\n", i, v[i]);
    }
}
```

Cały program wygląda następująco:

```c
#include <stdio.h>
#include <stdlib.h>

/* Magic numbers :-) */
#define MAX 100

int wczytaj(float v[], char nazwa_pliku[]) {
    FILE * fin = fopen(nazwa_pliku, "r");
    int n;
    int i;
    float wartosc;
    fscanf(fin, "%d", &n);

    for (i=0; i< n;i++) {
        fscanf(fin, "%f", &wartosc);
        v[i] = wartosc;
    }
    
    fclose(fin);
}


void wypisz(int n, float v[]) {
    int i;
    for (i = 0; i < n; i++) {
        printf("v[%d] = %f\n", i, v[i]);
    }
}

int suma(float v1[], float v2[], float vs[], int n) {
    int i;
    for (i = 0; i <n; i++) {
        vs[i] = v1[i] + v2[i];
    }

    return n;
}

void zapisz(float v[], int n, char nazwa_pliku[]) {
    FILE * fout = fopen(nazwa_pliku, "w");
    fprintf(fout, "%d\n", n);
    int i;
    for (i = 0; i < n; i++) {
        fprintf(fout, "%f\n", v[i]);
    }
    fclose(fout);
}

int main(int argc, char *argv[]) {
    /* float v1[100]; */
    float v1[MAX];
    int n1;
    float v2[MAX];
    int n2;
    float v3[MAX];
    int n3;

    n1 = wczytaj(v1, argv[1]);
    n2 = wczytaj(v2, argv[2]);
    n3 = suma(v1,v2,v3,n1);

    zapisz(v3,n3, argv[3]);

    wypisz(n1, v1);
    wypisz(n2, v2);
    wypisz(n3, v3);

    return 0;
}
```



## Struktury

Trochę przeszkadzało nam to, że do każdej funkcji musieliśmy za każdym razem przekazywać wektor oraz jego długość. O ile wygodniej byłoby, gdybyśmy mieli możliwość przekazywania jednej zmiennej, która sama w sobie zawierałaby informację o długości oraz wartościach poszczególnych elementów wektora. W tym celu utworzyliśmy własny, złożony typ danych - **strukturę**.

```c
struct Wektor {
    int n;
    float v[MAX];
};
```

Wtedy nasza funkcja `main` może wyglądać tak:

```c
int main(int argc, char *argv[]) {
    struct Wektor v1;
    struct Wektor v2;
    struct Wektor v3;

    wczytaj(&v1, argv[1]);
    wczytaj(&v2, argv[2]);

    ...

    return 0;
}
```

Trochę przeszkadzało nam to słowo `struct` przy każdej deklaracji zmiennej, dlatego zmodyfikowaliśmy odrobinę definicję naszej struktury używając słowa kluczowego `typedef`, dodając *podkreślenie* do nazwy głównej struktury oraz nazwyając nasz nowy typ danych po prostu `Wektor`.

```c
typedef struct _Wektor {
    int n;
    float v[MAX];
} Wektor;
```

Należy zaznaczyć, że zrobiliśmy to wyłącznie w celach estetycznych :-). Dzięki temu zabiegowi nasza funkcja `main` może wyglądać następująco:

```c
int main(int argc, char *argv[]) {
    Wektor v1, v2, v3;

    wczytaj(&v1, argv[1]);
    wczytaj(&v2, argv[2]);
    suma(v1,v2,&v3);
    zapisz(v3, argv[3]);

    wypisz(v1);
    wypisz(v2);
    wypisz(v3);

    return 0;
}
```

Większość wydaje się oczywiste, ale dlaczego znowu te znaki `&`? Odpowiedź: ponieważ wewnątrz funkcji `wczytaj` oraz `suma` będziemy chcieli zmodyfikować wartości zmiennych, które są zdefiniowane w naszym lokalnym bloku kodu. Tylko dzięki `&` będziemy mieli taką możliwość. Co więcej, funkcja `wczytaj` nie musi już zwracać długości. Będzie ją zapamiętywać w strukturze.

Okay. Wczytujemy wektor do struktury do której referencję otrzymamy jako argument.

```c
void wczytaj(Wektor *w, char nazwa_pliku[]) {
    FILE * fin = fopen(nazwa_pliku, "r");
    int dlugosc;
    int i;
    float wartosc;
    fscanf(fin, "%d", &dlugosc);
    w->n = dlugosc;

    for (i=0; i< dlugosc;i++) {
        fscanf(fin, "%f", &wartosc);
        w->v[i] = wartosc;
    }
    fclose(fin);
}

```

Uwaga! Ponieważ, chcemy modyfikować wartości struktury `Wektor` to jako argument otrzymamy referencję (*sic! wskaźnik*) do wektora czyli `Wektor *w` <- kluczowa jest gwiazdka przed nazwą zmiennej `w`. Przez to, że przekazujemy wektor jako referencję (wskaźnik) to do elementów struktury będziemy się odwoływać za pomocą znaków `->`. Czyli:

```c
w->n = dlugosc;
```

znaczy, że w miejsce atrybutu struktury `n` zostanie wpisana wartość naszej zmiennej lokalnej `dlugosc`. Wewnątrz pętli `for` wczytujemy zapamiętujemy kolejno wczytane wartości również odwołując się do atrybutu struktury:

```c
w->v[i] = wartosc;
```

Podobnie pozostałe funkcje otrzymują postać:

```c
void wypisz(Wektor w) {
    int i;
    for (i = 0; i < w.n; i++) {
        printf("v[%d] = %f\n", i, w.v[i]);
    }
}

void suma(Wektor v1, Wektor v2, Wektor *vs) {
    int i;
    for (i = 0; i <v1.n; i++) {
        vs->v[i] = v1.v[i] + v2.v[i];
    }
    vs->n = v1.n;
}

void zapisz(Wektor w, char nazwa_pliku[]) {
    FILE * fout = fopen(nazwa_pliku, "w");
    fprintf(fout, "%d\n", w.n);
    int i;
    for (i = 0; i < w.n; i++) {
        fprintf(fout, "%f\n", w.v[i]);
    }
    fclose(fout);
}

```

Na uwagę zasługuje fakt, że operatora referencji  `*` używamy tylko do zmiennych, których wartości chcemy modyfikować. Gdy wewnątrz funkcji będziemy wyłącznie odczytywać wartości struktury to używamy prostej deklaracji argumentu `Wektor v1`. Wtedy do atrybutów tej struktury w funkcji odwołujemy się zamiast strzałki `->` używając tylko kropki `.`. I tak w pętli `for`:

```c
for (i = 0; i <v1.n; i++) {
    vs->v[i] = v1.v[i] + v2.v[i];
}
```

do zmiennej przekazanej jako referencja (`Wektor *vs`) odwołujemy się używając `->` a do zmiennych `Wektor v1` i `Wektor v2` używając kropki `.`.

Cały program z użyciem struktur wygląda tak:

```c
#include <stdio.h>
#include <stdlib.h>

/* Magic numbers :-) */
#define MAX 100

typedef struct _Wektor {
    int n;
    float v[MAX];
} Wektor;

void wczytaj(Wektor *w, char nazwa_pliku[]) {
    FILE * fin = fopen(nazwa_pliku, "r");
    int liczba;
    int i;
    float wartosc;
    fscanf(fin, "%d", &liczba);
    w->n = liczba;

    for (i=0; i< liczba;i++) {
        fscanf(fin, "%f", &wartosc);
        w->v[i] = wartosc;
    }
    fclose(fin);
}


void wypisz(Wektor w) {
    int i;
    for (i = 0; i < w.n; i++) {
        printf("v[%d] = %f\n", i, w.v[i]);
    }
}

void suma(Wektor v1, Wektor v2, Wektor *vs) {
    int i;
    for (i = 0; i <v1.n; i++) {
        vs->v[i] = v1.v[i] + v2.v[i];
    }
    vs->n = v1.n;
}

void zapisz(Wektor w, char nazwa_pliku[]) {
    FILE * fout = fopen(nazwa_pliku, "w");
    fprintf(fout, "%d\n", w.n);
    int i;
    for (i = 0; i < w.n; i++) {
        fprintf(fout, "%f\n", w.v[i]);
    }
    fclose(fout);
}

int main(int argc, char *argv[]) {
    Wektor v1;
    Wektor v2;
    Wektor v3;

    wczytaj(&v1, argv[1]);
    wczytaj(&v2, argv[2]);

    suma(v1,v2,&v3);

    zapisz(v3, argv[3]);

    wypisz(v1);
    wypisz(v2);
    wypisz(v3);

    printf("To jest inna wersja tego samego programu.\n");

    return 0;
}
```

I to byłoby na tyle :-). 

Sugeruję, że wszyscy powinni w ramach samodzielnego ćwiczenia napisać program, który obliczy wartość iloczynu skalarnego dwóch wektorów podanych jako argumenty linii komend. Wynik iloczynu skalarnego powinien zostać wypisany na ekranie. Uwaga! Proszę spróbować napisać ten program całkowicie od zera! Nie używając fragmentów, ani nawet nie zaglądając do programów przykładowych! Proszę nie wgrywać tego programu do ISODa. On nie jest pracą domową :-)

Iloczyn skalarny wektorów zdefiniowany jest wzorem:

$$s = \sum\limits_{i=0}^{n} v_{1,i} \cdot v_{2,i}$$

co w języku C może zostać zapisane:

```c
s = 0;
for (i=0; i < n; i++) {
	s = s + v1[i]*v2[i]
}
```

Chciałbym aby dla następujących danych 

Plik1:

```bash
4
1
1.1
2.0
3
```

Plik2:

```bash
4
2
3
-1
1.0
```

program wypisał na ekranie:

```bash
Iloczyn skalarny: 6.3
```

