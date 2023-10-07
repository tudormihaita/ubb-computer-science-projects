# @author: Mihaita Tudor - grupa 214

from algoritmi.conversii import *
from operatii_aritmetice.operatii import *

to_baza16 = {
    0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9',
    10: 'A', 11: 'B', 12: 'C', 13: 'D', 14: 'E', 15: 'F'
}
from_baza16 = {
    '0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '10': 10,
    'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15, '16': 16
}


def run_conversie_numar():
    nr = input("Introduceti numarul pe care doriti sa-l convertiti:")
    baza_sursa = input("Introduceti baza sursa in care este scris numarul dat:")
    baza_destinatie = input("Introduceti baza in care doriti sa convertiti numarul dat:")
    if int(baza_sursa) < 2 or (int(baza_sursa) > 10 and int(baza_sursa) < 16):
        print("Baza sursa introdusa invalida!")
        return
    if int(baza_destinatie) < 2 or (int(baza_destinatie) > 10 and int(baza_destinatie) < 16):
        print("Baza destinatie introdusa invalida!")
        return
    for i in range(0, len(nr)):
        if from_baza16[nr[i]] >= int(baza_sursa):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    if int(baza_sursa) == 2 and int(baza_destinatie) in [4, 8, 16]:
        print("Se vor utiliza conversiile rapide")
        if int(baza_destinatie) == 4:
            print(conversie_rapida_baza2_baza4(nr))
        elif int(baza_destinatie) == 8:
            print(conversie_rapida_baza2_baza8(nr))
        elif int(baza_destinatie) == 16:
            print(conversie_rapida_baza2_baza16(nr))

    elif int(baza_destinatie) == 2 and int(baza_sursa) in [4, 8, 16]:
        print("Se vor utiliza conversiile rapide")
        if int(baza_sursa) == 4:
            print(conversie_rapida_baza4_baza2(nr))
        elif int(baza_sursa) == 8:
            print(conversie_rapida_baza8_baza2(nr))
        elif int(baza_sursa) == 16:
            print(conversie_rapida_baza16_baza2(nr))

    elif int(baza_sursa) < int(baza_destinatie):
        print("Se recomanda utilizarea conversiei prin substitutie sau prin baza intermediara")
        print("1 - conversie prin substitutie")
        print("2 - conversie prin baza intermediara")
        optiune = input(">>>")
        optiune = optiune.strip()
        if optiune == '1':
            print(conversie_substitutie(nr, int(baza_sursa), int(baza_destinatie)))
        elif optiune == '2':
            print(conversie_baza_intermediara(nr, int(baza_sursa), int(baza_destinatie)))
        else:
            print("comanda invalida!")
    elif int(baza_sursa) > int(baza_destinatie):
        print("Se recomanda utilizarea conversiei prin impartiri succesive sau prin baza intermediara")
        print("1 - conversie prin impartiri succesive")
        print("2 - conversie prin baza intermediara")
        optiune = input(">>>")
        optiune = optiune.strip()
        if optiune == '1':
            print(conversie_impartiri_succesive(nr, int(baza_sursa), int(baza_destinatie)))
        elif optiune == '2':
            print(conversie_baza_intermediara(nr, int(baza_sursa), int(baza_destinatie)))
        else:
            print("comanda invalida!")
    else:
        print("Nu se poate realiza conversia data!")


def run_conversie_baza_intermediara():
    nr = input("Introduceti numarul pe care doriti sa-l convertiti:")
    baza_sursa = input("Introduceti baza sursa in care este scris numarul dat:")
    baza_destinatie = input("Introduceti baza in care doriti sa convertiti numarul dat:")
    if int(baza_sursa) < 2 or (int(baza_sursa) > 10 and int(baza_sursa) < 16):
        print("Baza sursa introdusa invalida!")
        return
    if int(baza_destinatie) < 2 or (int(baza_destinatie) > 10 and int(baza_destinatie) < 16):
        print("Baza destinatie introdusa invalida!")
        return
    for i in range(0, len(nr)):
        if from_baza16[nr[i]] >= int(baza_sursa):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    print("Numarul dat convertit in baza destinatie este egal cu:")
    print(conversie_baza_intermediara(nr, int(baza_sursa), int(baza_destinatie)))


def run_conversie_substitutie():
    nr = input("Introduceti numarul pe care doriti sa-l convertiti:")
    baza_sursa = input("Introduceti baza sursa in care este scris numarul dat:")
    baza_destinatie = input("Introduceti baza in care doriti sa convertiti numarul dat:")
    if int(baza_sursa) < 2 or (int(baza_sursa) > 10 and int(baza_sursa) < 16):
        print("Baza sursa introdusa invalida!")
        return
    if int(baza_destinatie) < 2 or (int(baza_destinatie) > 10 and int(baza_destinatie) < 16):
        print("Baza destinatie introdusa invalida!")
        return
    for i in range(0, len(nr)):
        if from_baza16[nr[i]] >= int(baza_sursa):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    print("Numarul dat convertit in baza destinatie este egal cu:")
    print(conversie_substitutie(nr, int(baza_sursa), int(baza_destinatie)))


def run_conversie_impartiri_succesive():
    nr = input("Introduceti numarul pe care doriti sa-l convertiti:")
    baza_sursa = input("Introduceti baza sursa in care este scris numarul dat:")
    baza_destinatie = input("Introduceti baza in care doriti sa convertiti numarul dat:")
    if int(baza_sursa) < 2 or (int(baza_sursa) > 10 and int(baza_sursa) < 16):
        print("Baza sursa introdusa invalida!")
        return
    if int(baza_destinatie) < 2 or (int(baza_destinatie) > 10 and int(baza_destinatie) < 16):
        print("Baza destinatie introdusa invalida!")
        return
    for i in range(0, len(nr)):
        if from_baza16[nr[i]] >= int(baza_sursa):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    print("Numarul dat convertit in baza destinatie este egal cu:")
    print(conversie_impartiri_succesive(nr, int(baza_sursa), int(baza_destinatie)))


