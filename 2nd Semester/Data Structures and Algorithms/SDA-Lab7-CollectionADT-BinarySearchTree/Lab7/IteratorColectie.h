#pragma once
#include "Colectie.h"
#include <stack>
#include <exception>

using std::stack;
using std::exception;

class IteratorColectie {
public:

	friend class Colectie;

	virtual void prim() = 0;

	virtual void urmator() = 0;

	virtual void anterior() = 0;

	virtual TElem element() const = 0;

	virtual bool valid() const = 0;

	virtual ~IteratorColectie() = default;
};

class IteratorPreordine : public IteratorColectie {
	friend class Colectie;
private:
	IteratorPreordine(const Colectie& c);

	const Colectie& col;
	stack<int> S;
	int curent;

public:
	void prim();

	void urmator();

	bool valid() const;

	TElem element();
};

class IteratorInordine : public IteratorColectie {
	friend class Colectie;

private:
	// constructorul primeste o referinta catre Container
	// iteratorul va referi primul element din container
	
	// complexitate : teta(h)
	IteratorInordine(const Colectie& c);

	// contine o referinta catre containerul pe care il itereaza
	const Colectie& col;

	/* aici e reprezentarea  spcifica a iteratorului*/
	stack<int> S;
	int curent;

	// complexitate : O(h)
	void predecesor(int rad, int& prec, TElem e);

public:

	// reseteaza pozitia iteratorului la inceputul containerului
	// complexitate : teta(h)
	void prim();

	// muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	// complexitate : O(h)
	void urmator();

	//
	void anterior();

	// verifica daca iteratorul e valid (indica un element al containerului)
	// complexitate : teta(1)
	bool valid() const;

	// returneaza valoarea elementului din container referit de iterator
	// arunca exceptie daca iteratorul nu e valid
	// complexitate : teta(1)
	TElem element() const;
};
