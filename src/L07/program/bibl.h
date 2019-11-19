
struct Ocena {
    float ocena;
    int ects;
    char przedmiot[50];
    char kto_wystawil[50];
};

struct Student {
    char imie[50];
    char nazwisko[50];
    char nr_albumu[10];

    float srednia;

    int liczba_ocen;
    struct Ocena oceny[20];
};

int wczytaj(char *fname, struct Student studenci[]);
void wypisz_na_ekran(struct Student s[], int n);
void oblicz_srednie(struct Student s[], int n);