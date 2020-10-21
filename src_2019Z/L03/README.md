Dzisiaj strasznie dużo czasu poświęciliśmy na prezentacje programowania w języku C pod Windowsami… Zasadniczo więcej nie będziemy do tego wracać na seminarium! Musicie państwo samodzielnie poćwiczyć! Musicie zacząć programować lokalnie na waszych komputerach, ponieważ wkrótce zaczniemy używać wielu plików i  narzędzia online staną się bardzo niewygodne lub nieużyteczne.

Trochę czasu również poświęciliśmy systemowi kontroli wersji `git`. Zaznaczam , że system kontroli wersji `git` nie służy do komiplacji. To jest narzędzie ułatwiające sledzenie zmian oraz scalanie zmian (* ang. merge changes*) zrealizowaych przez różnych programistów.


Podstawowe pojęcia związane z `git`. Warto zajrzeć na strony (https://rogerdudler.github.io/git-guide/index.pl.html, https://python101.readthedocs.io/pl/latest/git/, )

* centralne repozytorium (to jest dla github, ale nie musi, ale o tym kiedy indziej)

* lokalne repozytoria a właściwie kopie centralnego (czyli klony), może ich być wiele...

* pierwszą rzeczą klonujemy centralne repozytorium do naszego bieżącego katalogu za pomocą komendy:

  ```bash
  git clone https://github.com/szmurlor/1dm1103.git
  ```

- otrzymamy w katalogu lokalnym nowy folder o nazwie `1dm1103` w którym będą wszystkie pliki z naszego seminarium

- gdy wykonamy jakieś zmiany w plikach to zatwierdzamy ich paczkę wykonując commit wpisując:

  ```bash
  git commit -a
  ```

  nie zapominamy o konieczności wpisania komentarza ;-)

- 	Gdy chcemy zaktualizować lokalną kopię pobierając przesłane zmiany przez innych na serwer to 'ciągniemy' te zmiany wpisując:

   ```bash
   git pull
   ```

- 	Gdy chcemy wysłać wszystkie zatwierdzone przez nas paczki zmian (commity) to wpychamy je na serwer wpisując:

   ```bash
   git push
   ```

- 	Uwaga, aby konkretny plik mógł podlegać kontroli wersji musi zostać dodany do listy śledzonych plików przez gita za pomocą komedy:

   ```bash
   git add nowy_plik.c
   ```


- 	Od tej pory, każde wpisanie komendy `git commit -a` będzie sprawdzać, czy wykonaliśmy w danym pliku jakieś zmiany. Jeżeli tak to zmiany te zostaną uwzględnione jako paczka zmian (commit).

Proszę się na razie nie martwic za bardzo gitem! To na razie tylko zasygnalizowanie tematu. Będziemy tego używać na bieżąco i do końca semestru dojdziecie do wprawy :-).

