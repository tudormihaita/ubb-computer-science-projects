#pragma once

#include "MDO.h"


class IteratorMDO{
	friend class MDO;
private:

	// constructorul primeste o referinta catre Container
	// iteratorul va referi primul element din container
	// complexitate : O(m)
	IteratorMDO(const MDO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;
	/* aici e reprezentarea  specifica a iteratorului */
	int poz;
	Nod* curent;
	int ind;

public:
		// metoda de optimizare a parcurgerii in ordine a perechilor (cheie, valoare)
		// in constructorul iteratorului, se vor interclasa toate listele inlantuite ordonate de la fiecare locatie de dispersie
		// optimizeaza complexitatea metodei urmator()
		//void interclasare();

		void deplasare();

		// reseteaza pozitia iteratorului la inceputul containerului
		// complexitate : O(m)
		void prim();

		// muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		// complexitate : O(n)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		// complexitate : teta(1)
		bool valid() const;

		// returneaza valoarea elementului din container referit de iterator
		// arunca exceptie daca iteratorul nu e valid
		// teta(1)
		TElem element() const;
};

