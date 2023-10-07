# @author: Mihaita Tudor - grupa 214

from operatii_aritmetice.operatii import inmultire_cu_o_cifra, adunare_doua_numere, impartirea_la_o_cifra

######################################
"""
Initializarea dictionarelor de conversie a cifrelor din bazele 2-10,16 in caractere si invers pentru efectuarea conversiilor si operatiilor aritmetice
Initializarea decitionarelor de conversii rapide din baza 2 in bazele 4,8,16 si invers
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

tabel_conversie_rapida_baza4_baza2 = {
    '0': '00', '1': '01', '2': '10', '3': '11'
}
tabel_conversie_rapida_baza8_baza2 = {
    '0': '000', '1': '001', '2': '010', '3': '011', '4': '100',
    '5': '101', '6': '110', '7': '111'
}
tabel_conversie_rapida_baza16_baza2 = {
    '0': '0000', '1': '0001', '2': '0010', '3': '0011', '4': '0100', '5': '0101', '6': '0110', '7': '0111', '8': '0111',
    '9': '1001', 'A': '1010', 'B': '1011', 'C': '1100', 'D': '1101', 'E': '1110', 'F': '1111'
}

tabel_conversie_rapida_baza2_baza4 = {
    '00': '0', '01': '1', '10': '2', '11': '3'
}

tabel_conversie_rapida_baza2_baza8 = {
    '000': '0', '001': '1', '010': '2', '011': '3', '100': '4',
    '101': '5', '110': '6', '111': '7'
}

tabel_conversie_rapida_baza2_baza16 = {
    '0000': '0', '0001': '1', '0010': '2', '0011': '3', '0100': '4', '0101': '5', '0110': '6', '0111': '7', '1000': '8',
    '1001': '9', '1010': 'A', '1011': 'B', '1100': 'C', '1101': 'D', '1110': 'E', '1111': 'F'
}


def conversie_baza_intermediara(a, baza_sursa, baza_destinatie):
    """
    converteste numarul natural dat a din baza sursa in baza destinatie, utilizand baza intermediara 10
    realizeaza conversia lui a din baza sursa in baza 10 prin substitutie
    converteste numarul obtinut in baza 10 in baza destinatie prin impartiri succesive
    :param a: numar natural, sub forma de string
    :param baza_sursa: baza p oarecare, 2-10 sau 16
    :param baza_destinatie: baza q oarecare, 2-10 sau 16
    :return: c - numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    b = 0
    # inversarea numarului dat initial drept string, pentru a aplica mai usor conversia prin subsitutie in baza intermediara 10
    a = a[::-1]
    p = baza_sursa
    # aplicarea metodei conversiei prin substitutie din baza sursa p in baza intermediara 10
    for i in range(len(a) - 1, -1, -1):
        if a[i].isdigit():
            b = b + int(a[i]) * pow(p, i)
        else:
            b = b + from_baza16[a[i]] * pow(p, i)

    string_c = ""
    q = baza_destinatie
    # aplicarea metodei conversiei prin impartiri succesive din baza intermediara 10 in baza destinatie q
    while b != 0:
        cat = b // q
        rest = b % q
        if rest < 10:
            string_c = string_c + str(rest)
        else:
            string_c = string_c + to_baza16[rest]
        b = cat

    # string-ul obtinut reprezinta numarul inversat in baza destinatie q, deci vom returna sirul inversat pentru a obtine numarul dorit
    return string_c[::-1]


def conversie_substitutie(a, baza_sursa, baza_destinatie):
    """
    converteste numarul dat a sub forma de string din baza sursa in baza destinatie prin metoda substitutiei, cu preconditia ca baza sursa < baza destinatie
    fiecare cifra este inmultita cu baza sursa ridicata la puterea corespunzatoare pozitiei ocupate de cifra in numar
    (numerotate de la 0 la n-1 de la dreapta la stanga), si produsele obtinute se aduna, calculele fiind efectuate in baza destinatie
    rezultatul final reprezinta numarul scris in baza destinatie
    :param a: numar natural, sub forma de string
    :param baza_sursa: baza p oarecare, 2-10 sau 16
    :param baza_destinatie: baza q oarecare, 2-10 sau 16
    :return: numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    a = a[::-1]
    rez = ""
    b = '0'
    p = baza_sursa
    q = baza_destinatie
    for i in range(0, len(a)):
        putere = '1'
        for j in range(0, i):
            # obtinerea bazei sursa ridicata la puterea corespunzatoare pozitiei cifrei in numar, utilizand operatia de inmultire cu o cifra
            # pentru a efectua toate calculele in baza data
            putere = inmultire_cu_o_cifra(putere, str(p), q)

        # inmultirea puterii obtinute cu cifra numarului
        putere = inmultire_cu_o_cifra(putere, a[i], q)

        # adunarea rezultatelor intre ele pentru a obtine numarul final scris in baza destinatie
        b = adunare_doua_numere(b, putere, q)
    rez = b
    # returnarea numarului final in baza destinatie sub forma de string
    return rez


def conversie_impartiri_succesive(a, baza_sursa, baza_destinatie):
    """
    converteste numarul dat a sub forma de string din baza sursa in baza destinatie, folosind metoda impartirilor succesive
    calculele sunt efectuate in baza sursa
    numarul se imparte cu baza destinatie, apoi catul rezultat se imparte la baza pana cand catul devine 0
    resturile rezultate in urma impartirilor scrise in ordine inversa reprezinta numarul dat scris in baza destinatie
    :param a: numar natural, sub forma de string
    :param baza_sursa: baza p oarecare, 2-10 sau 16
    :param baza_destinatie: baza q oarecare, 2-10 sau 16
    :return: numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    b = ""
    p = baza_sursa
    q = baza_destinatie
    cat = a
    # impartirea numarului la baza destinatie pana cand catul obtinut devine 0, utilizand in acest scop operatia de impartire la o cifra
    while cat != '0':
        cat, rest = impartirea_la_o_cifra(cat, str(q), p)
        # adaugarea restului la string-ul egal cu numarul scris in baza destinatie
        b = b + rest
    # returnarea sirului inversat, pentru a obtine numarul final in baza destinatie
    return b[::-1]