1. Instalacja kompilatora C pod Windows (użyć msys2 a potem pacman -S base-devel gcc)
   Kilka danych i linków (to jest powtórzenie informacji z ISODa :-):

   Chcemy używać komendy `cc`  skrótu do `gcc`. Kroki:

   - Ściągamy pakiet instalacyjny msys2: (np.: http://www.msys2.org/ 
   - Po instalacji podsystemu Unix należy uruchomić go z menu start (wyszukując msys2)  
   - W nowo otwartym oknie terminala należy zainstalować kompilator języka C oraz klienta git wpisując komendę:  `pacman -S base-devel gcc`, (Więcej o iinstalacji kompilatora C pod msys2 na stronie: https://www.devdungeon.com/content/install-gcc-compiler-windows-msys2-cc)
   - Potem w PowerShellu, który otwieramy w Visual Studio Code możemy wpisać  `$env:PATH = 'C:\msys64\usr\bin\;$env:PATH'` (ten krok jest potrzebny po to aby programy [kompilator, itp.] były dostępne jako komendy) Celem tej komendy jest rozszerzenie listy przeszukiwanych folderów w celu odnalezienia programu do uruchomienia po wpisaniu danej komendy. Alternatywnie możemy (i zachęcam do tego) dopisać ścieżkę w zmiennych środowiskowych globalnie dla cąłego komputera (Właściwości mojego komputera, ustawienia zaawansowane, zmienne środowiskowe…)

2. Instalacja Visual Studio Code (to powinno byc proste: https://code.visualstudio.com/download)

3. Prypominam na wszelki wypadek o konfiguracja ścieżki PATH c:\msys64\usr\bin za pomocą komend w Power Shellu: `$env:PATH='C:\msys64\usr\bin;$env:PATH'`

4. Przykładowa kompilacja w Visual Studio Code (wciśnięcie otwiera wbudowaną powłokę power shell w Windows: CTRL+\` i CTRL+SHIFT+\`)

5. Dodajemy funkcje: sumującą i wypisującą wektor na ekranie. Argumenty, wartości zwracane. Skupiamy się na argumentach i wartości  zwracanej.


   ```c
   double suma(int n, double v[]) {
       int i;
       double s = 0;
   
       for (i = 0; i < n; i++) {
           s = s + v[i];
           /*p = p * v[i];*/
       }
   
      /* printf("W sumie: %lf\n", s); */
   
       return s;
   }
   ```

   Rozmawialiśmy o kontekstach, zasięgu widoczności zmiennych (to struktura drzewiasta i kluczowa jest każda klamerka, która tworzy nowy obszar dla zmeinnych, obszary zagnieżdżone widzą zmienne tylko ze swoich rodziców, nie widzą zmiennych z sąsiednich kontekstów (bloków kodu, funkcji, itp.))

6. Uczyliśmy się trochę debugować kod. Idea to izolacja fragmentu kodu gdzie występuje błąd. Używaliśmy do printfa wypisując w różnych miejscach kodu poszczególne wyniki.

7. Potem dodaliśmy analogicznie wypisywanie na ekranie:


   ```c
   void wypisz(int n, double v[]) {
       int i;
       for (i = 0; i < n; i++) {
           printf("v[%d] = %lf\n", i, v[i]);
       }
   }
   ```

   Proszę zwrócić uwagę, że funkcja *wypisująca* zwraca `void`, który po prostu oznacza: *nic*. Czyli funkcja nic nie zwraca dlatego nie ma nawet i nie jest potrzebny żaden `return` w funkcji.

8. Różnica między pętlą `while`, `for` i `do … while`. Zasadniczo wszystko to samo można zrobić przy użyciu każdej z pętli ale w odrobinę inny sposób. Pętla `while` używana wtedy gdy nie jesteśmy w stanie przewidzieć ile wykonamy operacji. Różnice w implementacji zobrazowaliśmy implementując iloczyn wartości wektora:

   ```c
   double iloczyn(int n, double v[]) {
       int i;
       double p = 1;
   
   /*    for (i = 0; i < n; i++) {
           p = p * v[i];
       }
   */
       i = 0;
       while(i < n) {
           p = p * v[i];
           i = i + 1;
           /* i += 1; */
           /* i++; */
           /*++i; */
       }
       
       /*
       i = 0;
       do {
           p = p * v[i];
           i = i + 1;
           v = (i++)*3
       } while(i < n);
       */
   
       return p;
   }
   ```

9. Przy okazji prezentacji while i do … while wprowadziliśmy operator *inkrementacji* - `++` w postaci postfixowej - `i++` i prefixowej `++i` (czyli po i przed zmienną). Różnica jest taka, że w przypadku notacji postfixowej (za zmienną) wartość zmiennej zostanie zwiększona po wykonaniu 'wszystkich' operacji w danym wierszu. W przypadku prefixowej, operacja inkrementacji zostanie wykonana przed jakimikolwiek operacjami - zwłaszcza przypisania w danym wierszu. Różnicę prześledziliśmy na przykładzie banalnego programu:

   ```c
   #include <stdio.h>
   
   int main() {
       int i = 3;
       /* int v = (++i) * 2; */
       int v = (i++) * 2;
       printf("%d\n", v);
       return 0;
   }
   ```

10. Zmodyfikujmy funkcję wypisującą na ekranie tak aby była w stanie albo zapisać do pliku albo wypisać na ekranie i nazwijmy ją zapisz. (tutaj chcieliśmy, ale się nie udało trochę powiedzieć o operatorze warunkowego przypisania i słowie kluczowym `if`.)

    

    ```c
    void zapisz(int n, double v[]) {
        int i;
        FILE * fout;
        fout = fopen("wektor.txt", "w");
        for (i = 0; i < n; i++) {
            fprintf(fout, "%lf\n", v[i]);
        }
        fclose(fout);
    }
    ```

    `printf` został zastąpiony `fprintf`, a jako pierwszy do niego argument przekazana została struktura danych reprezentująca uchwyt do otwartego za pomocą funkcji `fopen` pliku o sztywno wpisanej nazwie `wektor.txt`.

    Zwróciliśmy uwagę na to, że plik musi być zamknięty (`fclose(fout)`) aby faktycznie dane zostały zapisane na dysk. W przeciwnym razie w celu poprawienia wydajności działania programów początkowo są przechowywane w szybkiej pamięci operacyjnej.

    Struktura `FILE * fout` zawiera *magiczne* informacje o otwartym pliku, które całkowicie są obsługiwane przez język C i nie musimy do niej zaglądać… :-)

    Drugim argumentem do funkcji `fopen` jest napis `"w"`, który oznacza, że chcemy otworzyć plik do zapisu (*ang. write*).

11. W międzyczasie nie możemy zapomnieć, że stworzyliśmy funkcję, która przetwarza argumenty podane w linii komend przez użytkownika z postaci tekstowej (z tablicy `char *argv[]`) do postaci zmiennoprzecinkowej `double v[]`.

    

    ```c
    /* Interpretacja danych użytkownika. */
    void wczytaj(int n, double v[], char *argv[]) {
        int i;
        for (i = 0; i < n; i++) {
            v[i] = atof(argv[i+1]);
        }
    }
    ```

12.  W międzyczasie zmieniliśmy wygląd bardzo długiej funkcji `main` w czytelny SPIS TREŚCI:

    

    ```c
    int main(int argc, char *argv[]) {
        int n = argc-1;
        double v[n];
    
        wczytaj(n,v,argv);
        wypisz(n,v);
        printf("Suma = %lf\n", suma(n,v) );
        printf("Iloczyn = %lf\n", iloczyn(n,v) );
        zapisz(n,v);
    
        return 0;
    }
    ```

      
   Używając sformułowania *spis treści* mam na myśli, to, że funkcja `main` stanowi teraz w kolejnych linijkach czytelnie wyświetlony scenariusz działania (algorytm) naszego programu bez wnikania w szczegóły implementacyjne. Jednym rzutem oka od razu widzimy co robi nasz program i do czego służy. Osiągnęliśmy to dzięki:
    
   - zastosowaniu logicznie uzasadnionego podziału na funkcje, które robią tylko to do czego zostały napisane; z zasady powinniśmy pisać funkcje robiąca *jak najmniej*. Ułatwi to nam w przyszłości testowanie programów.
   - zastosowaniu czytelnych i precyzyjnych nazw funkcji - nazwa funkcji odzwierciedla dokładnie to co funkcja robi.
    
 
