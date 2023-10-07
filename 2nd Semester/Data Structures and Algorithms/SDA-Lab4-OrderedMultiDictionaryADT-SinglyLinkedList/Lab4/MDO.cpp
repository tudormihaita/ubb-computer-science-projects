#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	this->cp = INITIAL_CAPACITY;

	this->prim = -1;

	this->rel = r;

	this->elems = new TElem[cp];

	this->urm = new int[cp];

	for (int i = 0; i < this->cp - 1; i++) {
		this->urm[i] = i + 1;
	}
	this->urm[cp - 1] = -1;

	this->primLiber = 0;
}

int MDO::aloca() {
	int i = this->primLiber;
	this->primLiber = this->urm[primLiber];

	return i;
}


void MDO::dealoca(int i) {
	this->urm[i] = this->primLiber;
	this->primLiber = i;
}


void MDO::redim() {
	int newCapacity = 2 * this->cp;

	TElem* newElems = new TElem[newCapacity];

	int* newUrm = new int[newCapacity];

	for (int i = 0; i < this->cp; i++) {
		newElems[i] = this->elems[i];
		newUrm[i] = this->urm[i];
	}

	delete[] this->elems;
	delete[] this->urm;

	this->elems = newElems;
	this->urm = newUrm;

	for (int i = this->cp; i < newCapacity-1; i++) {
		this->urm[i] = i + 1;
	}

	this->urm[newCapacity - 1] = -1;
	this->primLiber = this->cp;

	this->cp = newCapacity;
}

int MDO::creeazaNod(TElem e) {
	if (this->primLiber == -1) {
		redim();
	}
	int i = aloca();
	this->elems[i] = e;
	this->urm[i] = -1;

	return i;
}

void MDO::adauga(TCheie c, TValoare v) {
	int nouNod = creeazaNod({ c,v });

	if (this->prim == -1) {
		this->urm[nouNod] = this->prim;
		this->prim = nouNod;
	}
	else {
		int i = this->prim;
		while ( i != -1 && rel(this->elems[i].first, c)) {
			i = this->urm[i];
		}

		if (i == this->prim) {
			this->urm[nouNod] = this->prim;
			this->prim = nouNod;
		}
		else {
			int nod = this->prim;
			while (this->urm[nod] != i) {
				nod = this->urm[nod];
			}

			if (i == -1) {
				this->urm[nod] = nouNod;
			}
			else {
				this->urm[nouNod] = this->urm[nod];
				this->urm[nod] = nouNod;
			}
		}
	}
}

vector<TValoare> MDO::cauta(TCheie c) const {
	if (vid()) {
		return {};
	}


	vector<TValoare> vals;
	int nod = this->prim;

	while (nod != -1) {
		if (elems[nod].first == c) {
			vals.push_back(elems[nod].second);
		}
		nod = urm[nod];
	}
	
	return vals;
}

bool MDO::sterge(TCheie c, TValoare v) {
	int nod = this->prim;
	bool gasit = false;
	int p = -1;

	while (nod != -1 && gasit == false) {
		if (elems[nod].first == c && elems[nod].second == v) {
			gasit = true;
			p = nod;
		}

		nod = urm[nod];
	}

	if (gasit == true) {
		if (p == this->prim) {
			prim = urm[prim];
		}
		else {
			int q = this->prim;
			while (urm[q] != p) {
				q = urm[q];
			}
			urm[q] = urm[p];
		}
		dealoca(p);
	}

	return gasit;
}

int MDO::dim() const {
	if (this->prim == -1) {
		return 0;
	}
	else {
		int dim = 1;
		int i = this->prim;
		while (this->urm[i] != -1) {
			i = this->urm[i];
			dim++;
		}

		return dim;
	}
}


TValoare MDO::ceaMaiFrecventaValoare() const {
	if (vid()) {
		return NULL_TVALOARE;
	}

	int frMax = NULL_TVALOARE;
	TValoare valMax = NULL_TVALOARE;

	int nod = this->prim;
	while (nod != -1) {
		TValoare val = this->elems[nod].second;
		int frCurent = 0;
		int p = this->prim;
		while (p != -1) {
			if (this->elems[p].second == val) {
				frCurent++;
			}
			p = this->urm[p];
		}

		if (frCurent > frMax) {
			frMax = frCurent;
			valMax = val;
		}

		nod = this->urm[nod];
	}

	return valMax;

	// ceva incercare esuata
	/*int frMax = NULL_TVALOARE;
	int* fr = new int[this->cp];

	for (int i = 0; i < this->cp; i++)
		fr[i] = 0;

	TValoare valMax = NULL_TVALOARE;

	int nod = this->prim;
	while (nod != -1) {
		TCheie c = this->elems[nod].first;
		vector<TValoare> vals = cauta(c);
		for (auto& val : vals) {
			fr[val]++;
		}

		nod = this->urm[nod];

	}

	for(int i=0;i<this->cp;i++)
		if (fr[i] > frMax) {
			frMax = fr[i];
			valMax = i;
		}

	return valMax;*/
}


bool MDO::vid() const {
	return(this->prim == -1);
	//return(dim() == 0);
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	delete[] this->elems;
	delete[] this->urm;
}