def run_adunare():
    baza = input("Introduceti baza in care sunt reprezentate numerele date si in care se va efectua adunarea:")
    nr1 = input("Introduceti primul numar:")
    nr2 = input("Introduceti cel de-al doilea numar:")
    for i in range(0, len(nr1)):
        if from_baza16[nr1[i]] >= int(baza):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    for i in range(0, len(nr2)):
        if from_baza16[nr2[i]] >= int(baza):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    print("Rezultatul adunarii celor 2 numere in baza data este:")
    print(adunare_doua_numere(nr1, nr2, int(baza)))


def run_scadere():
    baza = input("Introduceti baza in care sunt reprezentate numerele date si in care se va efectua scaderea:")
    nr1 = input("Introduceti primul numar:")
    nr2 = input("Introduceti cel de-al doilea numar:")
    for i in range(0, len(nr1)):
        if from_baza16[nr1[i]] >= int(baza):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    for i in range(0, len(nr2)):
        if from_baza16[nr2[i]] >= int(baza):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return

    if int(nr1) < int(nr2):
        print("Primul numar este mai mic decat cel de-al doilea, nu se poate efectua scaderea!")
        return

    print("Rezultatul scaderii celui de-al doilea numar din primul in baza data este:")
    print(scadere_doua_numere(nr1, nr2, int(baza)))


def run_inmultire():
    baza = input("Introduceti baza in care vor fi reprezentate numarul si cifra data pentru efectuarea inmultirii:")
    nr = input("Introduceti numarul:")
    cifra = input("Introduceti cifra:")
    for i in range(0, len(nr)):
        if from_baza16[nr[i]] >= int(baza):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    if from_baza16[cifra] >= int(baza):
        print("Cifra nu exista in baza data!")
        return
    print("Rezultatul inmultirii numarului cu cifra data este:")
    print(inmultire_cu_o_cifra(nr, cifra, int(baza)))


def run_impartire():
    baza = input("Introduceti baza in care vor fi reprezentate numarul si cifra data pentru efectuarea impartirii:")
    nr = input("Introduceti numarul:")
    cifra = input("Introduceti cifra:")
    for i in range(0, len(nr)):
        if from_baza16[nr[i]] >= int(baza):
            print("Numarul dat este reprezentat gresit in baza sursa!")
            return
    if from_baza16[cifra] >= int(baza):
        print("Cifra nu exista in baza data!")
        return
    print("Rezultatul impartirii numarului la cifra data este:")
    cat, rest = impartirea_la_o_cifra(nr, cifra, int(baza))
    print(cat, "rest", rest)


def help():
    print("Aplicatia permite conversia numerelor intr-o baza oarecare data(2-10 sau 16) prin urmatoarele metode:")
    print("-Impartiri succesive, substitutie, utilizarea unei baze intermediare(implictit baza 10)")
    print("-Conversii rapide din baza 2 in baza 4,8,16 si invers")
    print(
        "De asemenea, se pot realiza operatiile aritmetice de baza(adunarea a 2 numere, scaderea a 2 numere, inmultirea/impartirea cu o cifra"
        "intr-o baza oarecare data")
    print("Aplicatia dispune de urmatoarele comenzi:")
    print(
        "[converteste_numar] - Se va cere introducerea unui numar, a bazei sursa si a bazei destinatie in care urmeaza sa fie convertit,"
        "iar in functie de datele introduse se va oferi posibilitatea utilizarii metodelor de conversie cele mai potrivite")
    print(
        "[conversie_baza_intermediara] - Se va executa algoritmul de conversie a unui numar utilizand baza intermediara")
    print("[conversie_substitutie] - Se va executa algoritmul de conversie a unui numar prin metoda substitutiei "
          "(se recomanda utilizarea acestei metode in contextul unei conversii de la baza mai mica la baza mai mare")
    print(
        "[conversie_impartiri_succesive] - Se va executa algoritmul de conversie a unui numar prin metoda impartirilor succesive"
        "(se recomanda utilizarea acestei metode in contextul unei conversii de la baza mai mare la baza mai mica")
    print("[adunare] - Se vor aduna 2 numere introduse de utilizator, ambele scrise intr-o baza oarecare p mentionata")
    print("[scadere] - Se vor scade 2 numere introduse de utilizator, ambele scrise intr-o baza oarecare p mentionata")
    print("[inmultire] - Se va inmulti un numar dat intr-o baza p oarecare cu o cifra data")
    print(
        "[impartire] - Se va imparti un numar dat intr-o baza p oarecare la o cifra data si se va afisa catul si restul obtinut")
    print("[exit] - Iesire din aplicatie")


comenzi = {
    "converteste_numar": run_conversie_numar,
    "conversie_baza_intermediara": run_conversie_baza_intermediara,
    "conversie_substitutie": run_conversie_substitutie,
    "conversie_impartiri_succesive": run_conversie_impartiri_succesive,
    "adunare": run_adunare,
    "scadere": run_scadere,
    "inmultire": run_inmultire,
    "impartire": run_impartire
}


def run():
    help()
    while True:
        comanda = input(">>>")
        comanda = comanda.strip()
        if comanda == "":
            continue
        elif comanda == "exit":
            return
        elif comanda in comenzi:
            try:
                comenzi[comanda]()
            except ValueError as ve:
                print(str(ve))
        else:
            print("comanda invalida!")


run()
