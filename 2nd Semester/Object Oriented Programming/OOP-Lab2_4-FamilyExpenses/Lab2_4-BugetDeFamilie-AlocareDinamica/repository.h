#pragma once
#include "cheltuiala.h"

//typedef Cheltuiala TElem;
typedef void* TElem;

typedef void (*DestroyFct)(TElem);
typedef TElem (*CopyFct)(TElem);


typedef struct {
	TElem* elems;
	int size;
	int capacity;
	DestroyFct dfnc;
}Vector;


/*
* Creeaza si initializeaza un vector dinamic initial vid
*/
Vector* create_empty(DestroyFct);


/*
* Creeaza un deepCopy la vectorul dat, copiind elementele utilizand functia de copiere corespunzatoare tipului de data
*/
Vector* copy_vector(Vector*, CopyFct);


/*
* Redimensioneaza vectorul curent prin dublare in cazul in care lungimea sa a ajuns la capacitatea maxima
*/
void redim_vector(Vector*);


/*
* Returneaza numarul de elemente ale vectorului
* input/pre: vector
* return/post: int, numarul de elemente din vector
*/
int get_size(Vector*);


/*
* Returneaza elementul unui vector de pe o anumita pozitie
* input/pre: vector, int(pozitia elementului cautat)
* return/post: elementul corespunzator din vector
*/
TElem get_element(Vector*, int);



/*
* Seteaza numarul de elemente ale unui vector
* input/pre: vector, int(numarul de elemente nou)
* return/post: dimensiunea vectorului se va modifica la numarul intreg dat
*/
void set_size(Vector*, int);


/*
* Modifica un anumit element din vector cu atributele unui alt obiect dat
* input/pre: vector, int(pozitia elementului), element
* return/post: elementul de pe pozitia data din vector va fi modificat cu cel nou si va fi returnat
*/
TElem set_element(Vector*, int, TElem);


/*
* Adauga o cheltuiala in lista de cheltuieli a familiei
* input/pre: vector, element
* return/post: in vector se va adauga cheltuiala data, marindu-se numarul de elemente
*/
void add_element(Vector*, TElem);


/*
* Sterge un element din vector
* input/pre: vector, int(pozitia elementului)
* return/post: se va elimina elementul dat din vector si se va returna elementul sters
*/
TElem delete_element(Vector*, int);


/*
* Interschimba 2 cheltuieli din vector
* input/pre: int, 2 pozitii corespunzatoare celor 2 elemente din vector
* return/post: Se vor interschimba elementele de pe acele pozitii
*/
int exchange_elements(Vector*, int, int);


/*
* Se elibereaza memoria alocata pentru vectorul dinamic
*/
void destroy_vector(Vector*);
