#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;

    printf("Witaj świecie podałeś %d argumentów %%!\n", argc);

    /* argc = 0; */
    for (i=0; i<argc; i++) {
        printf("[%d]: %s\n", i, argv[i]);
        /* i = i + 1; */
        /* i += 1; */
        /* i++; */
    }

    return 0;
}