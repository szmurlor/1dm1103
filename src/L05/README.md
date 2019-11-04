WORK IN PROGRESS!

:-) 

Wskaźniki.

```c
#include <stdio.h>

int main()
{
    int i,j;
    int *p;   /* a pointer to an integer */
    p = &i;
    *p=5;
    j=i;
    printf("%d %d %d\n", i, j, *p);
    return 0;
}
```

1. Ułożenie w pamięci
2. Wartości

A teraz zagadka. Co to jest?

```c
#include <stdio.h>

int main()
{
    int i,j;
    int *p;   /* a pointer to an integer */
    int **pp;
    p = &i;
    pp = &p;
    *p=5;
    j=i;
    printf("%d %d %d %d\n", i, j, *p, **pp);
    printf("%p %p %p\n", p, pp, *pp);

    return 0;
}
```

A teraz zagadka. Co to jest?

```c
#include <stdio.h>

int main()
{
    int t[5] = {1, -2, 4 , 5, 6};
    int *p = t;   /* a pointer to an integer */
    printf("%d %d %d %d %d\n", t[0], t[1], t[2], t[0+3], *p, *(p+4));
    printf("%p %p %p %p\n", &t[0], t, p, *(p+4));

    return 0;
}
```

Użycie wskaźników przy przekazywaniu wartości do funkcji i zwracaniu wyników.

- blok kodu - zakres dostępu do zmiennej wewnątrz bloku.

```c
#include <stdio.h>

int wypisz10razy_ptr(int *a) {
  int i;
  for (i = 0; i < 10; i++) {
    /* printf("a = %d\n", (*a++) ); A co sie stanie? */
    printf("a = %d\n", (*a)++);
  }
}

int wypisz10razy(int a) {
  int i;
  for (i = 0; i < 10; i++) {
    printf("a = %d\n", a++);
  }
}

int main() {
  int a = 5;
  int i;
  for (i = 0; i < 10; i++) {
    printf("a = %d\n", a++);
  }

  printf("Po wyjściu z pętli a=%d\n", a);

  wypisz10razy(a);
  printf("Po powrocie z funkcji, która otrzymała kopię wartości a: a=%d\n", a);

  wypisz10razy_ptr(&a);
  printf("Po powrocie z funkcji, która otrzymała wskaźnik do zmiennej lokalnej a: a=%d\n", a);

  return 0;
}
```

Struktury. Jeszcze raz struktury.

```c
#include <stdio.h>
#include <string.h>

struct college_detail
{
    int college_id;
    char college_name[50];
};

struct student_detail
{
    int id;
    char name[20];
    float percentage;

    // zagnieżdżona struktra w strukturze
    struct college_detail clg_data;
}stu_data, *stu_data_ptr;

int main()
{
    struct student_detail sd = {1, "Raju", 90.5, 71145,
                                    "Anna University"};
    sd_ptr = &sd;

    printf(" Id is: %d \n", sd_ptr->id);
    printf(" Name is: %s \n", sd_ptr->name);
    printf(" Percentage is: %f \n\n", sd_ptr->percentage);

    printf(" College Id is: %d \n", sd_ptr->clg_data.college_id);
    printf(" College Name is: %s \n", sd_ptr->clg_data.college_name);

    return 0;
}
```

```c
#include <stdio.h>
#include <string.h>

struct student
{
       int id1;
       int id2;
       char a;
       char b;
       float percentage;
};

int main()
{
    int i;
    struct student record1 = {1, 2, 'A', 'B', 90.5};

    printf("Rozmiar struktury w bajtach : %d\n", sizeof(record1));

    printf("\nAdres id1        = %u", &record1.id1 );
    printf("\nAdres id2        = %u", &record1.id2 );
    printf("\nAdres a          = %u", &record1.a );
    printf("\nAdres b          = %u", &record1.b );
    printf("\nAdres percentage = %u",&record1.percentage);

    return 0;
}
```

Wczytajmy strukturę danych o studentach z pliku CSV.

`strtok`
