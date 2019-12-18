Na 10-tym seminarium poruszyliśmy 'szeroki wachlarz' problemów :-)

Scenariusz:

* omówiliśmy strukturę programu obliczającego wartości wielomianu,
* przypomnieliśmy, jak obliczany jest wielomian - pokazaliśmy, że często wygodniej jest zapisać scenariusz obliczania, 
  proces w formie algorytmicznej, ponieważ wtedy jest łatwiej napisać do niej kod programu, 
* następnie omówiliśmy strukturę pliku wynikowego, składającego się z dwóch kolumn: pierwszej zawierającej wartości 
   współrzędnej X-owej oraz drugiej zawierającej wartości zadanego wielomianu dla odpowiadających wartości X z 
   pierwszej kolumny,
* w kolejnym etapie napisaliśmy prościutki programik w Pythonie, aby narysować wykres wielomianu na ekranie 
  (to był dodatek do naszego przedmiotu i znajomość Pythona nie będzie wymagana na zaliczeniu!), 
* później stwierdziliśmy, że naiwny / definicyjny sposób wyznaczania wartości wielomianu jest nieefektywny 
  z punktu widzenia kumulacji błędu zaokrągleń, dużo efektywniejszym jest 
  tzw. schemat Hornera (<https://pl.wikipedia.org/wiki/Schemat_Hornera>),
* dalej, ponieważ nie byliśmy pewni, której implementacji obliczania wielomianu używamy, więc dodaliśmy 
  funkcję `printf`ze stosowną informacją,
* w kolejnym etapie chcieliśmy mieć możliwość szybkiego (w jednym miejscu) włączania i wyłączania tych 
  komunikatów diagnostycznych (mowa o `printf`ach) - w tym celu dodalismy nowy plik utils.h i dodaliśmy do 
  niego makro `#define debug(...) printf(__VA_ARGS__)`, które w miejscu użycia go wstawi `printf`z argumentem 
  takim samym jak podano do `debug`, ale tylko wtedy jeżeli na etapie kompilacji będzie zdefiniowane makro `DEBUG`; 
  dołączyliśmy ten plik na górze `bibl.c` ; 
* stwierdziliśmy, że wygodnie będzie  definiować czy nasz program ma pracować w trybie 'z debugingiem', 
  czy 'bez debugingu' w `Makefile`. W tym celu zdefiniowaliśmy w nim zmienną `CFLAGS`, która albo zawiera 
  wartość `-DDEBUG`, albo jest pusta,
* wartość `-DDEBUG` to opcja `-D` z argumentem `DEBUG` przekazywana do kompilatora, która sprawia że definiuje on 
  w procesie preprocesingu i kompilacji makro `DEBUG`,
* pamiętajmy, że makrodefinicje `#ifndef`, `#else`, itp., działają na etapie preprocesingu - czyli przetwarzania 
  oryginalnego kodu źródłowego w innych kod źródłowy, na zasadzie podstawiania zmodyfikowanej treści kodu w miejsce 
  użycia makrodefinicji, oraz uwzględniania fragmentów w procesie kompilacji lub nie (zwłaszcza w kontekście `#ifdef`) - 
  to `n ` w środku nie jest błędem, raz jest to *if not defined* a innym razem *if defined*. A oznacza, że blok kodu 
  będzie interpretowany przez kompilator tylko wtedy, gdy jakaś makrodefinicja nie będzie zdefiniowana lub będzie.
* na koniec w telegraficznym skrócie postanowiliśmy napisać program w wersji dynamicznej - o tym napiszemy trochę dłużej 
  w osobnym podrozdziale.

## Wersja z dynamiczną alokacją pamięci

Motywacja: wersję z dynamiczną alokacją napiszemy po to, aby móc wczytywać wektory o dowolnej długości oraz aby 
efektywniej zarządzać pamięcią. W pierwotnej wersji programu wektory były prealokowane i zawsze zajmowały 
w pamięci `50*sizeof(double)` bajtów
