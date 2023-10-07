#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <stack>

using namespace std;

bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

Colectie::Colectie() {
	this->cp = INITIAL_CAPACITY;

	this->elems = new TElem[cp];

	this->st = new int[cp];
	this->dr = new int[cp];

	this->rad = -1;

	for (int i = 0; i < this->cp-1; i++) {
		this->st[i] = i + 1;
		this->dr[i] = i + 1;
		this-> elems[i] = -1;
	}

	this->elems[cp - 1] = -1;

	this->st[cp - 1] = NIL;

	this->dr[cp - 1] = NIL;

	this->primLiber = 0;
}

void Colectie::redim() {
	int newCapacity = 2 * this->cp;

	TElem* newElems = new TElem[newCapacity];

	int* newSt = new int[newCapacity];
	int* newDr = new int[newCapacity];

	for (int i = 0; i < cp; i++) {
		newElems[i] = elems[i];
		newSt[i] = st[i];
		newDr[i] = dr[i];
	}

	delete[] elems;
	delete[] dr;
	delete[] st;

	elems = newElems;
	st = newSt;
	dr = newDr;

	for (int i = cp; i < newCapacity - 1; i++) {
		st[i] = dr[i] = i + 1;
		elems[i] = -1;
	}

	st[newCapacity - 1] = dr[newCapacity - 1] = NIL;
	elems[newCapacity - 1] = -1;
	primLiber = cp;

	cp = newCapacity;

}

int Colectie::aloca() {
	int i = this->primLiber;
	this->primLiber = this->st[primLiber];

	return i;
}

void Colectie::dealoca(int i) {
	this->st[i] = this->primLiber;
	this->primLiber = i;

	this->elems[i] = -1;
}

int Colectie::creeazaNod(TElem e) {
	if (primLiber == NIL) {
		redim();
	}

	int i = aloca();
	this->elems[i] = e;
	this->st[i] = this->dr[i] = NIL;

	return i;
}


int Colectie::adaugaRec(int p, TElem e) {
	if (p == -1)
		p = creeazaNod(e);
	else {
		if (rel(e, elems[p])) {
				st[p] = adaugaRec(st[p], e);
		}
		else {
			dr[p] = adaugaRec(dr[p], e);
		}
	}


	/*cout << "vecinii nodului " << elems[p] << ":\n";
	cout << elems[st[p]] << ";" << elems[dr[p]] << "\n";
	cout << "parintele nodului: " << elems[p] << ": " << parent[p] << "\n";*/
	return p;
}

int Colectie::adaugaIter(int p, TElem e) {
	int nouNod = creeazaNod(e);

	int curent = p;
	int parent = NIL;


	while (curent != NIL) {
		parent = curent;
		if (rel(e, elems[curent]))
			curent = st[curent];
		else
			curent = dr[curent];
	}

	if (parent == NIL)
		parent = nouNod;
	else if (rel(e, elems[parent]))
		st[parent] = nouNod;
	else
		dr[parent] = nouNod;

	return parent;
}


void Colectie::adauga(TElem e) {
	//varianta recursiva
	//this->rad = adaugaRec(rad, e);

	//varianta iterativa
	if (rad == NIL)
		this->rad = adaugaIter(rad, e);
	else
		adaugaIter(rad, e);

}


int Colectie::minim(int p) {
	int min = p;
	while (p != NIL) {
		min = p;
		p = st[p];
	}

	return min;
}


int Colectie::stergeRec(int p, TElem e) {
	if (p == NIL)
		return NIL;
	else {
		if (e == elems[p]) {
			if (st[p] != NIL && dr[p] != NIL) {
				int temp = minim(dr[p]);
				elems[p] = elems[temp];
				dr[p] = stergeRec(dr[p], elems[p]);

				return p;
			}
			else {
				int temp = p;
				int repl = NIL;

				if (st[p] == NIL) {
					repl = dr[p];
				}
				else {
					repl = st[p];
				}

				dealoca(temp);
				return repl;
			}
		}
		else if (rel(e, elems[p])) {
			st[p] = stergeRec(st[p], e);
			return p;
		}
		else if (!rel(e, elems[p])) {
				dr[p] = stergeRec(dr[p], e);
				return p;
		}
	}
}


