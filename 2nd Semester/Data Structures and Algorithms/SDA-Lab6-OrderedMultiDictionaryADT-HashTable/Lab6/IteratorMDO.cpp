#include <limits>
#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	this->poz = 0;

	deplasare();
}


void IteratorMDO::deplasare() {
	while (this->poz < dict.m && dict.elems[poz]==nullptr)
		this->poz++;
	if (this->poz < dict.m) {
		this->curent = dict.elems[poz];
		this->ind = 0;
	}
}

void IteratorMDO::prim(){
	this->poz = 0;

	deplasare();
}

void IteratorMDO::urmator() {
	if (!valid()) {
		throw exception("Iteratorul nu este valid!");
	}

	ind++;
	if (ind == this->curent->v.size()) {
		// se cauta urmatoarea cea mai mica cheie strict mai mare decat cheia curenta, pentru a parcurge perechile (cheie,valoare) in ordine
		// pentru eficientizare se poate realiza interclasarea tuturor perechilor
		TCheie cPrec = this->curent->c;
		TCheie cMin = INT_MAX;
		for (int i = 0; i < dict.m; i++) {
			if (dict.elems[i] != nullptr) {
				Nod* p = dict.elems[i];
				while (p != nullptr) {
					if (p->c > cPrec) {
						if (p->c < cMin)
							cMin = p->c;
					}
					p = p->urm;
				}
			}
		}
		bool gasit = false;
		for (int i = 0; i < dict.m && gasit == false; i++) {
			if (dict.elems[i] != nullptr) {
				Nod* p = dict.elems[i];
				while (p != nullptr && gasit == false) {
					if (p->c == cMin) {
						gasit = true;
						this->poz = i;
						this->curent = p;
						this->ind = 0;
					}

					p = p->urm;
				}
			}
		}
	}

}

bool IteratorMDO::valid() const{
	return (poz < dict.m) && (curent != nullptr) && (ind < curent->v.size());
}

TElem IteratorMDO::element() const{
	if (!valid()) {
		throw exception("Iteratorul nu este valid!");
	}

	return { curent->c, curent->v[ind]};
}


