1. Zaczęliśmy nasze zajęcia od standardowego 'boilerplatea' czyli plików nagłówkowych i funkcji main. Zadeklarowaliśmy strukturę student:

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

Przyjrzyjmy się strukturze: imie, nazwisko i nr_albumu to napisy, które mogą mieć maksymalnie po 49 znaków (pamiętamy o `\0` na końcu :-)). Potem srednia - liczba zmiennoprzecinkowa, liczba_ocen - liczba całkowita wskazująca ile mamy wczytanych ocen z przedmiotów w kolejnych tablicach struktury. I, tak: tablica z miejscem na maksymalnie 20 ocen, 20 pól dotyczących punktów ects oraz po dwadzieścia napisów przedmioty oraz kto_wystawił daną oceną. Każdy napis `przedmiot` i `kto_wystawil` może analogicznie zawierać maksymalnie 49 znaków. 

2. Potem ustaliliśmy następujący scenariusz programu:

 * wczytujemy informacje o studentach i ich ocenach z pliku tekstowego,
 * wypisujemy na ekranie w czytelny dla użytkownika sposób zawartość naszej 'bazy danych studentów'.

3, Zaczęliśmy pisać funkcję `main()`, która zakłada, że jako pierwszy argument podczas uruchamiania skompilowanego programu użytkownik będzie podawać nazwę pliku. Otworzymy plik o wskazanej nazwie (`fopen`) oraz zapamiętamy uchwyt do niego w strukturze `FILE`, do której będziemy przechowywać wskaźnik `FILE *fin`. Następnie wywołamy funkcję wczytującą, której przekażemy wskaźnik do tablicy struktur do której powinna ona wczytać informacje o studentach. Przypomnieliśmy przy tym jak odwołujemy się do tablic, za pomocą równoważnego zapisu. Dla przypomnienia: użycie samej nazwy tablicy `studenci` jest równoważne wskaźnikowi do jej pierwszego elementu: `&studenci[0]`.

```c
    /* n = wczytaj(argv[1], studenci); */
    n = wczytaj(argv[1], &studenci[0]);
```

4. Potem poświęciliśmy dużo czasu na napisanie długiej funkcji, której zadaniem było zinterpretowanie pliku tekstowego w odpowiedni sposób. W trakcie pisania co chwilę wyświetlaliśmy poszczególne wartości z pliku: najpierw w postaci oryginalnego napisu, a potem już ze zmiennych w których przechowywane są wartości zinterpretowane. Najlepiej ilustruje to przykład:

```c
    w = fgets(bufor, 254, fin);
    printf("Wczytałem z pliku napis: %s\n", bufor);
    
    n = atoi(bufor);
    printf("Wczytałem z pliku liczbę: %d\n", n);
```

W pierwszych dwóch linijkach wczytujemy linijkę z pliku za pomocą funkcji `fgets`, która wczyta całą linijkę do tablicy znaków wskazywanej przez wskaźnik!: `bufor`. Liczba `254` oznacza maksymalną długość jaką `fgets` może wczytać do bufora. Potem wyświetlamy na ekranie oryginalny napis (Można zwrócić uwagę, że napis ten zawiera również końcowy znak nowej linii.) Następnie konwertujemy napis w tej linijce na liczbę całkowitą typu `int` za pomocą funkcji `atoi`. W ostatniej linijce wyświetlamy wartość typu `%d` czyli liczbę całkowitą zinterpretowaną. Wyświetlając na ekranie sprawdzamy, czy nasz program poprawnie zinterpretował liczbę. 

Proszę zwrócić uwagę, że naszą funkcję wczytującą pisaliśmy przyrostowo, po kawałku, kompilując, uruchamiając, edytując, kompilując, uruchamiając, itd. Dzięki temu było nam łatwiej wychwytywać ewentualne problemy i błędy w trakcie pisania. 

5. Przyjrzyjmy się dwóm metodom interpretującym dane w poszczególnych linijkach:

a) metoda z użyciem funkcji `sscanf()`, która potrafi 'wyłuskać' z napisu określone w napisie definiującym format (tzw. ang. 'format string') typy zmiennych:

