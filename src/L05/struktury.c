#include <stdio.h>
#include <string.h>

struct College {
    int id;
    char name[51];
};

struct Student {
    int id;
    char name[51];
    float percent;

    struct College college;
};

void wypisz_studenta(struct Student s) {
    printf("%d\n", s.id);
    printf("%s\n", s.name);
    printf("%.1f\n", s.percent);
    printf("college.id = %d\n", s.college.id);
    printf("college.name = %s\n", s.college.name);
}

int main(int argc, char *argv[]) {
    struct Student najlepszy;
    najlepszy.name[0] = 'A';
    najlepszy.name[1] = 'l';
    najlepszy.name[2] = 'a';
    /*najlepszy.name[3] = 0;*/
    printf("%s\n", najlepszy.name);
    najlepszy.name[0] = 'E';
    najlepszy.name[1] = 'd';
    najlepszy.name[2] = 0;
    printf("%s\n", najlepszy.name);

    /* strcpy(&najlepszy.name[0], "Grzegorz Brzeczyszczykiewicz"); */
    strcpy(najlepszy.name, "Grzegorz Brzeczyszczykiewicz");
    najlepszy.id = 999;
    najlepszy.percent = 98.5;
    najlepszy.college.id = 11;
    /* najlepszy.college.name = "ZONK"; */
    strcpy(najlepszy.college.name, "ZONK");

    wypisz_studenta(najlepszy);
    
    return 0;
}