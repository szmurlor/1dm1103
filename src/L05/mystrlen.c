#include <stdio.h>

/*int mystrlen(char *s) {*/
int mystrlen1(char s[]) {
    int i = 0;
    while (s[i] != 0)
        i++;
    return i;
}

int mystrlen2(char s[]) {
    int i = 0;
    while (s[i++] != 0);
    return i-1;
}

int mystrlen_rekur(char s[]) {
    if (*s == 0) {
        printf("Jestem w if.\n");
        return 0;
    } else {
        printf("Jestem w else %p.\n", s);
        return 1 + mystrlen_rekur( ++s );
    }
}

int mystrlen_rekur_1(char s[]) {
    if (*s == 0)
        return 0;
    else
        return 1 + mystrlen_rekur( ++s );
}

int mystrlen_rekur_2(char s[]) {
    return *s == 0 ? 0 : 1 + mystrlen_rekur( ++s );
}

int main(int argc, char *argv[]) {
    
    printf("1: Pierwszy argument ma dlugosc: %d\n", mystrlen1(argv[1]));
    printf("2: Pierwszy argument ma dlugosc: %d\n", mystrlen2(argv[1]));
    printf("Rekur: Pierwszy argument ma dlugosc: %d\n", mystrlen_rekur(argv[1]));

    printf("Druga literka drugiegop napisu: %c\n", argv[2][1]);
    return 0;
}