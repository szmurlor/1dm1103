## Plan seminarium 9:

1. Dynamiczne zarządzanie pamięcią dynamicznej struktury danych (powiększanie, usuwanie, wstawianie, elementów)
2. Pliki nagłówkowy - podział programu na moduły

## Opis funkcjonalny programu

Napiszemy program, który będzie wczytywać wektor liczby i wykonywać na nim zadane operacje - sumowanie, 
dodawanie nowych wartości, wstawianie nowych wartości na określonej pozycji, usuwanie danych z końca,
usuwanie danych ze środka zbioru danych.

## Struktury danych:

Nie będziemy mówić o strukturach w języku C typu 'struct'. Tamte struktury służą do wygodnego przechowywania
w jednolitych fragmentach pamięci operacyjnej zbioru związanych ze sobą funkcjonalnie atrybutów (wartości).
Przykładem takiej struktury był student.

Dzisiaj zajmiemy się strukturami danych w sensie programowania, algorytmiki i informatyki.

W programowaniu wyróżniamy następujące typy struktur danych:

1. Typy podstawowe (int, float, double, char, itp...) - jestęsmy w stanie wykonać na nich proste operacje
   oraz przede wszystkim użyć na nich operatora przypisania `=`
2. Typy złożone (struct), które służą do uporzadkowania fragmentu pamięci operacyjnej i przyporządkowania
   odpowiednim jej kawałkom typów prosych.
3. Struktury o swobodnym dostępie (tablice - jedno i wielowymiarowe, słowniki, itp...).
4. Struktury o dostępie sekwencyjnym (napisy, listy dynamiczne - jedno i dwielokierunkowe, drzewa binarne,
   struktury grafowe, itp.).

Rozwiązując różne problemy techniczne za każdym razem musimy wybrać odpowiednią strukturę danych.

Na przykład załóżmy banalny problem obliczenia wartości wielomianu dla zadanej wartości x. Załóżmy, że 
chcemy napisać program, który będzie efektywnie wyznaczał wartości określonego wielomianu
dla zadanego zbiore wartości x. Wielomian wyrazony jest w ogólności  funkcją:

$$f(x) = a_0 + a_1 x + a_2 x^2 + ... + a_n x^n$$

gdzie współczynniki $a_0, a_1,...$ są liczbami skalarnymi definiującymi nasz wielomian.

Postarajmy się rozwiązać problem napisania takiego programu uniwersalnie. To znaczy, że chcielibyśmy
mieć jeden program, który będzie wyznaczać wartości jakiegoś wielomianu (o dowolnie wybranym przez
użytkonika stopniu), z dowlnie określonymi przez użytkownika współczynnikami, dla dowolnie
wybranego przez użytkownika wektora współrzędnych x.

W celu rozwiązania będziemy chcieli aby użytkownik podawał jako wywołanie naszego programu dwa
pliki: 

a) plik z wartościami współczynników
b) plik z wartościami współrzędnych

Wynik będziemy zapisywać w pliku wynikowym, które nazwę użytkownik poda w momencie wywołania jako 
trzeci argument





1.  Piszemy n