1. Omówiona architektrura komputera
2. Omówiona architektura warstwowa. System operacyjny jako pośrednik między programami użytkownika a sprzętem.
3. Omówiony proces kompilacji, budowania programu. Wytłumaczone co to jest program wykonywalny.
4. Przedstawione generacje języków programowania (1,2,3,4 poziom...)
5. Wytłumaczone co  jest i jaka jest rola preprocesora.
6. To system operacyjny uruchamia program: wczytuje do pamięci program, rezerwuje pamięć (stos i sterta) rozpoczyna wykonywanie programu na mikroprocesorze. 
7. Zwróciłem uwagę, że programy wykonują się sekwencyjnie - koemnda po komendzie (licznik rozkazów).
8. Zwróciłem uwagę na konieczność zarządzania i kontroli pamięci (program valgrind)
9. Program zwraca rożne rodzaje wyników: wynikiem dla użytkownika jest to co jest wypisane na ekranie, to co użytkownik może przeczytać, wynikiem dla systemu operacyjnego jest wartość liczbowa, całkowita, którą zwraca funkcja `int main() { ... return 0;}`, wartość `0` oznacza sukces. Każda inna to kmunika o błędzie. POkazałem jak wykorzystuje to program `make` do sprawdzenia czy program wykonał się poprawnie.
10. Przekazywaliśmy do programu argumenty linii komend (rozdzielone znakiem spacji). Funkcja main otrzymuje informację o tych argumentach w tablicy napisów: `int main(int argc, char *argv[])`, gdzie `argc` to liczba podanych podczas uruchamiania programu argumentów, a `argv` to tablica napisów.
11. Powiedzieliśmy o opcjach kompilatora `-Wall` oraz `--pedantic`, które sprawiają, że kompilator stara się przeanalizować kompilowany kod i wyświetlić użytkownikowi ostrzeżenia, gdy napotka potencjalne problemy.
 