Na 10-tym seminarium poruszyliśmy 'szeroki wachlarz' problemów :-)

Scenariusz:

* Omówiliśmy strukturę programu obliczającego wartości wielomianu,
  * funkcja `main` zaczyna się od deklaracji trzech sekcji zmiennych: a) struktur, które będą przechowywać uchwyty do otwartych plików, b) trzech wektorów przechowujących odpowiednio współczynniki wielomianu, wartości współrzędnych X oraz wartości wyniku - czyli wartości naszego wielomianu dla odpowiednich współrzędnych x, oraz c) dwóch zmiennych przechowujących rzeczywiste długości (rozmiary) wektorów a i x (wektor f ma ten sam rozmiar co x).
  * dalej mamy w `main` standardowy scenariusz: 
    * otwieramy pliki (dwa do odczytuj - tryb "r", i jeden do zapisu - tryb "w")
    * wczytujemy dane wejściowe z plików (dwa wywołania `read_vec`)
    * obliczamy wartości wielomianu dla poszczególnych współrzędnych X  i wynik zapisujemy w f
    * zapisujemy wyniki do pliku zbudowanego z dwóch kolumn, rozdzielonych przecinkiem (pierwsza kolumna to wartości współrzędnych X a druga to wartości wielomianu) - w skrócie zapisujemy x i f
    * pamiętamy o **zwolnieniu zasobów** - czyli zamknięciu plików za pomocą `fclose(...)`.
