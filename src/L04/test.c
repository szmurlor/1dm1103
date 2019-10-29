#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	/* char * napis = "Ala ma kota"; */
	char napis[] = "Ala ma kota";
	int i;

	for (i=0; i<strlen(napis);i++)
		/* printf("[%d] = %d\n", i, napis[i]); */
		printf("[%d] = %c\n", i, napis[i]);
/*
	printf("Napis: %s\n", napis);
	printf("Napis: %s\n", napis[0]);
	printf("Napis: %c\n", napis[0]);
	printf("Napis: %s\n", argv);
	printf("Napis: %s\n", argv[0]);
*/

/*
	for (i=0;i<128;i++) {
		printf("[%d] = %c\n", i, i);
	}
*/
	

	return 0;
}
