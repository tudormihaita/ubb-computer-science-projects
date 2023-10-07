#pragma once
#include "cheltuiala.h"

/*
* Valideaza o cheltuiala data prin verficarea atributelor sale: ziua sa fie un numar intreg intre 1 si 31, suma un numar real > 0, tipul unul din lista de tipuri data
* input/pre: cheltuiala, erori(string) - va salva mesajele de eroare corespunzatoare atributelor invalide
* return/post: string-ul de erori va fi modificat corespunzator atributelor invalide, sau va ramane vid daca cheltuiala data este valida
*/
void valideaza_cheltuiala(Cheltuiala*, char*);


/*
* Verifica daca o zi data pentru o cheltuiala este valida(numar intreg intre 1 si 31)
* input/pre: zi(int)
* return/post: 0 daca ziua este valida
*              -1 altfel
*/
int valideaza_zi(int);


/*
* Verifica daca o suma data pentru o cheltuiala este valida(numar real > 0)
* input/pre: suma(double)
* return/post: 0 daca suma este valida
*              -2 altfel
*/
int valideaza_suma(double);


/*
* Verifica daca un tip dat pentru o cheltuiala este valid(face parte din lista de tipuri date)
* input/pre: tip(char*)
* return/post: 0 daca tipul este valid
*              -3 altfel
*/
int valideaza_tip(char*);