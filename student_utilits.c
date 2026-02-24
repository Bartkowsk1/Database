#include <stdio.h>
#include <stdlib.h>
#include "student.h"

const char* pobierz_nazwe_kierunku(Kierunek k){
    switch (k){
        case INFORMATYKA:
            return "Informatyka";
            
        case MATEMATYKA:
            return "Matematyka";
            
        case FIZYKA:
            return "Fizyka";
            
        case ELEKTRONIKA:
            return "Elektronika";
            
        case ELEKTROTECHNIKA:
            return "Elektrotechnika";
            
        default:
            return "Inny";

    }
}

//using const for read-only purpose sec.0
void wypisz_studenta(const Student* s)
{
    // (*s).imie = s->imie
    printf("\nImie: %s \n", s->imie);
    printf("Nazwisko: %s \n", s->nazwisko);
    printf("Nr indeksu: %d \n", s->nr_indeksu);
    printf("Kierunek: %s \n", pobierz_nazwe_kierunku(s->kierunek));
    printf("Srednia ocen: %.3f\n", s->srednia);
    //pobierz nazwe kierunku
}

void dodaj_studenta(Student **baza, int *ilosc) {
    int nowy_rozmiar = *ilosc + 1; // Nowy rozmiar po dodaniu studenta
    Student *nowa_baza = realloc(*baza, nowy_rozmiar * sizeof(Student)); // Reallocujemy pamięć dla nowej bazy

    *baza = nowa_baza;
    (*ilosc)++; 
    printf("Podaj imię studenta: ");
    scanf("%s", (*baza)[*ilosc - 1].imie);
    printf("Podaj nazwisko studenta: ");
    scanf("%s", (*baza)[*ilosc - 1].nazwisko
    );
    printf("Podaj numer indeksu studenta: ");
    scanf("%i", &(*baza)[*ilosc - 1].nr_indeksu);
    int wybor_kierunku;
    printf("Wybierz kierunek studenta (0 - Informatyka, 1 - Matematyka, 2 - Fizyka, 3 - Elektronika, 4 - Elektrotechnika): ");
    scanf("%i", &wybor_kierunku);
    (*baza)[*ilosc - 1].kierunek = (Kierunek)wybor_kierunku; 
    printf("Podaj średnią ocen studenta: ");
    scanf("%f", &(*baza)[*ilosc - 1].srednia);

    printf("Student został dodany pomyślnie!\n");

}
void wypisz_cala_baze(const Student *baza, int rozmiar) {
    // Zabezpieczenie przed pierwszym testem bez danych w bazie 
    if (baza == NULL || rozmiar == 0) {
        printf("Baza jest obecnie pusta. Dodaj studentów, aby ich zobaczyć!\n");
        return;
    }

    for (int i = 0; i < rozmiar; i++) {
        printf("\nStudent %d z %d:", i + 1, rozmiar);
        // Używamy gotowej funkcji, przekazując adres konkretnego studenta z tablicy
        wypisz_studenta(&baza[i]);
    }
}


void zapisz_baze(const char *filename, Student *baza, int ilosc) {
    FILE *plik = fopen(filename, "wb"); // "wb" = write binary
    
    if (plik == NULL) {
        printf("Błąd: Nie udało się otworzyć pliku do zapisu!\n");
        return;
    }

    if (ilosc > 0) {
        fwrite(baza, sizeof(Student), ilosc, plik);
    }
    
    fclose(plik);
    printf("Baza danych została pomyślnie zapisana do pliku %s.\n", filename);
}

void wczytaj_baze(const char *filename, Student **baza, int *ilosc) {
    FILE *plik = fopen(filename, "rb"); // "rb" = read binary
    
    if (plik == NULL) {
        printf("Brak pliku bazy danych. Tworzę nową, pustą bazę.\n");
        *baza = NULL;
        *ilosc = 0;
        return;
    }

    fseek(plik, 0, SEEK_END);
    long rozmiar_pliku = ftell(plik);
    rewind(plik);

    *ilosc = rozmiar_pliku / sizeof(Student);

    if (*ilosc > 0) {
        *baza = malloc(*ilosc * sizeof(Student));
        fread(*baza, sizeof(Student), *ilosc, plik);
        printf("Pomyślnie wczytano %d studentów z bazy.\n", *ilosc);
    } else {
        *baza = NULL;
    }

    fclose(plik);
}


void zwolnij_pamiec(Student **baza, int *ilosc){
    free(*baza);
    *baza = NULL; // Dobrą praktyką jest ustawienie wskaźnika na NULL po zwolnieniu
    *ilosc = 0; // Resetujemy ilość studentów
}