#include <stdio.h>

int main() {
    int i = 3, j = 78;
    int *p;
    int **pp;
    p = &i;
    pp = &p;
    *p = 9;
    j = i;
    printf("%d %d %d %d\n", i, j, *p, **pp);
    printf("%p %p %p %p %p\n", &i, &j, p, *pp, pp);


    return 0;
}