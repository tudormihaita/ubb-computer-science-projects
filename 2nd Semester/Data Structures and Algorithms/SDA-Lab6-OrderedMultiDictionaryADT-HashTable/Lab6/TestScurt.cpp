#include <assert.h>

#include "MDO.h"
#include "IteratorMDO.h"

#include <exception>
#include <vector>

using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	MDO dictOrd = MDO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
    dictOrd.adauga(1,2);
    dictOrd.adauga(1,3);
    assert(dictOrd.dim() == 2);
    assert(!dictOrd.vid());
    vector<TValoare> v= dictOrd.cauta(1);
    assert(v.size()==2);
    v= dictOrd.cauta(3);
    assert(v.size()==0);
    IteratorMDO it = dictOrd.iterator();
    it.prim();
    while (it.valid()){
    	TElem e = it.element();
    	it.urmator();
    }
    assert(dictOrd.sterge(1, 2) == true);
    assert(dictOrd.sterge(1, 3) == true);
    assert(dictOrd.sterge(2, 1) == false);
    assert(dictOrd.vid());
}

void testFrecventaValoare() {
    MDO dictOrd = MDO(relatie1);
    assert(dictOrd.ceaMaiFrecventaValoare() == NULL_TVALOARE);

    dictOrd.adauga(1, 4);
    dictOrd.adauga(1, 7);
    dictOrd.adauga(1, 3);
    dictOrd.adauga(1, 9);

    dictOrd.adauga(4, 3);
    dictOrd.adauga(4, 4);
    dictOrd.adauga(14, 4);
    dictOrd.adauga(5, 3);
    dictOrd.adauga(5, 7);

    dictOrd.adauga(3, 3);
    dictOrd.adauga(13, 3);
    dictOrd.adauga(15, 7);
    dictOrd.adauga(7, 4);
    dictOrd.adauga(19, 4);

    dictOrd.adauga(10, 9);
    dictOrd.adauga(20, 7);
    dictOrd.adauga(16, 4);

    assert(dictOrd.ceaMaiFrecventaValoare() == 4);

    dictOrd.adauga(27, 3);
    dictOrd.adauga(54, 3);
    dictOrd.adauga(13, 3);

    assert(dictOrd.ceaMaiFrecventaValoare() == 3);
}