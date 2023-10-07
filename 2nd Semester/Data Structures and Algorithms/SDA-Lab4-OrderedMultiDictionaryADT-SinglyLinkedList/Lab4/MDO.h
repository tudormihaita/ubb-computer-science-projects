#pragma once

#define INITIAL_CAPACITY 10
#define NULL_TVALOARE -1

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;
//typedef std::pair<TValoare, int> TFrecventa;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
public:
	friend class IteratorMDO;

private:
	// reprezentare:

	int cp;

	TElem* elems;

	int* urm;

	int prim;

	int primLiber;

	Relatie rel;

	// metode private, valabile doar in implementare
	// definesc operatii auxiliare care implementeaza comportamentul
	// listei inlantuite cu legaturile prin pointeri in reprezentarea inlantuirilor pe tablou

	int aloca();

	void dealoca(int i);

	void redim();

	int creeazaNod(TElem e);

// notatii complexitati:
// n - nr chei
// m - nr perechi

public:

	// constructorul implicit al MultiDictionarului Ordonat
	// complexitate : teta(1)
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	// complexitate : O(m)
	void adauga(TCheie c, TValoare v);

	// cauta o cheie si returneaza vectorul de valori asociate
	// complexitate : teta(m)
	vector<TValoare> cauta(TCheie c) const;

	// sterge o cheie si o valoare 
	// returneaza adevarat daca s-a gasit cheia si valoarea de sters
	// complexitate : O(m)
	bool sterge(TCheie c, TValoare v);

	// returneaza numarul de perechi (cheie, valoare) din MDO
	// complexitate : teta(m)
	int dim() const;

	// verifica daca MultiDictionarul Ordonat e vid
	// complexitate : teta(1) ( sau teta(m) daca folosim metoda dim )
	bool vid() const;

	// returneaza valoarea care apare cel mai frecvent in dictionar. 
	// Daca mai multe valori apar cel mai frecvent, se returneaza una (oricare) dintre ele.
	// Daca dictionarul este vid, operatia returneaza NULL_TVALOARE
	// complexitate : teta(m^2)
	TValoare ceaMaiFrecventaValoare() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	// complexitate : teta(1)
	IteratorMDO iterator() const;


	// destructorul
	// complexitate : teta(1)
	~MDO();

};
