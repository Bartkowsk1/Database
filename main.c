#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "student.h"


int main() {

    SetConsoleOutputCP(CP_UTF8);

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

    zwolnij_pamiec(&baza, &rozmiar);
    return 0;
}