int Colectie::stergeIter(int p, TElem e) {
	int curent = p;
	int parent = NIL;

	while (curent != NIL && elems[curent] != e) {
		parent = curent;
		if (rel(e, elems[curent]))
			curent = st[curent];
		else
			curent = dr[curent];
	}

	if (curent == NIL) {
		// valoarea nu exista
		return p;
	}

	// verificam daca are cel mult un descendent nodul respectiv
	if (st[curent] == NIL || dr[curent] == NIL) {
		int repl;

		if (st[curent] == NIL)
			repl = dr[curent];
		else
			repl = st[curent];

		//verificam daca nodul care va fi sters este chiar radacina
		if (parent == NIL) {
			dealoca(curent);
			return repl;
		}

		if (curent == st[parent])
			st[parent] = repl;
		else
			dr[parent] = repl;

		dealoca(curent);
	}
	// nodul care va fi sters are amandoi descendentii
	else {
		int prec = NIL;
		int temp;

		// gasim minimul din subarborele drept / succesorul nodului in inordine
		// nodul respectiv va fi inlocuitorul nodului curent sters
		temp = dr[curent];
		while (st[temp] != NIL) {
			prec = temp;
			temp = st[temp];
		}

		// refacerea legaturilor in cazul in care noul nod mutat avea descendenti
		if (prec != NIL)
			st[prec] = dr[temp];
		else
			dr[curent] = dr[temp];

		elems[curent] = elems[temp];
		dealoca(temp);

	}

	return p;
}


bool Colectie::sterge(TElem e) {
	// varianta recursiva
	/*if (cautaRec(rad, e) == -1)
		return false;
	else {
		this->rad = stergeRec(rad, e);
		return true;
	}*/

	// varianta iterativa
	if (cautaRec(rad, e) == NIL)
		return false;
	else {
		this->rad = stergeIter(rad, e);
		return true;
	}
}

int Colectie::cautaRec(int p, TElem e) const {
	if (p == NIL || elems[p] == e) {
		return p;
	}
	else {
		if (rel(e, elems[p]))
			return cautaRec(st[p], e);
		else
			return cautaRec(dr[p], e);
	}
}

int Colectie::cautaIter(int p, TElem e) const {
	while (p != NIL) {
		if (e == elems[p])
			return p;
		else if (rel(e, elems[p]))
			p = st[p];
		else
			p = dr[p];
	}

	return p;
}


bool Colectie::cauta(TElem elem) const {
	// varianta recursiva
	/*if (cautaRec(rad, elem) == -1)
		return false;
	else
		return true;*/

	//varianta iterativa
	if (cautaIter(rad, elem) == NIL)
		return false;
	else
		return true;
}


int Colectie::nrAparitii(TElem elem) const {
	int nrAp = 0;
	stack<int> S;

	if (rad != NIL)
		S.push(rad);

	while (!S.empty()) {
		int p = S.top();
		S.pop();
		if (elems[p] == elem)
			nrAp++;

		if (dr[p] != NIL)
			S.push(dr[p]);
		if (st[p] != NIL)
			S.push(st[p]);
	}

	return nrAp;
}



int Colectie::dim() const {
	stack<int> S;
	int dim = 0;

	if (rad != NIL)
		S.push(rad);

	while (!S.empty()) {
		int p = S.top();
		S.pop();
		dim++;

		if (dr[p] != NIL)
			S.push(dr[p]);
		if (st[p] != NIL)
			S.push(st[p]);
	}

	return dim;
}


bool Colectie::vida() const {
	return(this->rad == NIL);
}


IteratorColectie* Colectie::iterator() const {
	//return new IteratorPreordine(*this);
	return new IteratorInordine(*this);
}


Colectie::~Colectie() {
	delete[] elems;
	delete[] st;
	delete[] dr;
}
