#include <stdio.h>

void zwieksz_o_jeden(int a) {
    a++;
    printf("Co sie dzieje? %d\n",a);
}

void zwieksz_o_jeden_dobrze(int *a) {
    (*a)++;
    printf("Co sie dzieje? %d\n", *a);
}

int main() {
    int a = 6;
    zwieksz_o_jeden(a);
    printf("a = %d\n", a);
    zwieksz_o_jeden_dobrze(&a);
    printf("a = %d\n", a);
}