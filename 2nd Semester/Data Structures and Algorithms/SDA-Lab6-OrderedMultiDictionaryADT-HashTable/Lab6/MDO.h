#pragma once

#include <vector>
#include <cmath>

#define MAX 10
#define NULL_TVALOARE -1

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie,TValoare > TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class Nod {
private:
	TCheie c;
	vector<TValoare> v;
	//TElem e;

	Nod* urm;
public:
	friend class MDO;
	friend class IteratorMDO;

	Nod() = default;

	Nod(TCheie c, vector<TValoare> v, Nod* urm) {
		this->c = c;
		this->v = v;
		this->urm = urm;
	}
};

class MDO {
	friend class IteratorMDO;
    private:
		int n;

		int m;

		int d(TCheie c) const;

		Relatie rel;

		Nod** elems;


    public:

	// constructorul implicit al MultiDictionarului Ordonat
	// complexitate : teta(m)
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	// complexitate : O(n) / O(n/m) - in contextul dispersiei perfecte
	void adauga(TCheie c, TValoare v);

	// cauta o cheie si returneaza vectorul de valori asociate
	// complexitate : O(n) / O(n/m) - in contextul dispersiei perfecte
	vector<TValoare> cauta(TCheie c) const;

	// sterge o cheie si o valoare 
	// returneaza adevarat daca s-a gasit cheia si valoarea de sters
	// complexitate : O(n/m)
	bool sterge(TCheie c, TValoare v);

	// returneaza valoarea care apare cel mai frecvent în dictionar. Daca mai multe valori apar cel mai frecvent, se returneaza 
	// una (oricare) dintre ele.
	// daca dictionarul este vid, operatia returneaza NULL_TVALOARE
	TValoare ceaMaiFrecventaValoare() const;

	// returneaza numarul de perechi (cheie, valoare) din MDO
	// complexitate : teta(m)
	int dim() const;

	// verifica daca MultiDictionarul Ordonat e vid 
	// complexitate : O(m)
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	// complexitate : O(m)
	IteratorMDO iterator() const;

	// destructorul
	// complexitate : teta(n)
	~MDO();

};