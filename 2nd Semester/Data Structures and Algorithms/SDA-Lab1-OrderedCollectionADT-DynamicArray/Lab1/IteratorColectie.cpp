#include "IteratorColectie.h"
#include "Colectie.h"
#include <stdexcept>


/* complexitate creator iterator colectie: teta(1) */
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	this->curent = 0;
}


/* complexitate returnare element colectie prin iterator: teta(1) */
TElem IteratorColectie::element() const{
	if (valid())
		return col.elems[this->curent];
	else
		throw std::out_of_range("Iteratorul nu este valid, nu se poate accesa elementul!");
}


/* complexitate verificare iterator valid: teta(1) */
bool IteratorColectie::valid() const {
	if (col.size <= this->curent)
		return false;
	else if (col.size == 0)
		return false;
	else
		return true;
}


/* complexitate iterare element urmator colectie: teta(1) */
void IteratorColectie::urmator() {
	if (valid())
		this->curent++;
	else
		throw std::out_of_range("Iteratorul este invalid, nu se poate trece la urmatorul element!");
}

/* complexitate setare iterator la primul element din colectie: teta(1) */
void IteratorColectie::prim() {
	this->curent = 0;
}
