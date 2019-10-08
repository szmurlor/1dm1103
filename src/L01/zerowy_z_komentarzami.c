/* Ponizsza linijka to dyrektyrwa preprocesora, taka instrukcja dla kompilatora, ze bedziemy
 * uzywac funkcji i zmiennych z biblioteki standardowej wejścia-wyjścia: std io */
#include <stdio.h>

/*
 * To jest komentarz. Komentarz jest pomijany przez kompilator.
 */


/* Linijka ponizej to jest deklaracja funkcji main. Kolejne linijki to jest definicja funkcji main.
 * Deklaracja to określenia co funkcja będzie zwracać i jakie argumenty będzie wymagać.
 * Definicja to jest ciąg instrukcji wchodzącej w skład funkcji.
 *
 * int na początku oznacza, że funkcja main będzie zwracać liczbę całkowitą jako wynik
 * int argc - to argument, który powinien zawierać liczbę argumentów podanych przez użytkownika
 * w momencie uruchomiena programu.
 * char *argv[] - to tablica napisów zawirająca klejne argumenty (parametry) podane w linii komend.  */
int main(int argc, char *argv[]) {
        int i; /* to jest zmienna pomocnicza, którą będziemy zwiększąć o jeden w pętli for i, której
                  wartość będziemy sprawdzać, że stwierdzić czy zakończyć pętlę. */
        for (i = 0; i < argc; i++)
                printf("%s", argv[i]); /* to jest funkcja standardowa wypisująca napis na standrowe wyjście  */
 
        return 99; /* wynik zwracany przez funkcję main, który możemy odczytać wpisują w terminalu (konsoli)
                      echo $? tuż po uruchomieniu naszego programu. */
}

/* Ten program wygląda strasznie z tymi komentarzami i już tak więcej nie będę pisać...*/
