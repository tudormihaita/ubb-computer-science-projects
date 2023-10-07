#pragma once
#include "repository.h"
#include "cheltuiala.h"
#include <stdbool.h>

typedef int (*CompareFct)(TElem, TElem, bool);
typedef int (*FilterFct)(TElem, void*);



typedef struct {
	Vector* cheltuieli;
	Vector* undo_list;
}Buget;


/*
* Creeaza un buget care contine o lista de cheltuieli initial vida, si cu o capacitate maxima prestabilita ce poate fi modificata
* Initilizeaza si o lista generica de undo operatii, care va contine deepCopy-uri la listele inaintea modificarilor efectuate
*/
Buget create_buget();


/*
* Adauga o cheltuiala in lista/containerul de cheltuieli
* Verifica daca datele de intrare sunt valide si in caz afirmativ, adauga cheltuiala noua creata, altfel afiseaza mesajele de eroare corespunzatoare
* input/pre: vector, zi(int), suma(float), tip(char*), erori(char* - string-ul in care se vor retine erorile returnate la validare)
* return/post: 0 daca cheltuiala a fost valida si adaugata cu succes
*			   -1 daca cheltuiala a fost invalida, setand string-ul de erori corespunzator atributelor invalide
*/
int add_cheltuiala(Buget*, int, double, char*, char*);


/*
* Cauta si returneaza o cheltuiala din lista cu id-ul dat
* input/pre: vector, id(int) - pozitie valida din vector
* return/post: un pointer la cheltuiala de pe pozitia id in cazul in care exista
*			   NULL, in cazul in care pozitia data drept id nu exista in vectorul curent
*/
Cheltuiala* find_cheltuiala(Buget*, int);


/*
* Sterge o cheltuiala din lista de cheltuieli
* Verifica daca pozitia data exista in lista, iar in caz afirmativ, elimina cheltuiala din container
* input/pre: vector, id(int) - pozitia in lista a cheltuielii date
* return/post: 0 daca cheltuiala a fost stearsa cu succes
*			   -1 daca pozitia data este invalida
*/
int delete_cheltuiala(Buget*, int);


/*
* Modifica o cheltuiala deja existenta in lista
* Valideaza datele noi de intrare cu care urmeaza sa fie modificata cheltuiala, verifica daca pozitia data este una valida si schimba atributele cheltuielii
* input/pre: vector, id(int - pozitia in lista), zi(int), suma(double), tip(char*), erori(char* - string de erori de validare)
* return/post: 0 daca datele furnizate sunt valide si cheltuiala a fost modificata
*			   -1 daca datele pentru modificare atributelor sunt invalide
*			   -2 daca pozitia data este una invalida in lista curenta
*/
int modify_cheltuiala(Buget*, int, int, double, char*, char*);


/*
* Returneaza numarul de cheltuieli din lista
* input/pre: vector
* return/post: lungimea listei(int)
*/
int get_lungime(Vector*);


/*
* Preia toate cheltuielile curente existente intr-o lista si o returneaza
* input/pre: vector
* return/post: vector, contine toate cheltuielile existente pana in momentul actual
*/
Vector* get_all_cheltuieli(Buget*);


/*
* Verifica daca cheltuiala data are ziua egala cu cea data pentru aplicarea filtrului in functie de zi
* input/pre: cheltuiala, zi(data printr-un pointer void*)
* return/post: 1 daca zilele sunt egale
			   0 in caz contrar
*/
int filtru_zi(Cheltuiala*, void*);


/*
* Verifica daca o cheltuiala data are suma mai mica sau egala cu suma minima data pentru aplicarea filtrului in functie de suma
* input/pre: cheltuiala, suma(data printr-un pointer void*)
* return/post: 1 daca suma cheltuielii curente este mai mica sau egala cu suma minima data
			   0 in caz contrar
*/
int filtru_suma_minima(Cheltuiala*, void*);


/*
* Verifica daca o cheltuiala data are suma mai mare decat suma maxima data pentru aplicarea filtrului in functie de suma
* input/pre: cheltuiala, suma(data printr-un pointer void*)
* return/post: 1 daca suma cheltuielii curente este mai mare decat suma maxima data
			   0 in caz contrar
*/
int filtru_suma_maxima(Cheltuiala*, void*);


/*
* Verifica daca cheltuiala data are tipul identic cu cel dat pentru aplicarea filtrului in functie de tip
* input/pre: cheltuiala, tip(dat printr-un pointer void*)
* return/post: 1 daca tipurile sunt identice
			   0 in caz contrar
*/
int filtru_tip(Cheltuiala*, void*);


/*
* Filtreaza cheltuielile din lista curenta dupa o anumita proprietate(zi, suma, tip) si returneaza lista de cheltuieli filtrata
* input/pre: vector, filtru(string convertit corespunzator proprietatii verificate), *proprietate - pointer la functia pentru stabilirea conditiei de filtrare
* return/post: vector, lista filtrata in functie de proprietatea data
*/
Vector* filter_cheltuieli_proprietate(Buget*, void*, FilterFct);


/*
* Compara valorile sumelor a 2 cheltuieli in functie de criteriul de sortare dat, crescator sau descrescator
* input/pre: 2 cheltuieli, reversed(bool) - criteriul de sortare, crescator/descrescator
* return/post: 1 daca cheltuielile sunt deja sortate corespunzator in functie de suma
			   0 in caz contrar
*/
int compare_suma(Cheltuiala*, Cheltuiala*, bool);


/*
* Compara tipurile a 2 cheltuieli in functie de criteriul de sortare dat, crescator sau descrescator
* input/pre: 2 cheltuieli, reversed(bool) - criteriul de sortare, crescator/descrescator
* return/post: 1 daca cheltuielile sunt deja sortate corespunzator in functie de tip
			   0 in caz contrar
*/
int compare_tip(Cheltuiala*, Cheltuiala*, bool);


/*
* Sorteaza cheltuielile curente din lista crescator sau descrescator, in functie de o proprietate data(dupa suma sau dupa tip)
* input/pre: vector, reversed(bool) - criteriul de sortare crescator/descrescator , *compare - pointer la functia de comparare a proprietatilor date pentru sortare
* return/post: vector - lista cu cheltuielile sortate dupa criteriul si proprietatea data
*/
Vector* sort_cheltuieli(Vector*, bool, CompareFct);

/*
* Restaureaza lista de cheltuieli la starea precedenta, inainte de ultima operatie efectuata
* input/pre - buget, ce contine o lista de cheltuieli si o lista de undo, initial vida, in care se vor adauga listele de restaurat in functie de operatiile efectuate
* return/post : 1 - daca operatia de undo a fost efectuata cu succes si efectul unei operatii de adaugare/stergere/modificare a fost inversat
*				0 - daca nu se mai pot efectua astfel de operatii/ s-a ajuns la starea initiala a listei de cheltuieli(lista vida)
*/
int undo(Buget*);


/*
* Elibereaza memoria alocata pentru buget
*/
void destroy_buget(Buget* buget);

