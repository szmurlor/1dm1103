#include <stdio.h>

void print_rekur(double v[], int poz, int max) {

	if (poz >= max)
		return;
	else {
		printf("v[%d] = %lf\n", poz, v[poz]);
		print_rekur(v, ++poz, max);
	}
}

double suma_rekur(double v[], int poz, int max) {
/* return (poz >= max) ? 0 : v[poz] + suma_rekur(v, ++poz, max); */
	if (poz >= max)
		return 0;
	else 
		return v[poz] + suma_rekur(v, ++poz, max);
}

int main(int argc, char**argv) {
	double v[5] = {1,2,3,4,5};
	print_rekur(v,0,5);
	printf("Wynik sumy obliczony rekurencyjnie to: %lf\n", suma_rekur(v,0,5));
	return 0;
}
