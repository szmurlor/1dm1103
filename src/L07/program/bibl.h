
#define ROSNACO 1
#define MALEJACO -1

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
void wypisz_na_ekran_srednie(struct Student s[], int n);
void oblicz_srednie(struct Student s[], int n);
int sortuj_babelkowo(struct Student s[], int n);
int sortuj_babelkowo_rosnaco(struct Student s[], int n);
int sortuj_babelkowo_malejaco(struct Student s[], int n);

/* 
    kierunek = 1 oznacza sortowanie rosnaco
    kierunek = -1 oznacza sortowanie malejaco
 */
int sortuj_babelkowo_kierunek(struct Student s[], int n, int kierunek);


int sortuj_wybieranie_kierunek(struct Student s[], int n, int kierunek);
