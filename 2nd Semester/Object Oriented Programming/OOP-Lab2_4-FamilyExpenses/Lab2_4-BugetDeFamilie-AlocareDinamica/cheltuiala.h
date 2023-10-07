#pragma once

typedef struct {
	int zi;
	double suma;
	char* tip;
}Cheltuiala;



/*
* Se creeaza o cheltuiala si se initializeaza
* input/pre: un numar intreg(ziua din luna, int > 0 si <= 31), un numar real(suma cheltuita)
* si un string(tipul cheltuielii, unul din: Mancare, Transport, Telefon&Internet, Imbracaminte, Altele)
* return/post: cheltuiala cu ziua, suma si tipul dat
*/
Cheltuiala* create_cheltuiala(int, double, char*);


/*
* Creeaza o copie a cheltuielii date
* input/pre: o cheltuiala valida
* return/post: o copie a cheltuielii date
*/
Cheltuiala* copy_cheltuiala(Cheltuiala*);


/*
* returneaza tipul cheltuielii
* input/pre: cheltuiala
* return/post: tipul cheltuielii date sub forma de string
*/
char* get_tip(Cheltuiala*);


/*
* Returneaza ziua in care a fost efectuata cheltuiala
* input/pre: cheltuiala
* return/post: ziua(int) din luna in care a fost efectuala cheltuiala data
*/
int get_zi(Cheltuiala*);


/*
* Returneaza valoarea cheltuielii efectuate
* input/pre: cheltuiala
* return/post: suma corespunzatoare valorii cheltuielii date
*/
double get_suma(Cheltuiala*);


/*
* Seteaza tipul unei cheltuieli
* input/pre: cheltuiala, un string din lista:Mancare, Transport, Telefon&Internet, Imbracaminte, Altele
* return/post: tipul cheltuielii va deveni string-ul dat
*/
void set_tip(Cheltuiala*, char*);


/*
* Seteaza ziua in care a fost efectuata cheltuiala
* input/pre: cheltuiala, un int egal cu o zi din luna
* return/post: ziua cheltuielii va fi egala cu numarul intreg dat
*/
void set_zi(Cheltuiala*, int);


/*
* Seteaza suma care a fost achitata pentru efectuarea cheltuielii
* input/pre: cheltuiala, un double egal cu suma
* return/post: suma cheltuielii va fi egala cu valoarea reala data
*/
void set_suma(Cheltuiala*, double);


/*
* Seteaza unei cheltuieli atributele alteia
* input/pre: 2 cheltuieli
* return/post: atributele primei cheltuieli vor deveni identicele cu cele
* ale cheltuielii 2
*/
void replace_cheltuiala(Cheltuiala*, Cheltuiala*);


/*
* Compara 2 cheltuieli
* input/pre: 2 cheltuieli
* return/post: 1 daca ziua, suma si tipul cheltuielilor coincid
*			   0 altfel
*/
int compare_cheltuieli(Cheltuiala*, Cheltuiala*);


/*
* Se sterg informatiile unei cheltuieli date
* input/pre: cheltuiala
* return/post: se elimina informatiile din atributele cheltuielii, marcand-o ca fiind stearsa
*/
void destroy_cheltuiala(Cheltuiala*);