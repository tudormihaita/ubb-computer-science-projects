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
    dictOrd.adauga(1, 2);
    dictOrd.adauga(1, 4);
    dictOrd.adauga(4, 3);
    dictOrd.adauga(5, 2);
    dictOrd.adauga(3, 4);
    dictOrd.adauga(3, 7);
    dictOrd.adauga(8, 5);
    dictOrd.adauga(2, 2);

    assert(dictOrd.ceaMaiFrecventaValoare() == 2);

    dictOrd.adauga(10, 4);
    
    assert(dictOrd.ceaMaiFrecventaValoare() == 2);

    MDO dictOrd1 = MDO(relatie1);
    assert(dictOrd1.ceaMaiFrecventaValoare() == NULL_TVALOARE);

    dictOrd1.adauga(1, 3);
    dictOrd1.adauga(2, 2);
    dictOrd1.adauga(1, 3);

    assert(dictOrd1.ceaMaiFrecventaValoare() == 3);
}
