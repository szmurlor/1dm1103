# Plan seminarium 11

1. Przypominamy szybko obliczanie wartości wielomianu na tablicach
2. Przypominamy śledzenie wycieków pamięci za pomocą valgrind
3. Poprawiamy alokację pamięcie - nie za każdym razem, tylko preallokujemy zawsze dwa razy większy rozmiar,
    * potrzebujemy struktury `Wektor`, aby poprawić czytelność programu,
    * w strukturze zapamiętamy bieżący rozmiar oraz rozmiar zajmowanej pamięci,
    * utworzymy funkcje do inicjalizacji wektora,
    * utworzymy funkcje do dodawania elementu do wektora (push),
    * do wstawiania wartości na zadanej pozycji,
    * do usuwania ostatniego elementu (pop).
    Tym samym zaimplementujemy strukturę danych typu stos.
4. Przerabiamy program do liczenia wartości wielomianu za pomocą listy jednokierunkowej (skupiamy się na pokazaniu pisania funkcji do tworzenia, czyszczenia, itp.)
5. Spróbujmy teraz napisać (zaprojektować) jednolity interfejs do naszych zbiorów danych.
    * wyjaśnić pojęcie interfejsu (chcemy mieć łatwo wymienalny moduł implementujący zarządzanie wektorami)
6. ss

Co dalej?
Interfejs użytkownika.
Komunikacja sieciowa - sterowanie urządzeniami. Jakiś Raspberry PI może?

Notatki:
Zainstalowałem pod Windowsem:

* [](https://sourceforge.net/projects/vcxsrv/files/latest/download)
* sudo apt install qt5-default
* python3 -m pip install pyqt5
