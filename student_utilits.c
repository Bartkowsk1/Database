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
            return "inny";

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
