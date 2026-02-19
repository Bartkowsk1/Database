#include <stdio.h>
#include <stdlib.h>
#include "student.h"


int main() {

    Student *baza = NULL; // Początkowo brak studentów, więc NULL
    int rozmiar = 0;
    int wybor = 0;

    wczytaj_baze("bazaStudentow.dat", &baza, &rozmiar); // Wczytujemy bazę studentów z pliku

        
    do
    {
    printf("\n==== SYSTEM BAZY STUDENTÓW ====\n");    
    printf("Aktualna liczba studentów: %i\n", rozmiar);
    printf("Co chcesz zrobić?\n");
    printf("1. Dodaj studenta 2. Usuń studenta 3. Zapisz zmiany do pliku 4. Wyjdź\n");
    scanf("%i", &wybor);

    switch (wybor)
    {
    case 1:
        dodaj_studenta(&baza, &rozmiar);
        break;
    case 2:
            if (rozmiar > 0) {
                printf("\nUsuwanie ostatniego studenta...\n");
                
                // Przekazujemy ADRES (&) studenta do funkcji kolegi
                wypisz_studenta(&baza[rozmiar - 1]); 
                
                // Zmniejszamy licznik (Logiczne usunięcie)
                rozmiar--; 
                printf("Student zostal usuniety.\n");
            } else {
                printf("\nBaza jest pusta! Nie ma kogo usunac.\n");
            }
            break;
    case 3:
        zapisz_baze("baza.dat", baza, rozmiar);
        break;
    case 4:
        zwolnij_pamiec(&baza, &rozmiar);
        break;    
    default:
        printf("Nieprawidłowy wybór, spróbuj ponownie.\n");
        break;
    }
        } while (wybor != 4);










    return 0;
    zwolnij_pamiec(&baza, &rozmiar);
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