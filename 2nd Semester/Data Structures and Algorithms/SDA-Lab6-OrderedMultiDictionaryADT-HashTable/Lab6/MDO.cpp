#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

MDO::MDO(Relatie r) {
	this->n = 0;
	this->m = MAX;

	this->elems = new Nod*[m];
	for (int i = 0; i < m; i++)
		this->elems[i] = nullptr;

	this->rel = r;

}

int hashCode(TCheie c) {
	return abs(c);
}

int MDO::d(TCheie c) const {
	return hashCode(c) % m;
}


void MDO::adauga(TCheie c, TValoare v) {
	int poz = this->d(c);

	//Nod* p = new Nod(c, { v }, nullptr);

	if (this->elems[poz] == nullptr) {
		Nod* nouNod = new Nod(c, { v }, nullptr);
		nouNod->urm = this->elems[poz];
		this->elems[poz] = nouNod;
	}
	else {
		Nod* p = this->elems[poz];
		while (p != nullptr && p->c != c) {
			p = p->urm;
		}

		if (p != nullptr && p->c == c) {
			p->v.push_back(v);
		}
		else {
			Nod* nouNod = new Nod(c, { v }, nullptr);
			Nod* p = this->elems[poz];

			while (p != nullptr && rel(p->c, c)) {
				p = p->urm;
			}

			if (p == elems[poz]) {
				nouNod->urm = elems[poz];
				elems[poz] = nouNod;
			}
			else {
				Nod* q = this->elems[poz];
				while (q->urm != p) {
					q = q->urm;
				}

				if (p == nullptr) {
					q->urm = nouNod;
				}
				else {
					nouNod->urm = q->urm;
					q->urm = nouNod;
				}
			}
		}
	}

	this->n++;
}



vector<TValoare> MDO::cauta(TCheie c) const {
	int poz = d(c);
	Nod* p = this->elems[poz];
	while (p != nullptr) {
		if (p->c == c)
			return p->v;
		p = p->urm;
	}

	return {};

}

bool MDO::sterge(TCheie c, TValoare v) {
	int poz = d(c);
	Nod* p = this->elems[poz];
	bool gasit = false;
	while (p != nullptr && gasit == false) {
		if (p->c == c)
			if (find(p->v.begin(), p->v.end(), v) != p->v.end())
				gasit = true;
		p = p->urm;
	}

	if (gasit == true) {
		Nod* p = this->elems[poz];
		while (p->c != c) {
			p = p->urm;
		}

		p->v.erase(find(p->v.begin(), p->v.end(), v));
		if (p->v.empty()) {
			if (p == this->elems[poz]) {
				this->elems[poz] = this->elems[poz]->urm;
				delete p;
			}
			else if (p->urm == nullptr) {
				Nod* q = this->elems[poz];
				while (q->urm != p) {
					q = q->urm;
				}

				q->urm = nullptr;
				delete p;
			}
			else {
				Nod* q = this->elems[poz];
				while (q->urm != p) {
					q = q->urm;
				}

				q->urm = p->urm;
				delete p;
			}
		}
	}

	return gasit;
}

TValoare MDO::ceaMaiFrecventaValoare() const {
	if (this->vid())
		return NULL_TVALOARE;

	int frMax = 0;
	int valMax = NULL_TVALOARE;
	IteratorMDO it = this->iterator();
	it.prim();
	while (it.valid()) {
		int frC = 0;
		int valC = it.element().second;
		IteratorMDO itC = this->iterator();
		itC.prim();
		while (itC.valid()) {
			if (itC.element().second == valC) {
				frC++;
			}
			itC.urmator();
		}
		if (frC > frMax) {
			frMax = frC;
			valMax = valC;
		}

		it.urmator();
	}

	return valMax;

}

int MDO::dim() const {
	if (this->vid())
		return 0;
	int dim = 0;
	for (int i = 0; i < m; i++) {
		Nod* p = this->elems[i];
		while (p != nullptr) {
			dim += int(p->v.size());
			p = p->urm;
		}
	}

	return dim;
}

bool MDO::vid() const {
	for (int i = 0; i < m; i++) {
		if (this->elems[i] != nullptr)
			return false;
	}

	return true;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	for (int i = 0; i < m; i++) {
		while (this->elems[i] != nullptr) {
			Nod* p = this->elems[i];
			this->elems[i] = this->elems[i]->urm;
			delete p;
		}
	}

	delete[] this->elems;
}
