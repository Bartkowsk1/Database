//Jak cos to ja komentarze pół english pół polish :D
#ifndef STUDENT_H
#define STUDENT_H

/* --- CONST --- */

// Max length of string
#define MAX_STR 50 

//Max number of student (array)
#define MAX_STUDENTS 100 


/* --- DATA TYPE --- */

//Enum type  - used in struct below instead of numbers
//Fields of study
typedef enum {
    INFORMATYKA,
    MATEMATYKA,
    FIZYKA,
    ELEKTRONIKA,
    ELEKTROTECHNIKA,
    INNY
} Kierunek;

// Struct of student 
typedef struct {
    char imie[MAX_STR];
    char nazwisko[MAX_STR];
    int nr_indeksu;
    Kierunek kierunek;
    float srednia;
} Student;


/* --- DEKLARACJE FUNKCJI (PROTOTYPY) --- */
//tutaj będziemy wpisywać funkcje

#endif // STUDENT_H