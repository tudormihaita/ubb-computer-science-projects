# @author: Mihaita Tudor - grupa 214

######################################
"""
Initializarea dictionarelor de conversie a cifrelor din bazele 2-10,16 in caractere si invers pentru efectuarea conversiilor si operatiilor aritmetice
"""
######################################

to_baza16 = {
    0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9',
    10: 'A', 11: 'B', 12: 'C', 13: 'D', 14: 'E', 15: 'F'
}
from_baza16 = {
    '0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '10': 10,
    'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15, '16': 16
}


def inmultire_cu_o_cifra(nr, cifra, baza):
    """
    realizeaza operatia de inmultire a numarului nr cu cifra data intr-o baza oarecare, respectand algoritmul:
    an an-1 ... a1 a0 (p) *
                      b (p)
    _______________________
    cn+1 cn ... c1 c0 (p)

    i=0,n , t0=0

    ci := (ti+ai*b) mod p
    ti+1:=(ti+ai*b) div p
    cn+1 := tn+1

    :param nr: numar natural, dat sub forma de string
    :param cifra: numar natural <= 9 ( sau <= F in cazul calculelor in baza 16 )
    :param baza: baza p oarecare, 2-10 sau 16
    :return: rezultatul inmultirii numarului nr cu cifra data, in baza specificata
    """
    rez = ""
    nr = nr[::-1]
    cat = 0
    rest = 0
    for i in range(len(nr)):
        produs = from_baza16[nr[i]] * from_baza16[cifra]
        produs += cat
        cat = produs // baza
        rest = produs % baza
        rez = rez + to_baza16[rest]
    if cat != 0:
        rez = rez + to_baza16[cat]
    return rez[::-1]

def impartirea_la_o_cifra(nr, cifra, baza):
    """
    realizeaza operatia de impartire a numarului nr la cifra data intr-o baza oarecare, respectand algoritmul:
    an an-1 ... a1 a0 (p) : b (p) = cn cn-1 ... c1 c0 (p) rest r(p)

    i=n,0 , tn=0

    (ti*p+ai):b = ci rest ti-1
    r := t -1

    :param nr: numar natural, dat sub forma de string
    :param cifra: numar natural <= 9 ( sau <= F in cazul calculelor in baza 16 )
    :param baza: baza p oarecare, 2-10 sau 16
    :return: rezultatul impartirii numarului nr la cifra data, in baza specificata
    """
    rez_cat = ""
    rez_rest = ""
    cat = 0
    rest = 0
    for i in range(len(nr)):
        d = rest * baza + from_baza16[nr[i]]
        cat = d // from_baza16[cifra]
        rest = d % from_baza16[cifra]
        rez_cat = rez_cat + to_baza16[cat]
    rez_rest = to_baza16[rest]

    if len(rez_cat) > 1:
        while rez_cat[0] == '0':
            rez_cat = rez_cat[1:]

    return rez_cat, rez_rest


def adunare_doua_numere(nr1, nr2, baza):
    """
    realizeaza adunarea a doua numere intr-o baza oarecare data, respectand algoritmul:

    an an-1 ... a1 a0 (p) +
    bm bm-1 ... b1 b0 (p)
    _____________________
    ck ck-1 ... c1 c0 (p)

    i=0,max(m,n) presupunem ca vom completa numarul mai scurt cu cifre de 0, t0=0

    ci := (ai+bi+ti) mod p
    ti+1 := (ai+bi+ti) div p
    k= max(m,n)+1, cmax(m,n)+1=t max(m,n)+1

    :param nr1: numar natural, dat sub forma de string
    :param nr2: numar natural, dat sub forma de string
    :param baza: baza p oarecare, 2-10 sau 16
    :return: rezultatul adunarii celor doua numere in baza data
    """
    nr1 = nr1[::-1]
    nr2 = nr2[::-1]
    # determinarea numarului cu lungimea maxima(cele mai multe cifre) si completarea numarului cu lungimea mai mica cu 0-uri
    if len(nr1) > len(nr2):
        lg = len(nr1) - len(nr2)
        for i in range(lg):
            nr2 = nr2 + '0'
    else:
        lg = len(nr2) - len(nr1)
        for i in range(lg):
            nr1 = nr1 + '0'

    lg = len(nr1)
    rez = ""
    cat = 0
    rest = 0
    for i in range(lg):
        s = from_baza16[nr1[i]] + from_baza16[nr2[i]]
        s += cat
        cat = s // baza
        rest = s % baza
        rez = rez + to_baza16[rest]
    if cat != 0:
        rez = rez + to_baza16[cat]

    return rez[::-1]

def scadere_doua_numere(nr1, nr2, baza):
    """
    realizeaza scaderea a doua numere intr-o baza oarecare data, respectand algoritmul:

    Preconditie: nr1>=nr2
    an an-1 ... a1 a0 (p) -
    bm bm-1 ... b1 b0 (p)
    _____________________
    cn cn-1 ... c1 c0 (p)

    i=0,n presupunem ca vom completa numarul mai scurt cu cifre de 0, t0=0

    ci := p+ai-bi+ti , daca ai+ti <bi, ti+1=-1
    ci := ai-bi+ti altfel, ti+1=0

    :param nr1: numar natural, dat sub forma de string
    :param nr2: numar natural, dat sub forma de string
    :param baza: baza p oarecare, 2-10 sau 16
    :return: rezultatul scaderii celor doua numere in baza data
    """
    nr1 = nr1[::-1]
    nr2 = nr2[::-1]
    # completarea numarului mai scurt cu 0-uri
    if len(nr1) > len(nr2):
        lg = len(nr1) - len(nr2)
        for i in range(lg):
            nr2 = nr2 + '0'

    lg = len(nr1)
    rez = ""
    imprumut = 0
    for i in range(lg):
        d = from_baza16[nr1[i]] - imprumut
        d = d - from_baza16[nr2[i]]
        if d >= 0:
            rez = rez + to_baza16[d]
            imprumut = 0
        else:
            rez = rez + to_baza16[baza-abs(d)]
            imprumut = 1

    while rez[-1] == '0':
        rez = rez[:-1]
    return rez[::-1]

############### TESTE OPERATII #######################

#print(adunare_doua_numere('10AC3D', 'F9E40', 16))
#print(inmultire_cu_o_cifra('A23F', '6', 16))
#print(impartirea_la_o_cifra("A27F", '4', 16))
#print(impartirea_la_o_cifra("257", '8', 10))
#print(scadere_doua_numere('11010', '10111', 2))
#print(scadere_doua_numere('80F5', '7A1F', 16))

#####################################################