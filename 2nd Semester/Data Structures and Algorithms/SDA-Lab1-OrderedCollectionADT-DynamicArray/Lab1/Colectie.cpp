#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

/* complexitate relatie: teta(1) */
bool rel(TElem e1, TElem e2) {
	return (e1 <= e2);
}

/* complexitate creator colectie: teta(1) */
Colectie::Colectie() {
	this->cp = 50;
	elems = new TElem[this->cp];
	this->size = 0;
}

/* complexitate redimensionare adaugare vector dinamic colectie: teta(n) */
void Colectie::redim_adaugare() {
	TElem *eNew = new TElem[2 * this->cp];
	for (int i = 0; i < this->size; i++)
		eNew[i] = this->elems[i];

	this->cp = 2 * this->cp;
	delete[] elems;
	elems = eNew;
}

/* complexitate redimensionare stergere vector dinamic colectie: teta(n) */
void Colectie::redim_stergere() {
	TElem* eNew = new TElem[this->cp/2+1];
	for (int i = 0; i < this->size; i++)
		eNew[i] = this->elems[i];

	this->cp = this->cp/2;
	delete[] elems;
	elems = eNew;
}

/* complexitate adaugare element colectie: O(n) */
void Colectie::adauga(TElem e) {
	if (this->size == this->cp)
		redim_adaugare();
	if (rel(e ,this->elems[this->size]))
		this->elems[this->size++] = e;
	else {
		int i;
		for (i = this->size - 1; i >= 0 && !rel(this->elems[i], e); i--){
			this->elems[i+1] = this->elems[i];
		}
		this->elems[i + 1] = e;
		this->size++;
	}
}

/* complexitate stergere element colectie: O(n) */
bool Colectie::sterge(TElem e) {
	bool gasit = false;
	int st, dr, mid;
	int ind;
	st = 0; dr = this->size-1;
	while (st <= dr && gasit == false) {
		mid = (st + dr) / 2;
		if (this->elems[mid] == e) {
			gasit = true;
			ind = mid;
		}
		else if (e < this->elems[mid])
			dr = mid - 1;
		else
			st = mid + 1;
	}
	if (gasit == true) {
		for (int i = ind; i < this->size - 1; i++)
			this->elems[i] = this->elems[i + 1];
		this->size--;
		if (this->size <= this->cp / 2)
			redim_stergere();
	}
	return gasit;
}


/* complexitate cautare element colectie: O(log2n) */
bool Colectie::cauta(TElem elem) const {
	bool gasit = false;
	int st, dr, mid;
	st = 0; dr = this->size - 1;
	while (st <= dr && gasit == false) {
		mid = (st + dr) / 2;
		if (this->elems[mid] == elem) {
			gasit = true;
		}
		else if (elem < this->elems[mid])
			dr = mid - 1;
		else
			st = mid + 1;
	}
	return gasit;
	
}


/* complexitate numar aparitii element colectie: teta(n) */
int Colectie::nrAparitii(TElem elem) const {
	int nr = 0;
	for (int i = 0; i < this->size; i++)
		if (this->elems[i] == elem)
			nr++;
	return nr;
}


/* complexitate numar elemente unice colectie: O(n^2) */
int Colectie::numaraElementeUnice() const {
	int nr_uniq = 0;
	int* uniq = new int[this->cp];

	for (int i = 0; i < this->size; i++) {
		int elem_curent = this->elems[i];
		bool gasit = false;
		for (int j = 0; j < nr_uniq && gasit == false; j++) {
			if (uniq[j] == elem_curent)
				gasit = true;
		}
		if (gasit == false) {
			uniq[nr_uniq] = elem_curent;
			nr_uniq++;
		}

	}

	delete[] uniq;
	return nr_uniq;

}

/* complexitate returnare dimensiune colectie: teta(1) */
int Colectie::dim() const {
	return this->size;
}

/* complexitate verificare colectie vida: teta(1) */
bool Colectie::vida() const {
	return(this->size == 0);
}

/* complexitate creator iterator colectie: teta(1) */
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

/* complexitate destructor colectie: teta(1) */
Colectie::~Colectie() {
	this->size = 0;
	this->cp = 0;
	delete[] elems;
}
