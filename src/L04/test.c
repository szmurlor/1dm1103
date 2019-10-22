#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
	char * napis = "Ala ma kota";
	int i;

	for (i=0; i<strlen(napis);i++)
		printf("[%d] = %d\n", i, napis[i]);

	for (i=0;i<128;i++) {
		printf("[%d] = %c\n", i, i);
	}
	return 0;
}
