To jest *operator* warunkowego podstawienia! Jego idea działania jest taka, że wynik tego operatora zostanie podstawiony jako wartość do zmiennej po lewej stronie znaku `=`.

```c
double v = (n > 3) ? 1 : 0;
```

Alternatywnie powyższy kod możemy po prostu zapisać fragmentem kodu:

```c
if (n > 3) {
  v = 1;
} else {
  v = 0;
}
```

W języku C wewnątrz wyrażeń definiujących warunki można używać operatora podstawienia. Bardzo często spotykamy sie z kontrukcją typu:

```c
if ( (fout = fopen("plik", "r")) == NULL) {
	printf("Komunikat o błędzie...\n");
	exit(-1);
}
```

W powyższym kodzie w linicje ze słowem kluczowym `if` wykonujemy dwie operacje jednocześnie:

1. Przypisujemy wartość zwracaną przez funkcję fopen() do zmiennej `fout`.
2. Następnie sprawdzamy czy wartość zmiennej fout (po podstawieniu) jest równa NULL <- wynik tej operacji logicznej będzie przekazany jako warunek `if`.

Uwaga! O ile poniższy kod z punktu widzenia składni języka C jest całkowicie poprawny o tyle jest on niskeij jakości stylistycznej.

```c
(n > 3 ? v = 1 : v = 0);
```

Wynika to z tego, że operator warunkowego przypisania tam gdzie powinna być wyłącznie obliczona wartość do przypisania, właściwie tam go dokonuje. Tam gdzie jest `v=1` powinno być jedynie obliczenie wartości do podstawienia a nie samo podstawienie. Taka konstrukcja kodu zaprzecza nateuralnej idei tego operatora, który powinien być poprawnie stylistyzcnie sformułowany w następujący sposób:

```c
v = (n > 3 ? 1 : 0);
```
