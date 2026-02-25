#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("3. Usuń studenta\n");
        printf("4. Zapisz zmiany do pliku\n");
        printf("5. Posortuj studentów.\n");
        printf("6. Znajdź studenta.\n");
        printf("7. Wyjdź\n");
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
                    printf("Czy chcesz usunąć ostatniego studenta (1) czy wybranego (2)? ");
                    int wyborUsuwania;
                    scanf("%i", &wyborUsuwania);
                    if (wyborUsuwania == 1) {
                        usun_ostatniegoStudenta(&baza, &rozmiar);
                    } else if (wyborUsuwania == 2) {
                        usun_wybranegoStudenta(&baza, &rozmiar);
                    } else {
                        printf("Nieprawidłowy wybór usuwania.\n");
                    }
                } else {
                    printf("\nBaza jest pusta! Nie ma kogo usunąć.\n");
                } 
                
                break;


            case 4:
                zapisz_baze("baza.dat", baza, rozmiar);
                break;

            case 5:
                printf("Wybierz czy chcesz sortować po indeksie (1) czy nazwisku (2): ");
                int wyborSortowania;
                scanf("%i", &wyborSortowania);
                if (wyborSortowania == 1) {
                    sortuj_bazeIndex(baza, rozmiar);
                    printf("Studenci zostali posortowani po indeksie.\n");
                } else if (wyborSortowania == 2) {
                    sortuj_bazeNazwisko(baza, rozmiar);
                    printf("Studenci zostali posortowani po nazwisku.\n");
                } else {
                    printf("Nieprawidłowy wybór sortowania.\n");
                }
                break;


            case 6:
                printf("Wybierz czy chcesz znaleźć studenta po indeksie (1) czy nazwisku (2): ");
                int wyborZnajdowania;
                scanf("%i", &wyborZnajdowania);
                if (wyborZnajdowania == 1) {
                    int indexStudenta;
                    printf("Podaj numer indeksu do znalezienia: ");
                    scanf("%i", &indexStudenta);
                    Student *znajdzStudenta = szukaj_studentaIndex(baza, rozmiar, indexStudenta);
                    if (znajdzStudenta != NULL) {
                        printf("Znaleziono studenta:\n");
                        wypisz_studenta(znajdzStudenta);
                    } else {
                        printf("Nie znaleziono studenta o podanym numerze indeksu.\n");
                    }
                } else if (wyborZnajdowania == 2) {
                    char nazwiskoStudenta[MAX_STR];
                    printf("Podaj nazwisko do znalezienia: ");
                    scanf("%s", nazwiskoStudenta);
                    Student *znajdzStudenta = szukaj_studentaNazwisko(baza, rozmiar, nazwiskoStudenta);
                    if (znajdzStudenta != NULL) {
                        printf("Znaleziono studenta:\n");
                        wypisz_studenta(znajdzStudenta);
                    } else {
                        printf("Nie znaleziono studenta o podanym nazwisku.\n");
                    }
                } else {
                    printf("Nieprawidłowy wybór wyszukiwania.\n");
                }
                break;


            
            case 7:
                printf("\nBaza została zamknięta.\n");
                zapisz_baze("baza.dat", baza, rozmiar);
                break;


      
            default:
                printf("Nieprawidłowy wybór, spróbuj ponownie.\n");
                break;
        }
    } while (wybor != 7);

    // Zwalnianie pamieci na koncu pliku
    zwolnij_pamiec(&baza, &rozmiar);
    return 0;
}