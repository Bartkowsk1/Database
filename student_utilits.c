#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
    int podany_indeks;          //  Zmienne potrzebne do zbudowania funkcjonalności
    bool wynik_wyszukiwania;    //--^

    Student *nowa_baza = realloc(*baza, nowy_rozmiar * sizeof(Student)); // Reallocujemy pamięć dla nowej bazy
    //Poprawka realloca dodanie if  
    if(nowa_baza == NULL){
        printf("Błąd pamięci - brak wystarczajacego miejsca.");
    }else{
        *baza = nowa_baza;
    }
    (*ilosc)++; 
    printf("Podaj imię studenta: ");
    scanf("%49s", (*baza)[*ilosc - 1].imie); //%49s - ograniczenie aby nie przepełnić bufora 
    printf("Podaj nazwisko studenta: ");
    scanf("%49s", (*baza)[*ilosc - 1].nazwisko
    );

    //dodanie funkcjonalności uniemożliwiającej dodanie indeksu który jest już w bazie
    //za pomoca funkcji szukaj_studentaIndex
    do{
        printf("Podaj numer indeksu studenta: ");
        scanf("%i", &podany_indeks);
        
        wynik_wyszukiwania = szukaj_studentaIndex(*baza, *ilosc-1, podany_indeks);

        if(wynik_wyszukiwania){
            printf("Podany indeks jest juz przypisany dla innego studenta w bazie danych!!!\n");
        }

    }while(wynik_wyszukiwania);
    (*baza)[*ilosc - 1].nr_indeksu = podany_indeks;
    /*
        printf("Podaj numer indeksu studenta: ");
        scanf("%i", &(*baza)[*ilosc - 1].nr_indeksu);
    */

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

void wypisz_kierunek(const Student *baza, int rozmiar, Kierunek zKierunku) {
    // Zabezpieczenie przed pierwszym testem bez danych w bazie 
    if (baza == NULL || rozmiar == 0) {
        printf("Baza jest obecnie pusta. Dodaj studentów, aby ich zobaczyć!\n");
        return;
    }
    bool znaleziono = false;
    
    printf("Studenci z kierunku: %s  \n", pobierz_nazwe_kierunku(zKierunku));

    // petla z if statment
    for (int i = 0; i < rozmiar; i++) {
        if(baza[i].kierunek == zKierunku){
            wypisz_studenta(&baza[i]);
            znaleziono = true;
        }
    }
    if(!znaleziono){
        printf("Brak studentów na danym kierunku");
    }
}

void usun_ostatniegoStudenta(Student **baza, int *ilosc) {
    if (*ilosc > 0) {
        (*ilosc)--; // Zmniejszamy ilość studentów
        printf("Student %s %s został usunięty.\n", (*baza)[*ilosc].imie, (*baza)[*ilosc].nazwisko);
    } else {
        printf("Baza jest pusta! Nie ma kogo usunąć.\n");
    }
}

