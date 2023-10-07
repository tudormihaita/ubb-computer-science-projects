#pragma once

#define INITIAL_CAPACITY 100
#define NIL -1

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

	friend class IteratorColectie;
	friend class IteratorPreordine;
	friend class IteratorInordine;

private:
	/* aici e reprezentarea */

	int cp;
	int rad;

	TElem* elems;

	int* st;
	int* dr;
	//int* parent;

	int primLiber;

	// metode private
	int aloca();
	void dealoca(int i);
	int creeazaNod(TElem e);

	void redim();

	int adaugaRec(int p, TElem e);
	int adaugaIter(int p, TElem e);

	int cautaRec(int p, TElem e) const;
	int cautaIter(int p, TElem e) const;

	int stergeRec(int p, TElem e);
	int stergeIter(int p, TElem e);

	int minim(int p);

public:
		// constructorul implicit
		// complexitate : teta(cp)
		Colectie();

		// adauga un element in colectie
		// complexitate : O(h)
		void adauga(TElem e);

		// sterge o aparitie a unui element din colectie
		// returneaza adevarat daca s-a putut sterge
		// complexitate : O(h)
		bool sterge(TElem e);

		// verifica daca un element se afla in colectie
		// complexixtate : O(h)
		bool cauta(TElem elem) const;

		// returneaza numar de aparitii ale unui element in colectie
		// complexitate : teta(n)
		int nrAparitii(TElem elem) const;


		// intoarce numarul de elemente din colectie;
		// complexitate : teta(n)
		int dim() const;

		// verifica daca colectia e vida;
		// complexitate : teta(1)
		bool vida() const;

		// returneaza un iterator pe colectie
		// complexitate : teta(1)
		IteratorColectie* iterator() const;

		// destructorul colectiei
		// complexitate : teta(1)
		~Colectie();


};

