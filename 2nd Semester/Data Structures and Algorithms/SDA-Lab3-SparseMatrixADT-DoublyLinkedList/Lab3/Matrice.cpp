#include "Matrice.h"
#include <exception>

using namespace std;


Matrice::Matrice(int m, int n) {
	if (m <= 0 || n <= 0)
		throw exception("Dimensiuni invalide, nu se poate crea matricea!\n");

	this->nr_linii = m;

	this->nr_coloane = n;

	this->prim = nullptr;

	this->ultim = nullptr;
}


int Matrice::nrLinii() const{
	return this->nr_linii;
}


int Matrice::nrColoane() const{
	return this->nr_coloane;
}


TElem Matrice::element(int i, int j) const{
	if ((i < 0 || i >= this->nr_linii) || (j < 0 || j >= this->nr_coloane))
		throw exception("Pozitia data este invalida!\n");

	Nod* p = this->prim;
	while (p != nullptr) {
		if (p->linie == i && p->coloana == j)
			return p->element();
		p = p->urmator();
	}

	return NULL_TELEMENT;

}


TElem Matrice::modifica(int i, int j, TElem e) {
	/*if ((i < 0 || i >= this->nr_linii) || (j < 0 || j >= this->nr_coloane))
		throw exception("Pozitia data este invalida, nu se poate efectua modificarea!\n");*/

	//cazul 1: elementul dat nu exista deja in lista, iar valoarea cu care dorim sa modificam este tot 0
	if (element(i, j) == NULL_TELEMENT && e == NULL_TELEMENT) {
		return NULL_TELEMENT;
	}

	//cazul 2: elementul dat nu exista deja in lista, iar valoarea cu care dorim sa modificam este nenula; elementul va trebui adaugat in lista
	//se determina pozitia pe care trebuie inserat astfel incat sa se verifice ordinea lexicografica
	else if (element(i, j) == NULL_TELEMENT && e != NULL_TELEMENT) {
		Nod* nouNod = new Nod(e, i, j);
		
		if (prim == nullptr) {
			prim = nouNod;
			ultim = nouNod;
			return NULL_TELEMENT;
		}

		Nod* p = this->prim;
		while (p->urm != nullptr && p->urm->rel(i, j))
			p = p->urm;

		if (p->urm == nullptr) {
			p->urm = nouNod;
			nouNod->prec = p;
			ultim = nouNod;
		}
		else {
			p->urm->prec = nouNod;
			nouNod->urm = p->urm;
			p->urm = nouNod;
			nouNod->prec = p;
		}

		return NULL_TELEMENT;
		/*Nod* nouNod = new Nod(e, i, j);

		if (this->prim == nullptr) {
			prim = nouNod;
			ultim = nouNod;
			return NULL_TELEMENT;
		}

		Nod* p = this->prim;
		while (p->urmator() != nullptr && p->urmator()->rel(i, j)) {
			p = p->urmator();
		}

		if (p->urmator() != nullptr) {
			p->urm->prec = nouNod;
			nouNod->urm = p->urm;
			p->urm = nouNod;
			nouNod->prec = p;
		}
		else {
			p->urm = nouNod;
			nouNod->prec = p;
			ultim = nouNod;
		}

		return NULL_TELEMENT;*/
	}
	//cazul 3: elementul dat exista in lista, iar valoarea cu care dorim sa il modificam este nenula; doar se va actualiza valoarea elementului
	else if (element(i, j) != NULL_TELEMENT && e != NULL_TELEMENT) {
		Nod* p = this->prim;
		while (p != nullptr && !p->eq(i, j)) {
			p = p->urmator();
		}

		TElem oldElem = p->element();
		p->modifica(e);
		return oldElem;
	}
	//cazul 4: elementul dat exista in lista, iar valoarea cu care dorim sa il modifica este 0; elementul va fi sters din lista
	else if (element(i, j) != NULL_TELEMENT && e == NULL_TELEMENT) {
		/*if (prim->urmator() == nullptr) {
			TElem oldElem = prim->element();
			delete prim;
			delete ultim;
			prim = nullptr;
			ultim = nullptr;
			return oldElem;
		}*/

		Nod* p = prim;
		while (p != nullptr && !p->eq(i, j))
			p = p->urm;

		if (p == prim) {
			TElem oldElem = p->element();
			prim = prim->urm;
			if (prim == nullptr)
				ultim = nullptr;
			delete p;
			return oldElem;
		}
		else {
			TElem oldElem = p->element();
			Nod* q = prim;
			while (q->urm != p)
				q = q->urm;
			if (p == ultim) {
				q->urm = nullptr;
				ultim = q;
				delete p;
			}
			else {
				q->urm = p->urm;
				p->urm->prec = q;
				delete p;
			}
			return oldElem;
		}
		/*Nod* p = this->prim;
		while (p != nullptr && !p->eq(i, j)) {
			p = p->urmator();
		}

		TElem oldElem = p->element();
		if (p == prim) {
			prim = prim->urmator();
			if(prim == nullptr)
				ultim = nullptr;
			delete p;
			return oldElem;
		}

		if (p->urmator() == nullptr) {
			p->prec->urm = nullptr;
			p = p->prec;
			delete p->urm;
			return oldElem;
		}

		p->prec->urm = p->urm;
		p->urm->prec = p->prec;
		delete p;
		return oldElem;*/


	}
	//cazul 5: perechea de indici data nu este valida
	else {
		throw exception("Pozitia data este invalida, nu se poate efectua modificarea!\n");
	}
}


void Matrice::redimensioneaza(int numarNouLinii, int numarNouColoane) {
	if (numarNouLinii < 0 || numarNouColoane < 0)
		throw exception("Dimensiuni invalide, nu pot fi numere negative!\n");

	//se elimina din lista toate elementele nenule care se afla pe o linie mai mare decat noul numar dat de linii

		Nod* p = this->prim;
		while (p != nullptr) {
			if (p->linie >= numarNouLinii || p->coloana >= numarNouColoane) {
				p = p->prec;
				this->modifica(p->urm->linie, p->urm->coloana, NULL_TELEMENT);
			}
			p = p->urm;
		}


	if (numarNouLinii < this->nrLinii()) {
		this->nr_linii = numarNouLinii;
	}
	if (numarNouColoane < this->nrColoane()) {
		this->nr_coloane = numarNouColoane;
	}

	if (numarNouLinii > this->nrLinii())
		this->nr_linii = numarNouLinii;
	if (numarNouColoane > this->nrColoane())
		this->nr_coloane = numarNouColoane;

}

