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
   
    ("Co chcesz zrobić?\n");
    printf("1. Dodaj studenta 2. Usuń studenta 3. Zapisz zmiany 4. Wyjdź\n");
    scanf("%i", &wybor);

    switch (wybor)
    {
    case 1:
        dodaj_studenta(&baza, &rozmiar);
        break;
    case 2:
        wypisz_studenta(baza[rozmiar - 1]); //funckja wzięta z student_utilits.c do wypisania ostatniego studenta przed usunięciem
        rozmiar--; //zmniejszamy rozmiar, ale nie zwalniamy pamięci, bo możemy dodać kolejnego studenta
        break;    
    case 3:
        zapisz_baze("baza.dat", baza, rozmiar);
        break;
    case 4:
        zwolnij_pamiec(&baza, &rozmiar);
        break;    
    default:
        break;
    }
        } while (wybor != 4);










    return 0;
    zwolnij_pamiec(&baza, &rozmiar);
}

void dodaj_studenta(Student **baza, int *ilosc) {


}
void zapisz_baze(const char *filename, Student *baza, int ilosc) {}
void wczytaj_baze(const char *filename, Student **baza, int *ilosc) {}
void zwolnij_pamiec(Student **baza, int *ilosc){
    free(*baza);
    *baza = NULL; // Dobrą praktyką jest ustawienie wskaźnika na NULL po zwolnieniu
    *ilosc = 0; // Resetujemy ilość studentów
}