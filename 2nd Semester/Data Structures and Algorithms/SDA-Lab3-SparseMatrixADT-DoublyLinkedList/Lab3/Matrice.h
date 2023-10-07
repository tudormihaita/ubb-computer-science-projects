#pragma once

typedef int TElem;

#define NULL_TELEMENT 0


class Nod {

private:
	// reprezentare:

	TElem e;

	int linie;

	int coloana;

	// se retine o referinta catre elementul urmator
	Nod* urm;

	// se retine o referinta catre elementul anterior
	Nod* prec;

public:

	friend class Matrice;

	// constructor nod
	Nod(TElem e, int i, int j) {
		this->e = e;
		this->linie = i;
		this->coloana = j;
		this->urm = nullptr;
		this->prec = nullptr;
	}

	// destructor nod
	~Nod() = default;

	// returneaza elementul curent al listei inlantuite
	// complexitate : teta(1)
	TElem element() {
		return this->e;
	}

	// returneaza referinta/adresa catre urmatorul element
	// complexitate : teta(1) 
	Nod* urmator() {
		return this->urm;
	}

	// returneaza referinta/adresa catre nodul anterior al listei
	// complexitate : teta(1)
	Nod* precedent() {
		return this->prec;
	}

	// modifica valoarea elementului din nod cu o noua valoare data
	// complexitate : teta(1)
	void modifica(TElem e) {
		this->e = e;
	}

	// seteaza nodul urmator nodului curent
	// complexitate : teta(1)
	void setUrm(Nod* urm) {
		this->urm = urm;
	}

	// seteaza nodul precedent nodului curent
	// complexitate : teta(1)
	void setPrec(Nod* prec) {
		this->prec = prec;
	}

	// verifica relatia de ordine lexicografica intre indicii de linie si coloana ale nodurile nenule ale matricei 
	// prin sortare crescatoare dupa linie si coloana
	// complexitate : teta(1)
	bool rel(int i, int j) {
		if (this->linie < i)
			return true;
		else if (this->linie == i) {
			if (this->coloana < j)
				return true;
			else
				return false;
		}
		return false;
	}

	// verifica daca nodul dat reprezinta aceeasi pozitie in matrice ca indicii de linie si coloana dati
	// complexitate : teta(1)
	bool eq(int i, int j) {
		if (this->linie == i && this->coloana == j)
			return true;
		else
			return false;
	}
};




class Matrice {

private:

	int nr_linii;

	int nr_coloane;

	Nod* prim;

	Nod* ultim;

public:

	// constructor
	// se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	// destructor
	~Matrice() { //= default;
		while (prim != nullptr) {
			Nod* p = prim;
			prim = prim->urm;
			delete p;
		}
	};

	void deleteNoduri(Nod* nod) {
		if (nod == nullptr)
			return;

		deleteNoduri(nod->urmator());
		delete nod;
	}


	// returnare element de pe o linie si o coloana
	// se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	// indicii se considera incepand de la 0
	// complexitate : O(n*m)
	TElem element(int i, int j) const;


	// returnare numar linii
	// complexitate : teta(1)
	int nrLinii() const;

	// returnare numar coloane
	// complexitate : teta(1)
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	// complexitate : O(n*m)
	TElem modifica(int i, int j, TElem);


	// redimensioneaza o matrice la o anumita dimensiune. In cazul in care dimensiunile sunt mai mici decat dimensiunile actuale, 
	// elemente de pe pozitiile care nu mai sunt existente vor disparea. In cazul in care dimensiunile sunt mai mari decat dimensiunile actuale, 
	// toate elementele noi (de pe pozitii anterior inexistente) vor fi NULL_TELEMENT
	// arunca exceptie in cazul in care noile dimensiuni sunt negative.
	// complexitate : (O(n*m)^2)
	void redimensioneaza(int numarNouLinii, int numarNouColoane);

};