* przypomnieliśmy, jak obliczany jest wielomian - pokazaliśmy, że często wygodniej jest zapisać scenariusz obliczania, proces w formie algorytmicznej, ponieważ wtedy jest łatwiej napisać do niej kod programu,\
  \
  ![p(x) = a_0 + a_1 x + a_2 x^2 + \ldots + a_n x^n](https://latex.codecogs.com/svg.latex?p(x)&space;=&space;a_0&space;&plus;&space;a_1&space;x&space;&plus;&space;a_2&space;x^2&space;&plus;&space;\ldots&space;&plus;&space;a_n&space;x^n)

  lub w formie algorytmicznej

  ![p(x) = \sum\limits_{i=0}^{n} a_i x^i](https://latex.codecogs.com/svg.latex?p(x)&space;=&space;\sum\limits_{i=0}^{n}&space;a_i&space;x^i)\
  \
  następnie napisaliśmy bardzo prosty kod obliczający wartość wielomianu dla jednego x:

  ```
  s=0;
  for (i=0;i<=n;i++)
      s += a[i]*pow(x,i);
  ```

  a gdybyśmy mieli wektor takich x-ów to moglibyśmy napisać:

  ```
  for (j=0;j<nx;j++) {
      s=0;
      for (i=0;i<=n;i++)
          s += a[i]*pow(x[j],i);
      f[j] = s;
  }
  ```

  albo po prostu od razu:

  ```
  for (j=0;j<nx;j++) {
      f[j]=0;
      for (i=0;i<=n;i++)
          f[j] += a[i]*pow(x[j],i);
  }
  ```

  użyliśmy funkcji `pow()` z biblioteki matematycznej dlatego musieliśmy:
  * dodać do pliku instrukcję dołączenia pliku nagłówkowego: `#include <math.h>`
  * zlecić programowi do konsolidacji (linkowania) dołączenie do naszego ostatecznego programu wykonywalnego biblioteki matematycznej, która zawiera implementację (czyli definicję) funkcji matematycznych, między innymi `pow`:

    `gcc prog09.c bibl.c -o prog09 -lm`

    (zwróćcie uwagę na ostatni argument `-lm`,  który sprawia, że dołączamy bibliotekę matematyczną, określoną bardzo krótką, jednoliterową nazwą, po prostu `m`.) \
    Opcję tą dodaliśmy do pliku `makefile`.
* następnie omówiliśmy strukturę pliku wynikowego, składającego się z dwóch kolumn: pierwszej zawierającej wartości współrzędnej X-owej oraz drugiej zawierającej wartości zadanego wielomianu dla odpowiadających wartości X z pierwszej kolumny,
* szybko przeszliśmy przez to, jak zbudowana jest funkcja `read_vec`.  Zawiera ona pętlę while, która sprawdza dwa warunki: czy udało się wczytać z pliku kolejną jedną liczbę typu double (scanf wtedy zwraca wartość jeden) oraz czy przypadkiem nie wczytaliśmy już maksymalnej liczby elementów wektora - ta maksymalna liczba wynika z zarezerwowanego miejsca w wektorze przekazanym do funkcji wczytującej.
* w kolejnym etapie napisaliśmy prościutki programik w Pythonie, aby narysować wykres wielomianu na ekranie (to był dodatek do naszego przedmiotu i znajomość Pythona nie będzie wymagana na zaliczeniu!),
* później stwierdziliśmy, że naiwny / definicyjny sposób wyznaczania wartości wielomianu jest nieefektywny z punktu widzenia kumulacji błędu zaokrągleń, dużo efektywniejszym jest tzw. schemat Hornera (<https://pl.wikipedia.org/wiki/Schemat_Hornera>),
* dalej, ponieważ nie byliśmy pewni, której implementacji obliczania wielomianu używamy, więc dodaliśmy funkcję `printf`ze stosowną informacją,
* w kolejnym etapie chcieliśmy mieć możliwość szybkiego (w jednym miejscu) włączania i wyłączania tych komunikatów diagnostycznych (mowa o `printf`ach) - w tym celu dodaliśmy nowy plik utils.h i dodaliśmy do niego makro `#define debug(...) printf(__VA_ARGS__)`, które w miejscu użycia go wstawi `printf`z argumentem takim samym jak podano do `debug`, ale tylko wtedy jeżeli na etapie kompilacji będzie zdefiniowane makro `DEBUG`; dołączyliśmy ten plik na górze `bibl.c` ;
* stwierdziliśmy, że wygodnie będzie definiować czy nasz program ma pracować w trybie 'z debugingiem', czy 'bez debugingu' w `Makefile`. W tym celu zdefiniowaliśmy w nim zmienną `CFLAGS`, która albo zawiera wartość `-DDEBUG`, albo jest pusta,
* wartość `-DDEBUG` to opcja `-D` z argumentem `DEBUG` przekazywana do kompilatora, która sprawia że definiuje on w procesie przetwarzania wstępnego (*ang. preprocessing*) i kompilacji makro `DEBUG`,
* pamiętajmy, że makrodefinicje `#ifndef`, `#else`, itp., działają na etapie preprocesingu - czyli przetwarzania oryginalnego kodu źródłowego w innych kod źródłowy, na zasadzie podstawiania zmodyfikowanej treści kodu w miejsce użycia makrodefinicji, oraz uwzględniania fragmentów w procesie kompilacji lub nie (zwłaszcza w kontekście `#ifdef`) - to `n` w środku nie jest błędem, raz jest to `if not defined` a innym razem `if defined`. A oznacza, że blok kodu będzie interpretowany przez kompilator tylko wtedy, gdy jakaś makrodefinicja nie będzie zdefiniowana lub będzie.
* na koniec w telegraficznym skrócie postanowiliśmy napisać program w wersji dynamicznej - o tym napiszemy trochę dłużej w osobnym podrozdziale.

## Wersja z dynamiczną alokacją pamięci

Motywacja: wersję z dynamiczną alokacją napiszemy po to, aby móc wczytywać wektory o dowolnej długości oraz aby efektywniej zarządzać pamięcią. W pierwotnej wersji programu wektory były prealokowane i zawsze zajmowały w pamięci `50*sizeof(double)` bajtów. W wersji z dynamiczną alokacją wektor będzie zajmować rozmiar miejsca w pamięci odpowiadający rzeczywistej długości wektora.

Scenariusz działania takiej funkcji jest nastepujący:

1. Oczekujemy, że funkcja zwróci rzeczywisty rozmiar wektora wczytanego z pliku.
2. Oczekujemy, że funkcja otrzyma wskaźnik do zmiennej, w której zapisze lokalizację wektora z liczbami wczytanymi z pliku. Mówiąc po ludzku: zwrócić adres tego wczytanego wektora w pamięci operacyjnej. Zakładamy, że nasza funkcja zarezerwuje gdzieś pamięć o odpowiedniej długości i zwróci jej adres.
3. Funkcja będzie działać następująco:
   1. funkcja wczyta kolejną liczbę
   2. sprawdzi, czy wczytana liczba jest pierwsza, jeżeli tak to utworzy nowy wektor o rozmiarze 1
   3. zapisze wczytaną liczbę na pierwszej pozycji
   4. wczyta następną liczbę
   5. sprawdzi, czy to pierwsza - oczywiscie nie, więc utworzy znowu nowy wektor, ale tym razem o długości 2, i przepisze w jego 1 miejsce wartość z poprzedniego wektora,
   6. na końcu nowego, dwuelementowego wektora wpisze wczytaną liczbę (tą drugą),
   7. wczyta następną liczbę
   8. sprawdzi czy to pierwsza - oczywiście nie, więc utworzy znowu nowy wektor, ale tym razem o długości 3,  i przepisze w jego dwa pierwsze miejsca wartości z poprzedniego wektora,
   9. itd...
4. Zapis algorytmiczny w tzw. ***pseudokodzie ***takiej funkcji mógłby wyglądać następująco (operację `:=` należy czytać 'staje się'):

   ```
   vo := NULL
   n := 0
   while (d = read())
       vn = new_vector(n+1)
       if vo is not NULL:
           vn[from 1 to n] := vo
       vn[end] := d
       vo=vn
       n = n + 1
   return vn
   ```

   Proszę zwrócić uwagę, że w powyższym przykładzie algorytmicznym nie zajmujemy się zupełnie niuansami związanymi z argumentami, wskaźnikami, zwracanymi przez funkcję wartościami, itp.. To jest pseudokod w ideowy sposób  ilustrujący i opisujący działanie algorytmu. Uwaga! Proszę zapamiętać co oznacza pseudokod! Takie pytanie może pojawić się na zaliczeniu!
5. Zapis w języku `C` takiej funkcji może wyglądać, tak jak napisaliśmy na wykładzie:

   ```
   int read_vec(FILE * fin, double **v){
       double d;
       int n = 0, j;
       double *vn; // v new
       double *vo = NULL; // v old
       while ( fscanf(fin, "%lf", &d) == 1 ) {
           vn = (double*) malloc( sizeof(double) * (n+1));
           for (j = 0; j < n; j++) {
               vn[j] = vo[j];
           }
           if (vo != NULL)
               free(vo);
           vn[n] = d;
           vo = vn;
           n++;
       }
   
       *v = vn;    
       return n;
   }
   ```

   Zwróćmy uwagę na następujące szczegóły języka `C`:

   Alokację pamięci:

   ```
   vn = (double*) malloc( sizeof(double) * (n+1));
   ```

   gdzie wykorzystujemy tzw. **jawne rzutowanie** na typ wskaźnik do double. Co więcej, podajemy ilość potrzebnej pamięci w bajtach, czyli sizeof(double) - to ilość bajtów zajmowana przez jedną liczbę typu double razy rozmiar wektora.

   Zwracamy dwa wyniki: jeden za pomocą returna, czyli rzeczywistą liczbę wczytanych elementów n, a drugi za pomocą przekazanego do funkcji wskaźnika do wskaźnika typu double (`double **v`). Mówiąc po ludzku chcemy w jakiejś zmiennej zapisać adres naszego wektora. Adres naszego wektora to typ danych `double*`, a ponieważ chcemy ten adres gdzieś zapisać w miejscu, które jest poza naszą funkcją, to musimy uzyskać adres tego miejsca-zmiennej (czyli adresu). Dlatego mamy adres zmiennej przechowującej adres, czyli wskaźnik do zmiennej przechowującej wskaźnik. Gdybyśmy uczestniczyli w aferze szpiegowskiej to podalibyśmy adres skrytki na dworcu kolejowym, w której znajdowałby się adres do naszego skarbu (czyli wektora liczb) :-).

   A gdy chcemy zwrócić wynik to uzywamy `*v = vn`, co po ludzku (:-)) mogłoby oznaczać do zmiennej wskazywanej przez adres `v` wpisz adres mojego 'zaalokowanego' wektora.

Dalej zaczęliśmy używać programu valgrind, który w środowiskach linuxowych efektywnie jest w stanie wykryć tzw. wycieki pamięci, lub niewłaściwe odwołania do niezainicjowanych zmiennych, itp. Zauważyliśmy, że tracimy pamięci, ponieważ w pierwotnej wersji nie używaliśmy instrukcji free, która ma za zadanie zwolnić te pośrednie wektory, które mozolnie tworzymy w trakcie wczytywania.

Okazało się, że tych free brakowało trochę więcej (w mainie) :-). Co więcej, okazało się w trakcie używania valgrinda, że niewłaściwie mamy również zaimplementowaną funkcję wyznaczającą wartość wielomianu - po prostu nie alokujemy tam pamięci! I to jest zadanie dla was - proszę poprawić implementację i sprawić, aby valgrind nie wyświetlał żadnych błędów ani ostrzeżeń.

Uwagi końcowe:

Taka implementacja dynamicznej alokacji pamięci jest nieefektywna - takie zmienianie rozmiaru wektora przy każdej wczytanej liczbie wymaga za każdym razem kopiowania wcześniej wczytanych wartości... Na następnym wykładzie opowiemy jakie możemy zastosować skuteczniejsze metody dynamicznego wczytywania wektorów.

Wesołych Świąt i Szczęśliwego Nowego Roku

Robert Szmurło, grudzień 2019
