# Seminarium 2

Uwaga! Znajdź na tej stronie link: [Zadanie 2](zadanie2.md)

Scenariusz zajęć:

1. Powtórka materiału z poprzedniego wykładu

   * architektura warstwowa,
   * budowa komputera (szyna komunikacyjna, protokóły)
   * proces wytwarzania oprogramowania (wymagania dziedzinowe - czyli co ma robić aplikacja,  wymagania funkcjonalne -  czyli jak będzie udostępniać swoje funkcje i algorytmy użytkownikowi, projekt implementacji - czyli jak to będzie robić, programowanie - tworzenie kodu, testowanie - sprawdzanie czy robi to co trzeba, najlepiej na bieżąco za pomocą testów jednostkowych [wspomnieć o TDD], testowanie integracyjne - czyli testowanie końcowego wyniku)
   * jak przebiega proces budowania kodu programu zaczynając od kodu źródłowego,
     * edycja kodu
     * preprocesing (przetwarzanie tekstu kodu w innych tekst kodu)
     * kompilacja (tłumaczenie kodu tekstowego na maszynowy)
     * linkowanie czyli po polsku konsolidacja :-) (utworzenie programu wykonywalnego na dysku takiego, który może zostać wczytany przez system operacyjny i któremu mogą zostać przydzielone zasoby) [Quizz: kto wczytuje program z dysku: menadżer plików, powłoka testowa czyli shell, czy może system operacyjny?]

2. Napisanie programu witaj świecie, powtórzenie komend i programów do tworzenia plików (wprowadzenie Visual Studio Code), `cc pierwszy.c`.

   ```c
   #include <stdio.h>
   
   int main(int argc, char *argv[]) {
       printf("Witaj świecie\n");
       return 0;
   }
   ```

3. Dodanie do programu witaj świecie informacji o liczbie argumentów podanych w linii komend.

   ```c
   #include <stdio.h>
   
   int main(int argc, char *argv[]) {
      printf("Witaj świecie podałeś %d argumentów %%!\n", argc);
      return 0;
   }
   ```

4. Dodanie d programu wyświetlania wszystkich argumentów podanych z linii komend.

   ```c
   #include <stdio.h>
   
   int main(int argc, char *argv[]) {
       int i;
   
       printf("Witaj świecie podałeś %d argumentów %%!\n", argc);
   
       for (i=0; i<argc;) {
           printf("%s\n", argv[i]);
           i = i + 1;
       }
   
       return 0;
   }
   ```

5. Wariacje z pętlą `for` i zwiększaniem wartości `i` o jeden!

   ```c
   #include <stdio.h>
   
   int main(int argc, char *argv[]) {
       int i;
   
       printf("Witaj świecie podałeś %d argumentów %%!\n", argc);
   
       /* argc = 0; */
       for (i=0; i<argc; i++) {
           printf("%s\n", argv[i]);
           /* i = i + 1; */
           /* i += 1; */
           /* i++; */
       }
   
       return 0;
   }
   ```

6.  Wyświetlanie więcej informacji o argumentach (numer pozycji argumentu):

   ```c
   #include <stdio.h>
   
   int main(int argc, char *argv[]) {
       int i;
   
       printf("Witaj świecie podałeś %d argumentów %%!\n", argc);
   
       /* argc = 0; */
       for (i=0; i<argc; i++) {
           printf("[%d]: %s\n", i, argv[i]);
           /* i = i + 1; */
           /* i += 1; */
           /* i++; */
       }
   
       return 0;
   }
   ```

7. Rozpoczęcie programu do sumowania wartości liczbowych podanych jako argumenty linii komend. Program z błędami :-)

   ```c
   #include <stdio.h>
   
   int main(int argc, char *argv[]) {
       int i;
       double s;
   
       for (i = 0; i < n; i++) {
           s = s + atof(argv[i]);
       }
   
       printf("Suma = %d\n", s);
   
       return 0;
   }
   ```

   Błędy: brak `stdlib.h`, niezaincjalizowane `s`, uwzględnianie w sumie pierwszego argumentu (najlepiej pokazać na iloczynie ;-) za chwilę), `%d` zamiast `%lf` w printfie.

8. Wersja poprawiona:

   ```c
   #include <stdio.h>
   #include <stdlib.h>
   
   int main(int argc, char *argv[]) {
       int i;
       double s = 0;
   
       for (i = 0; i < n; i++) {         
           s = s + atof(argv[i]);
       }
   
       printf("Suma = %lf\n", s);
   
       return 0;
   }
   ```

9. Dodajmy liczenie iloczynu skalarnego zgodnie ze wzorem:

   $$p = \prod\limits_{i=1}^{\text{argc}-1} \text{atof}(\text{argv}[i])$$
   
   <a href="https://www.codecogs.com/eqnedit.php?latex=p&space;=&space;\prod\limits_{i=1}^{\text{argc}-1}&space;\text{atof}(\text{argv}[i])" target="_blank"><img src="https://latex.codecogs.com/gif.latex?p&space;=&space;\prod\limits_{i=1}^{\text{argc}-1}&space;\text{atof}(\text{argv}[i])" title="p = \prod\limits_{i=1}^{\text{argc}-1} \text{atof}(\text{argv}[i])" /></a>

   ```c++
   #include <stdio.h>
   #include <stdlib.h>
   
   int main(int argc, char *argv[]) {
       int i;
       double s = 0;
       double p = 1;
       
   
       for (i = 0; i < n; i++) {
           s = s + atof(argv[i]);
           p = p * atof(argv[i]);
       }
   
       printf("Suma = %lf\n", s);
       printf("Iloczyn = %lf\n", p);
   
       return 0;
   }
   ```

10. A teraz po prostu aby nie było dwa razy `atof` wprowadzimy zmienną lokalną.

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(int argc, char *argv[]) {
        int i;
        double s = 0;
        double p = 1;
        
    
        for (i = 0; i < n; i++) {
            double l = atof(argv[i]) ; 
            s = s + l;
            p = p * l;
        }
    
        printf("Suma = %lf\n", s);
        printf("Iloczyn = %lf\n", p);
    
        return 0;
    }
    ```

11. Na sam koniec wczytajmy dane podane jako argumenty linii komend, skonwertujmy je na liczby typu double i zapamiętajmy w wektorze `v[]`. Uwaga! Wektor `v[]` jest o jeden krótszy od wektora z listą argumentów, ponieważ lista argumentów zawiera również nazwę pliku na pierwszej pozycji `v[0]`.
    

    Wprowadzamy również na tym etapie zmienną pomocniczą `n` przechowującą rozmiar naszego wektora z liczbami. (Bo np. nie chce nam się wszędzie pisać `argc-1`)

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(int argc, char *argv[]) {
        int i;
        double s = 0;
        double p = 1;
        int n = argc-1;
        double v[n];
    
        /* Interpretacja danych użytkownika. */
        for (i = 0; i < n; i++) {
            v[i] = atof(argv[i+1]);
        }
    
        for (i = 0; i < n; i++) {
            s = s + v[i];
            p = p * v[i];
        }
    
        for (i = 0; i < n; i++) {
            printf("v[%d] = %lf\n", i, v[i]);
        }
    
        printf("Suma = %lf\n", s);
        printf("Iloczyn = %lf\n", p);
    
        return 0;
    }
    ```

12. Praca domowa: dodać do programu wyświetlanie wartości maksymalnej.