def conversie_rapida_baza2_baza4(a):
    """
    converteste numarul natural a dat sub forma de string din baza sursa 2 in baza destinatie 4, utilizand tabelul de conversii rapide
    :param a: numar natural, sub forma de string
    :return: numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    a = a[::-1]
    b = ""
    # completarea cu 0-uri la finalul numarului pentru a obtine o grupare corespunzatoare unei cifre din baza destinatie din tabelul de conversie rapida
    while len(a) % 2 != 0:
        a = a + '0'
    for i in range(0, len(a) - 1, 2):
        cifra_baza4 = a[i + 1] + a[i]
        b = b + tabel_conversie_rapida_baza2_baza4[cifra_baza4]

    return b[::-1]


def conversie_rapida_baza4_baza2(a):
    """
    converteste numarul natural a dat sub forma de string din baza sursa 4 in baza destinatie 2, utilizand tabelul de conversii rapide
    :param a: numar natural, sub forma de string
    :return: numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    b = ""
    for i in range(len(a)):
        b = b + tabel_conversie_rapida_baza4_baza2[a[i]]
    while b[0] == '0':
        b = b[1:]
    return b


def conversie_rapida_baza2_baza8(a):
    """
    converteste numarul natural a dat sub forma de string din baza sursa 2 in baza destinatie 8, utilizand tabelul de conversii rapide
    :param a: numar natural, sub forma de string
    :return: numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    a = a[::-1]
    b = ""
    # completarea cu 0-uri la finalul numarului pentru a obtine o grupare corespunzatoare unei cifre din baza destinatie din tabelul de conversie rapida
    while len(a) % 3 != 0:
        a = a + '0'
    for i in range(0, len(a) - 2, 3):
        #formarea unei grupe de cifre din baza 2 corespunatoare unei singure cifre din baza destinatie
        cifra_baza8 = a[i + 2] + a[i + 1] + a[i]
        b = b + tabel_conversie_rapida_baza2_baza8[cifra_baza8]

    return b[::-1]


def conversie_rapida_baza8_baza2(a):
    """
    converteste numarul natural a dat sub forma de string din baza sursa 8 in baza destinatie 2, utilizand tabelul de conversii rapide
    :param a: numar natural, sub forma de string
    :return: numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    b = ""
    for i in range(len(a)):
        b = b + tabel_conversie_rapida_baza8_baza2[a[i]]
    while b[0] == '0':
        b = b[1:]
    return b


def conversie_rapida_baza2_baza16(a):
    """
    converteste numarul natural a dat sub forma de string din baza sursa 2 in baza destinatie 16, utilizand tabelul de conversii rapide
    :param a: numar natural, sub forma de string
    :return: numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    a = a[::-1]
    b = ""
    # completarea cu 0-uri la finalul numarului pentru a obtine o grupare corespunzatoare unei cifre din baza destinatie din tabelul de conversie rapida
    while len(a) % 4 != 0:
        a = a + '0'
    for i in range(0, len(a) - 3, 4):
        cifra_baza16 = a[i + 3] + a[i + 2] + a[i + 1] + a[i]
        b = b + tabel_conversie_rapida_baza2_baza16[cifra_baza16]

    return b[::-1]


def conversie_rapida_baza16_baza2(a):
    """
    converteste numarul natural a dat sub forma de string din baza sursa 16 in baza destinatie 2, utilizand tabelul de conversii rapide
    :param a: numar natural, sub forma de string
    :return: numar natural egal cu numarul dat a in baza_sursa, scris in baza_destinatie
    """
    b = ""
    for i in range(len(a)):
        b = b + tabel_conversie_rapida_baza16_baza2[a[i]]
    while b[0] == '0':
        b = b[1:]
    return b


############### TESTE CONVERSII ######################

# print(conversie_substitutie('7902', 16, 10))
# print(conversie_baza_intermediara('7816', 9, 4))
# print(conversie_impartiri_succesive('27', 8, 10))
# print(conversie_rapida_baza2_baza4('1110100'))
# print(conversie_rapida_baza2_baza8('11110100'))
#print(conversie_rapida_baza2_baza16('111110100'))
# print(conversie_rapida_baza4_baza2('1310'))
#print(conversie_rapida_baza16_baza2('1F4'))
print(conversie_impartiri_succesive('FFD4', 16, 6))
######################################################