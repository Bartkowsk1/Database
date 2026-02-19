#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "student.h"

int main() {
    // Dodanie utf08
    SetConsoleOutputCP(CP_UTF8);

    Student *baza = NULL;
    int rozmiar = 0;
    int wybor = 0;

        // Wczytanie bazy (bo na niej pracujemy)
    wczytaj_baze("baza.dat", &baza, &rozmiar);

    do {
        printf("\n==== SYSTEM BAZY STUDENTÓW ====\n");    
        printf("Aktualna liczba studentów: %i\n", rozmiar);
        printf("Co chcesz zrobić?\n");
        printf("1. Dodaj studenta\n");
        printf("2. Wypisz wszystkich studentów\n"); 
        printf("3. Usuń ostatniego studenta\n");
        printf("4. Zapisz zmiany do pliku\n");
        printf("5. Wyjdź\n");
        printf("Twój wybór: ");
        
        scanf("%i", &wybor);
        
        // Usuwanie znaku przejscia do nowej lini 
        while(getchar() != '\n'); 

        switch (wybor) {
            case 1:
                dodaj_studenta(&baza, &rozmiar);
                break;
            case 2:
                printf("\n--- LISTA STUDENTÓW ---\n");
                wypisz_cala_baze(baza, rozmiar);
                break;
            case 3:
                if (rozmiar > 0) {
                    printf("\nUsuwanie ostatniego studenta...\n");
                    wypisz_studenta(&baza[rozmiar - 1]); 
                    rozmiar--; 
                    printf("Student został usunięty.\n");
                } else {
                    printf("\nBaza jest pusta! Nie ma kogo usunąć.\n");
                }
                break;
            case 4:
                zapisz_baze("baza.dat", baza, rozmiar);
                break;
            case 5:
                printf("\nZapisywanie przed wyjściem...\n");
                zapisz_baze("baza.dat", baza, rozmiar);
                break;    
            default:
                printf("Nieprawidłowy wybór, spróbuj ponownie.\n");
                break;
        }
    } while (wybor != 5);

    // Zwalnianie pamieci na koncu pliku
    zwolnij_pamiec(&baza, &rozmiar);
    return 0;
}