void usun_wybranegoStudenta(Student **baza, int *ilosc) {
    if (*ilosc == 0) {
        printf("Baza jest pusta! Nie ma kogo usunąć.\n");
        return;
    }

    int nr_indeksu;
    printf("Podaj numer indeksu studenta do usunięcia: ");
    scanf("%i", &nr_indeksu);

    int index_do_usuniecia = -1;
    for (int i = 0; i < *ilosc; i++) {
        if ((*baza)[i].nr_indeksu == nr_indeksu) {
            index_do_usuniecia = i;
            break;
        }
    }

    if (index_do_usuniecia != -1) {
        printf("Student %s %s został usunięty.\n", (*baza)[index_do_usuniecia].imie, (*baza)[index_do_usuniecia].nazwisko);
        for (int j = index_do_usuniecia; j < *ilosc - 1; j++) {
            (*baza)[j] = (*baza)[j + 1];
        }
        (*ilosc)--;
        *baza = realloc(*baza, (*ilosc) * sizeof(Student));
    } else {
        printf("Nie znaleziono studenta z numerem indeksu %d.\n", nr_indeksu);
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

void sortuj_bazeIndex(Student *baza, int rozmiar){
    for (int i = 0; i < rozmiar - 1; i++) {
        for (int j = 0; j < rozmiar - i - 1; j++) {
            if (baza[j].nr_indeksu > baza[j + 1].nr_indeksu) {
                Student temp = baza[j];
                baza[j] = baza[j + 1];
                baza[j + 1] = temp;
            }
        }
    }

}

void sortuj_bazeNazwisko(Student *baza, int rozmiar){
    for (int i = 0; i < rozmiar - 1; i++) {
        for (int j = 0; j < rozmiar - i - 1; j++) {
            if (strcmp(baza[j].nazwisko, baza[j + 1].nazwisko) > 0) {
                Student temp = baza[j];
                baza[j] = baza[j + 1];
                baza[j + 1] = temp;
            }
        }
    }

}

Student* szukaj_studentaIndex(Student *baza, int rozmiar, int nr_indeksu) {
    for (int i = 0; i < rozmiar; i++) {
        if (baza[i].nr_indeksu == nr_indeksu) {
            return &baza[i];
        }
    }
    return NULL;
}

Student* szukaj_studentaNazwisko(Student *baza, int rozmiar, char* nazwisko) {
    for (int i = 0; i < rozmiar; i++) {
        if (strcmp(baza[i].nazwisko, nazwisko) == 0) {
            return &baza[i];
        }
    }
    return NULL;
}
//
/*
to do:
    1. Poprawka wyszukiwania przez nazwisko
    2. Obsluga w przypadku nie znalezienia studenta o podanym indeksie/nazwisku -> ponowne wprowadzenie

    Opcjonalnie:
    1. Dodanie wyjścia z edytora po wyborze studenta z zachowaniem poprzednich danych (mimo edycji)
    2.  Dodanie wyjścia w momencie przeszukiwania studenta do edycji przez nazwisko
*/
void edytuj_studenta(Student *baza, int rozmiar){

    int wybor_Wyszkiwania;
    Student *wyszukany_Student = NULL;
    int index;


    if (baza == NULL || rozmiar == 0) {
        printf("\nBrak danych!!! Wprowadz pierwsze dane!\n");
        return; 
    }
    printf("Podan jak chcesz znaleźć studenta do edycji: \n");
    printf("1. Po numerze indeksu\n");
    printf("2. Po nazwisku \n");
    printf("0. Wyjdź\n");
    do{
        printf("Wybór: ");
        scanf(" %i", &wybor_Wyszkiwania);

        if(wybor_Wyszkiwania == 1){
            printf("Podaj nr indeksu: ");
            scanf(" %i", &index);
            getchar();
            wyszukany_Student = szukaj_studentaIndex(baza, rozmiar, index);
        }
        else if(wybor_Wyszkiwania == 2){
            char nazwisko[MAX_STR];
            printf("Podaj nazwisko: ");
            scanf(" %s", nazwisko);
            getchar();

            int ile_stud = 0;
            Student *pkt_startu = baza;
            int rozmiar_do_konca = rozmiar;

            printf("Znalezieni studenci o takim nazwisku: \n");

            //Petla while szukajaca wszystkich studentow z uzyciem funckji szukaj_studentaNazwisko
            while(rozmiar_do_konca > 0){
                Student *tymczasowy =  szukaj_studentaNazwisko(pkt_startu, rozmiar_do_konca, nazwisko);

                //
                if(tymczasowy == NULL){
                    break;
                }

                wypisz_studenta(tymczasowy);
                ile_stud++;

                /*
                Szukamy adres studenta i wykonujemy przejscie tak, aby szukać w następnej
                iteracji bez uwzglednienia znalezionego w (aktualnej iteracji) studenta
                */
                int pkt_przejscia = (tymczasowy - pkt_startu) + 1; //adres tymczasoewgo - pkt startu bazy

                pkt_startu = pkt_startu + pkt_przejscia; //zmieniony pkt startu tak aby zaczac od adresu następnego od znalezionego

            }
            //Sprawdzenie czy w ogole istnieje jakikolwiek student z wprowadzonym nazwikiem
            if(ile_stud == 0){
                printf("\nNie znaleziono studenta z takim nazwiskiem\n");
                return ;
            }
            //Obsluga po znalezieu studentow (jednego lub wielu)
            else if(ile_stud >= 1){
                printf("\nZnaleziono studenta/ów z takim nazwiskiem !!!\nKtórego chcesz zmodyfikować?\n");              
                printf("Podaj nr indeksu z listy: ");
                scanf(" %i", &index);
                getchar();
                wyszukany_Student = szukaj_studentaIndex(baza, rozmiar, index);
            }

        }
        else if(wybor_Wyszkiwania == 0){
            return ;
        }
        else{
            printf("Błąd! Wprowadź poprawny wybór jeszcze raz ");
        }
    }while(wybor_Wyszkiwania != 1 && wybor_Wyszkiwania != 2);
    //Wypisanie studenta
    printf("Student którego dane będą edytowane: \n");
    printf("-------------------------------");
    wypisz_studenta(wyszukany_Student);
    printf("-------------------------------\n");

    
    //Pola edycji -> po znalezionu konkretnego stidenta bedziemy pytac o to co chcemy edytowac
    //Korzystamy z zmiennej, która była używana do wyboru w jaki sposob mamy znalezc studenta do edycji
    wybor_Wyszkiwania = 0;
    printf("Wybierz co chcesz edytować\n");
    printf("1. Średnia ocen \n");
    printf("2. Kierunek \n");
    do{
        printf("Wybór: ");
        scanf(" %i", &wybor_Wyszkiwania);
        getchar();

        if(wybor_Wyszkiwania == 1){
            //Zmiana średniej
            printf("Podaj nowa średnią :" );
            //dwa miejsca po przecinku!!!
            scanf(" %f", &wyszukany_Student->srednia); // <=> wyszukany_Student.srednia
        }
        else if(wybor_Wyszkiwania == 2){
            printf("Podaj nowy kierunek studenta: ");
        
        }
        else{
            printf("Błąd! Wprowadź poprawny wybór jeszcze raz ");
        }
    }while(wybor_Wyszkiwania != 1 && wybor_Wyszkiwania != 2);

    printf("\n\nStudent po edycji dancyh: \n");
    printf("-------------------------------");
    wypisz_studenta(wyszukany_Student);
    printf("-------------------------------\n");


}