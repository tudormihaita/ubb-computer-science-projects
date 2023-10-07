#include "IteratorColectie.h"
#include "Colectie.h"
#include <iostream>

IteratorPreordine::IteratorPreordine(const Colectie& c) : col(c) {
	curent = NIL;

	prim();
}

void IteratorPreordine::prim() {
	while (!S.empty())
		S.pop();

	curent = col.rad;
	S.push(col.rad);
}

bool IteratorPreordine::valid() const {
	return curent != NIL && !col.vida();
}

TElem IteratorPreordine::element() {
	if (!valid())
		throw exception("Iteratorul nu este valid!\n");

	return col.elems[curent];
}

void IteratorPreordine::urmator() {
	if (!valid())
		throw exception("Iteratorul nu este valid!\n");

	int aux = S.top();
	S.pop();

	if (col.dr[aux] != NIL)
		S.push(col.dr[aux]);
	if (col.st[aux] != NIL)
		S.push(col.st[aux]);

	if (!S.empty())
		curent = S.top();
	else
		curent = NIL;
}



/* ---------------------------------------------- */
IteratorInordine::IteratorInordine(const Colectie& c) : col(c) {
	this->curent = col.rad;

	prim();

}

TElem IteratorInordine::element() const {
	if (!valid())
		throw exception("Iteratorul nu este valid!\n");

	return col.elems[curent];
}

bool IteratorInordine::valid() const {
	if (this->curent == NIL || col.vida())
		return false;

	return true;
}

void IteratorInordine::urmator() {
	if (!valid())
		throw exception("Iteratorul nu este valid!\n");

	/*stack<int> cS = S;
	std::cout << "STIVA CURENTA: ";
	while (!cS.empty()) {
		std::cout << col.elems[cS.top()] << " ";
		cS.pop();
	}
	std::cout << "\n";*/


	int aux = S.top();
	S.pop();

	if (col.dr[curent] != NIL) {
		curent = col.dr[curent];
		while (curent != NIL) {
			S.push(curent);
			curent = col.st[curent];
		}
	}

	if (!S.empty()) {
		curent = S.top();
	}
	else {
		curent = NIL;
	}

}


/*void IteratorInordine::predecesorIter(int rad, int& prec, TElem e) {
	if (rad == NIL)
		return;

		if (col.elems[rad] == e) {
			if (col.st[rad] != NIL) {
				int temp = col.st[rad];
				while (col.dr[temp] != NIL)
					temp = col.dr[temp];
				prec = temp;
			}

			return;
		}

		if (rel(e, col.elems[rad])) {
			predecesor(col.st[rad], prec, succ, e);
		}
		else {
			prec = rad;
			predecesor(col.dr[rad], prec, succ,  e);
		}

}*/

void IteratorInordine::predecesor(int rad, int& prec, TElem e) {
	if (rad == NIL)
		return;

	predecesor(col.st[rad], prec, e);

	if (rad != NIL && !rel(e, col.elems[rad])) {
		prec = rad;
	}

	predecesor(col.dr[rad], prec, e);
}

//IN LUCRU
void IteratorInordine::anterior() {
	int prec = NIL;
	predecesor(col.rad, prec, col.elems[curent]);

	if (prec == NIL)
		throw exception("Iteratorul nu este valid!\n");

	std::cout << "PRECEDENTUL LUI " << col.elems[curent] << ": " << col.elems[prec] << "\n";

	//S.pop();
	if(col.dr[prec] != curent)
		S.push(prec);

	this->curent = prec;


}

void IteratorInordine::prim() {
	while (!S.empty())
		S.pop();

	curent = col.rad;

	while (curent != NIL) {
		S.push(curent);
		curent = col.st[curent];
	}

	if (!S.empty()) {
		curent = S.top();
	}
}