```c
sscanf(bufor, "%s %s %s", studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_albumu);
```
W powyższej linijce funkcja `sscanf`, z napisu przechowywanego w zmiennej `bufor` wyciągnie trzy wyrazy (`%s %s %s`) i zapisze je do tablic znakowych `imie`, `naziwsko` i `nr_albumu` 'i-tej' struktury tablicy `studenci`.

Zwróciliśmy ponownie uwagę, że powyższy zapis jest równoważny zapisowi:

```c
sscanf(bufor, "%s %s %s", &studenci[i].imie[0], studenci[i].nazwisko, studenci[i].nr_albumu);
```
w którym jawnie podajemy, że chcemy zapisać wyniki w miejsca wskazywane przez adresy (`&`) pierwszych elementów `...[0]` tablic `imie`, `nawisko` i `nr_albumu`.

b) Drugi sposób interpretacji danych w poszczególnych linijkach opierał się na wykorzystaniu funkcji `strtok`. `Strtok` potrafi podzielić napis na kolumny względem podanego jako argument rozdzielnika. Używając jej musimy być bardzo ostrożni, ponieważ niszczy ona oryginalny napis wstawiając znak `\0` w miejscu wystąpienia znaku rozdzielającego. Za pierwszym razem gdy wywołamy funkcję `strtok` i podamy wskaźnik do początku napisu wstawi ona `\0` w miejsce pierwszego wystąpienia rozdzielnika i zwróci jako swój wynik wskaźnik do początku napisu - czyli teraz to już będzie nie oryginalny napis ale pierwsza kolumna, bo 'nowy - ten sam' napis będzie się kończył w miejscu starego rozdzielnika. Za drugim, i kolejnymi razami wywołamy naszą funkcję podając jako pierwszy argument wartość `NULL`, która informuje `strtok` aby kontynuował szukanie rozdzielników w dalszej części ostatnio przekazanego napisu. Gdy `strtok` nie znajdzie kolejnej kolumny to zwraca wartość NULL zamiast wskaźnika. 

Przykład:
Załóżmy napis:  
`char napis = "Ala ma; kota ;a kot ma Ale;";`  
Po pierwszym wywołaniu `strtok(napis,";");`, zawartość napisu będzie równa:  
`char napis = "Ala ma\0 kota ;a kot ma Ale;";`  
a `strtok` zwróci: `&napis[0]  `
Po drugim wywołaniu `strtok(NULL,";");`, zawartość napisu będzie równa:  
`char napis = "Ala ma\0 kota \0a kot ma Ale;";`  
a `strtok` zwróci: `&napis[7]`  
Po trzecim wywołaniu `strtok(NULL,";");`, zawartość napisu będzie równa:  
`char napis = "Ala ma\0 kota \0a kot ma Ale\0";`  
a `strtok` zwróci: `&napis[14]`  
Po czwartym wywołaniu `strtok(NULL,";");`, zawartość napisu będzie nadal równa:  
`char napis = "Ala ma\0 kota \0a kot ma Ale\0";`  
a `strtok` zwróci: `NULL`  

6. Kolejną rzeczą o której musieliśmy pamiętać używając `strtok` była konieczność skopiowania napisu z bufora do pól struktury (przedmioty i kto_wystawił). Użyliśmy do tego funkcji `strcpy`.

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
które służą do sterowania procesem kompilacji. Powyższa dyrektywa `#define` służy do deklarowania stałych. Dzięki zadeklarowaniu `DOWOLNANAZWA` w dowolnym fragmencie kodu programu zostanie **tekstowo** zastąpiona napisem `dowolna wartość`. Dopiero po wykonaniu wszystkich podmian nastąpi proces kompilacji programu.

Użyliśmy również warunkowego wyrażenia preprocesora.

```c
#ifdef DEBUG
cos tam
#endif
```
które oznacza, że fragment kodu wewnątrz bloku `ifdef` będzie uwzględniony w procesie kompilacji tylko wtedy jeżeli będzie zdefiniowana stała `DEBUG`. Dzięki temu mogliśmy globalnie, w jednym miejscu programu włączać i wyłączać komunikaty diagnostyczne - `printf`.

