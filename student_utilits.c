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

    *baza = nowa_baza; // Aktualizujemy wskaźnik do bazy
    (*ilosc)++; // Zwiększamy ilość studentów 
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
    (*baza)[*ilosc - 1].kierunek = (Kierunek)wybor_kierunku; // Rzutujemy na typ Kierunek
    printf("Podaj średnią ocen studenta: ");
    scanf("%f", &(*baza)[*ilosc - 1].srednia);

    printf("Student został dodany pomyślnie!\n");

}
void zapisz_baze(const char *filename, Student *baza, int ilosc) {}
void wczytaj_baze(const char *filename, Student **baza, int *ilosc) {}
void zwolnij_pamiec(Student **baza, int *ilosc){
    free(*baza);
    *baza = NULL; // Dobrą praktyką jest ustawienie wskaźnika na NULL po zwolnieniu
    *ilosc = 0; // Resetujemy ilość studentów
}