9. Na koniec napisaliśmy funkcję wypisującą zawartość naszej bazy danych o ocenach studentów na ekranie. Celem było czytelna prezentacja danych o studentach i ich ocenach.

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

11. Dalej postanowiliśmy stworzyć strukturę zagnieżdżoną przeprowadzając prostą **refaktoryzację** kodu. **Refaktoryzacja** to proces modyfikacji kodu, który zmienia jego wewnętrzne działanie, ale nie zmienia jego funkcjonalności z punktu widzenia użytkownika. Na zewnątrz nie widać żadnej różnicy - program działa tak samo. Wewnętrznie wykorzystuje tylko inne struktury danych i funkcje. (UWAGA! Musicie wiedzieć co oznacza refaktoryzacja i musicie umieć podać jakiś prosty przykład refaktoryzacji, ponieważ na zaliczeniu mogą pojawić się o to pytania!)
    

    Celem tej refakatoryzacji było zastąpienie czterech 20-sto elementowych tablic jedną tablicą złożoną ze struktur. W pierwotnej wersji programu na odpowiadających sobie pozycjach wszystkich czterech tablic znajdowały się dane odnoszące do tego samego przedmiotu i z niego oceny. Dużo efektywniej jest przechowywać takie powiązane dane właśnie w strukturach.

    

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

    Wprowadzenie rekatoryzacji wymagało od dokonania kilku zmian w pliku w kontekście odwoływania się do elementów struktury a nie elementów dwudziesto-elementowych tablic.

12. Na sam koniec naszego spotkania, w szalonym tempie podzieliśmy nasz plik `main.c` na trzy mniejsze pliki:

    ```c
    main.c	
    bibl.c
    bibl.h
    ```

    W pliku `main.c` zawarliśmy tylko funkcję main która odpowiada za główny scenariusz działania programu. W bliku `bibl.c`  umieściliśmy **definicje** naszych funkcji (Definicja funkcji ściśle określa jak ma działać funkcja - to jest po prostu jej kod.).  Dodatkowo, utworzyliśmy plik `bibl.h`, który zawiera deklaracje: funkcji zdefiniowanych w pliku `bibl.c` oraz dwóch struktur, których używamy zarówno w `main.c` jak i `bibl.c`. Aby te deklaracje były dostępne plikach źródłowych `*.c` musieliśmy dołączyć je w każdym z nich za pomocą instrukcji:

    ```c
    #include "bibl.h"
    ```

    Zwróć uwagę, że zamiast znaków `<>`, użyliśmy `""`. Związane to jest z tym, że użycie `""` powoduje, że kompilator będzie szukał tych plików w tym samym katalogu co znajduje się plik źródłowy. Gdy użyjemy `<>` to kompilator będzie szukał globalnych bibliotek języka C.
    

    W ten sposób w osobnych plikach znalazły się osobne funkcjonalności naszej aplikacji - zaczęliśmy pisać proste moduły :-). 

    

13. Proces kompilacji programu składającego się z dwóch plików wymagał od nas podania obydwu plików źródłowych tak:

    ```bash
    cc main.c bibl.c -o main
    ```

14. Dalej postanowiliśmy wprowadzić koncepcję Makefile'i. Makefile stanowią opis komend jakie należy wykonać aby skutecznie skompilować program do postaci wykonywalnej i ewentualnie go uruchomić. Dzięki napisaniu Makefile'a możemy teraz w katalogu gdzie znajduje się projekt wpisać po prostu `make`. Nie musimy już pamiętać jakich plików źródłowych (ewentualnie bibliotek) korzysta nasz program.


    Treść makefile wygląda tak:

    ```makefile
    all:
    	cc main.c bibl.c -Wall -o main
    ```

    Od tej pory a każdym razem gdy wpiszemy `make` wykona się komenda:
    `cc main.c bibl.c -Wall -o main`

    

Na kolejnych zajęcia przyjrzymy się dokładniej makefile'om i procesowi kompilacji, linkowania i budowania bibliotek. Jednocześnie zaczniemy dynamicznie zarządzać pamięcią.



