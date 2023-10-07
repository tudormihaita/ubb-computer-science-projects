from domain.cheltuieli import creeaza_cheltuiala, get_tip, get_suma, get_zi, replace_cheltuiala, get_id
from repos.repository_cheltuieli import adaugare_cheltuiala_lista, actualizare_cheltuiala, get_cheltuieli_lista, \
    sterge_cheltuieli, cautare_cheltuiala_dupa_id
from validations.validare_cheltuiala import valideaza_cheltuiala, valideaza_caracteristica_cheltuiala, \
    valideaza_valoare_noua_cheltuiala, \
    valideaza_zi, valideaza_suma, valideaza_tip_cheltuiala, valideaza_id_cheltuiala, valideaza_criteriu


def adaugare_cheltuiala_lista_service(lista, lista_undo, id_chl, zi_chl, suma_chl, tip_chl):
    """
    creeaza o cheltuiala pe baza zilei lunii, suma achitata si tipul cheltuielii
    incearca sa o valideze, si daca e valida o adauga in lista, insa fara a avea tipuri de cheltuieli identice in aceeasi zi a fiecarei luni
    :param lista: cheltuieli
    :param id_chl: int
    :param zi_chl: int
    :param suma_chl: float
    :param tip_chl: string
    :return: - ( daca cheltuiala este valabila si avem tipuri unice in fiecare zi a lunii )
    :raises: ValueError - daca int-ul id este <0
                        - daca int-ul zi este <=0 sau >31 "zi invalida!\n"
                        - daca float-ul suma <=0 "suma invalida!\n"
                        - daca string-ul tip este vid "tip invalid!\n"
                        - daca string-ul tip nu este vid, dar diferit de lista de tipuri, cheltuiala va fi automat trecuta in tipul "altele"
                        in cazul in care restul parametrilor sunt valizi
        va fi concatenat la string-ul de eroare
    """
    cheltuiala = creeaza_cheltuiala(id_chl,zi_chl,suma_chl,tip_chl)
    valideaza_cheltuiala(cheltuiala)
    adaugare_cheltuiala_lista(lista,cheltuiala)
    lista_undo.append((sterge_cheltuieli, cheltuiala))


def actualizare_cheltuiala_service(lista,lista_undo,id_cheltuiala,caracteristica,val_noua):
    """
    actualizeaza cheltuiala data de tipul cheltuiala din lista de cheltuieli cu o noua valoarea val_noua pentru caracteristica mentionata
    verifica daca cheltuiala pentru care vrem sa facem modificari se afla in lista
    valideaza caracteristica pentru care vrem sa schimbam valoarea
    se asigura ca valaorea noua introdusa este valida pentru caracteristica data
    verifica daca in urma modificarii, nu se va mai pastra unicitatea cheltuielilor prin id
    :param lista: cheltuieli
    :param id_cheltuiala: int
    :param caracteristica: string
    :param val_noua: int/flow/string in functie de caracteristica
    :return: - ( daca actualizarea cheltuielii este valida si a avut loc cu succces)
    :raises: ValueError - cu mesajul "caracteristica invalida!\n" daca caracteristica nou introdusa nu este una specifica cheltuielilor sau
                        se incearca schimbarea id-ului
                        - cu mesajul "valoarea invalida!\n" daca noua valoarea pentru caracteristica nu este valida sau nu este specifica
                        tipului de caracteristica
    """
    valideaza_id_cheltuiala(id_cheltuiala,lista)
    valideaza_caracteristica_cheltuiala(caracteristica)
    valideaza_valoare_noua_cheltuiala(caracteristica,val_noua)
    #if caracteristica == "id":
        #valideaza_cheltuiala_actualizata(lista,id_cheltuiala,caracteristica,val_noua)
    cheltuiala_undo = cautare_cheltuiala_dupa_id(lista,id_cheltuiala)
    cheltuiala_veche = creeaza_cheltuiala(id_cheltuiala,get_zi(cheltuiala_undo),get_suma(cheltuiala_undo),get_tip(cheltuiala_undo))
    #lista_undo.append(("replace_cheltuiala", cautare_cheltuiala_dupa_id(lista, id_cheltuiala),))
    actualizare_cheltuiala(lista,id_cheltuiala,caracteristica,val_noua)
    lista_undo.append((replace_cheltuiala ,cautare_cheltuiala_dupa_id(lista,id_cheltuiala),cheltuiala_veche))
    # adauga in lista_undo cheltuiala inainte de actualizare si trateaza cazul cu id ul schimbat



def afisare_cheltuieli_sortate_criteriu_service(lista,caracteristica,criteriu):
    """
    va afisa lista de cheltuieli ordonata crescator sau descrescator, in functie de criteriul introdus, si dupa caracteristica data
    :param lista: cheltuieli
    :param caracteristica: string
    :param criteriu: string
    :return: - ( se va sorta lista conform criteriului dat si in functie de caracteristica data )
    """
    criteriu = criteriu.strip()
    valideaza_criteriu(criteriu)
    valideaza_caracteristica_cheltuiala(caracteristica)
    #lista_noua = []
    if criteriu == "crescator":
        lista.sort(key=lambda x: x.get(caracteristica), reverse=False)
    elif criteriu == "descrescator":
        lista.sort(key=lambda x: x.get(caracteristica), reverse=True)

def afisare_cheltuieli_sortate_tip_service(lista):
    """
    va sorta cheltuielile alfabetic, in functie de tipul acestora
    :param lista: cheltuieli
    :return: - ( se va sorta lista conform criteriului dat )
    """
    lista.sort(key=lambda x: x.get("tip"), reverse=False)


def sterge_cheltuieli_dupa_zi_service(lista,lista_undo,zi):
    """
    sterge cheltuielile din lista pentru o zi data
    verifica daca ziua introdusa este valida
    si daca exista cheltuieli efectuate in acea zi
    :param lista: cheltuieli
    :param zi: int
    :return: - ( daca ziua este valida si exista cheltuieli efectuate in acea zi)
    """
    valideaza_zi(zi)
    lista_noua = []
    list_of_bool = [True for i in lista if zi == i["zi"]]
    if any(list_of_bool) == False:
        raise ValueError("nu exista cheltuieli efectuate in ziua data!\n")
    for cheltuiala in lista:
        if get_zi(cheltuiala) == zi:
            lista_noua.append(cheltuiala)
    lista[:] = [x for x in lista if not (x["zi"] == zi)]
    lista_undo.append((adaugare_cheltuiala_lista,lista_noua))
    # creeaza lista noua cu cheltuielile cu ziua respectiva si adauga in lista_undo


def sterge_cheltuieli_interval_timp_service(lista,lista_undo,zi_start,zi_end):
    """
    elimina din lista de cheltuieli acele cheltuieli care au fost efectuate intr-un interval de timp dat, specificat prin ziua de inceput si
    cea de sfarsit
    verifica daca zilele introduse pentru inceputul si sfarsitul intervalului sunt valide, cat si daca se efectueaza modificari asupra listei
    in urma stergerii
    :param lista: cheltuieli
    :param zi_start: int
    :param zi_end: int
    :return: - ( se sterg din lista cheltuielile efectuate in intervalul de timp mentionat )
    """
    valideaza_zi(zi_start)
    valideaza_zi(zi_end)
    lista_noua = []
    list_of_bool = [True for i in lista if i["zi"] >= zi_start and i["zi"] <= zi_end]
    if any(list_of_bool) == False:
        raise ValueError("nu exista cheltuieli efectuate in acest interval de timp\n")
    for cheltuiala in lista:
        if get_zi(cheltuiala) >= zi_start and get_zi(cheltuiala) <= zi_end:
            lista_noua.append(cheltuiala)
    lista[:] = [x for x in lista if not (x["zi"] >= zi_start and x["zi"] <= zi_end)]
    lista_undo.append((adaugare_cheltuiala_lista, lista_noua))


def sterge_cheltuieli_tip_service(lista,lista_undo,tip):
    """
    elimina din lista de cheltuieli intrarile existente care au tipul identic cu string-ul tip introdus
    verifica daca tipul cautat este valid si daca exista cel putin o cheltuiala de acest tip care sa fie stearsa
    :param lista: cheltuieli
    :param tip: string
    :return: - ( se sterg din lista acele cheltuieli care au tipul cautat )
    """
    valideaza_tip_cheltuiala(tip)
    lista_noua = []
    list_of_bool = [True for i in lista if i["tip"] == tip ]
    if any(list_of_bool) == False:
        raise ValueError("nu exista cheltuieli de acest tip!\n")
    for cheltuiala in lista:
        if get_tip(cheltuiala) == tip:
            lista_noua.append(cheltuiala)
    lista[:] = [x for x in lista if not ( x["tip"] == tip)]
    lista_undo.append((adaugare_cheltuiala_lista ,lista_noua))


def suma_totala_tip_cheltuiala(lista,tip):
    """
    tipareste suma totala rezultata prin adunarea cheltuielilor de un anumit tip dat de utilizator
    :param lista: cheltuieli
    :param tip: string
    :return: float suma_totala egala cu toate cheltuielile de tipul tip
    """
    valideaza_tip_cheltuiala(tip)
    suma_totala = 0.0
    for _cheltuiala in lista:
        if get_tip(_cheltuiala) == tip:
            suma_totala = suma_totala + get_suma(_cheltuiala)
    if suma_totala == 0:
        raise ValueError("nu exista cheltuieli de acest tip!\n")
    else:
        return suma_totala


def determinare_cheltuieli_anumit_tip(lista,tip):
    """
    tipareste toate cheltuielile de un anumit tip dat de utilizator
    :param lista: cheltuieli
    :param tip: string
    :return: lista_noua, care contine doar cheltuielile de tipul tip
    """
    lista_noua = []
    valideaza_tip_cheltuiala(tip)
    for i in range(0,len(lista)):
        if lista[i]["tip"] == tip:
            lista_noua.append(lista[i])
    if len(lista_noua) == 0:
        raise ValueError("nu exista cheltuieli de acest tip!\n")
    else:
        return lista_noua


def filtrare_cheltuieli_anumit_tip_service(lista,tip):
    """
    filtreaza cheltuielile din lista de string-ul tip cautat si afiseaza restul intrarilor din lista de tipuri diferite
    :param lista: cheltuieli
    :param tip: string
    :return: lista_noua, care contine doar cheltuielile de tipuri diferite fata de cel introdus
    """
    erori = ""
    lista_noua = []
    cheltuieli_filtrate = 0
    valideaza_tip_cheltuiala(tip)
    for i in range(0,len(lista)):
        if lista[i]["tip"] != tip:
            lista_noua.append(lista[i])
        elif lista[i]["tip"] == tip:
            cheltuieli_filtrate = cheltuieli_filtrate + 1
    if cheltuieli_filtrate == 0:
        erori += "nu exista cheltuieli de acest tip!\n"
    #if len(lista_noua) == 0:
        #erori += "nu au fost efectuate modificari asupra listei!\n"
    if len(erori)>0:
        raise ValueError(erori)
    else:
        return lista_noua

def filtrare_cheltuieli_mai_mici_suma_service(lista,suma_max):
    """

    :param lista:
    :param suma_max:
    :return:
    """
    erori = ""
    lista_noua = []
    cheltuieli_filtrate = 0
    valideaza_suma(suma_max)
    for i in range(0, len(lista)):
        if get_suma(lista[i]) >= suma_max:
            lista_noua.append(lista[i])
        elif get_suma(lista[i]) < suma_max:
            cheltuieli_filtrate = cheltuieli_filtrate + 1
    if cheltuieli_filtrate == 0:
        erori += "nu exista cheltuieli cu suma mai mica decat cea data!\n"
    # if len(lista_noua) == 0:
    # erori += "nu au fost efectuate modificari asupra listei!\n"
    if len(erori) > 0:
        raise ValueError(erori)
    else:
        return lista_noua

def cheltuieli_mai_mari_decat_suma_service(lista,suma_min):
    """
    tipareste toate cheltuielile mai mari decat o suma data
    :param lista: cheltuieli
    :param suma_min: float
    :return: lista_noua, care contine doar cheltuielile mai mari decat float-ul suma_min introdus
    """
    #cheltuieli_mai_mari_decat_suma(lista,suma_min)
    #if not(suma_min<=0 or abs(suma_min-float(suma_min))<0.0001):
        #raise ValueError("suma introdusa nu este valida!\n")
    valideaza_suma(suma_min)
    lista_noua = []
    for i in range(0, len(lista)):
        if lista[i]["suma"] > suma_min:
            lista_noua.append(lista[i])
    if len(lista_noua) == 0:
        raise ValueError("nu exista cheltuieli de valori mai mari decat suma data!")
    else:
        return lista_noua
        #for _cheltuiala in lista_noua:
                #afisare_cheltuiala(_cheltuiala)

def tiparire_cheltuieli_inainte_de_o_zi_mai_mici_decat_suma_service(lista,zi,suma_max):
    """
    tipareste cheltuielile din lista care au fost efectuate inainte de o zi data si cu o valoare mai mica decat o suma maxima
    verifica daca valorile introduse pentru zi si suma sunt valide
    :param lista: cheltuieli
    :param zi: int
    :param suma_max: float
    :return: lista_noua, care contine cheltuielile cautate
    """
    valideaza_zi(zi)
    valideaza_suma(suma_max)
    lista_noua = []
    for i in range(0,len(lista)):
        if lista[i]["zi"] < zi and lista[i]["suma"] < suma_max :
            lista_noua.append(lista[i])
    if len(lista_noua) == 0:
        raise ValueError("nu exista cheltuieli efectuate inainte de ziua data si cu o valoarea mai mica decat suma data!")
    else:
        return lista_noua


def determinare_zi_suma_maxima_service(lista):
    """
    calculeaza suma tuturor cheltuielilor pentru fiecare zi si determina ziua in care suma cheltuita este maxima
    :param lista: cheltuieli
    :return: int-ul zi_suma_max, care are valoarea zilei in care suma cheltuielilor este maxima
    """
    if len(lista)==0:
        raise ValueError("Nu exista cheltuieli in lista!\n")

    lista_sume_zile = [0] * 31
    for cheltuiala in lista:
        zi_cautata = get_zi(cheltuiala)
        lista_sume_zile[zi_cautata-1] = lista_sume_zile[zi_cautata-1] + get_suma(cheltuiala)
    suma_max = 0.0
    zi_suma_max = -1
    for i in range(0,len(lista_sume_zile)):
        if lista_sume_zile[i] > suma_max:
            suma_max = lista_sume_zile[i]
            zi_suma_max = i + 1

    return zi_suma_max


def tiparire_cheltuieli_anumita_suma_service(lista,suma):
    """
    tipareste toate cheltuielile din lista care au suma egala cu cea introdusa
    :param lista: cheltuieli
    :param suma: float
    :return: lista_noua, in care se regasesc doar cheltuielile cu suma specificata
    """
    valideaza_suma(suma)
    lista_noua = []
    for cheltuiala in lista:
        if abs(cheltuiala["suma"]-suma)<0.0001:
            lista_noua.append(cheltuiala)
    return lista_noua


def get_numar_cheltuieli_lista(lista):
    """
    preia numarul de cheltuieli adaugate pana in momentul actual in lista de cheltuieli de familie
    :param lista: lista de cheltuieli de tipurile "mancare" , "intretinere" , "telefon" , "imbracaminte" , "altele" , unic definite pentru
    o anumita zi a lunii
    :return: rezultatul: int - numarul de cheltuieli din lista denumita lista
    """
    return len(lista)

def get_cheltuieli_service(lista):
    return get_cheltuieli_lista(lista)

def undo_service(lista,lista_undo):
    if len(lista_undo)==0:
        raise ValueError("Nu se mai poate efectua operatia de undo!\n")
    op = lista_undo.pop()
    if type(op[1]) == list:
        for i in range(0,len(op[1])):
            op[0](lista,op[1][i])
    elif len(op)==3:
        op[0](lista,op[1],op[2])
    else:
        op[0](lista,op[1])

def cautare_cheltuiala_id_service(lista,id_cheltuiala):
    """

    :param lista:
    :param id_cheltuiala:
    :return:
    """
    #valideaza_id_cheltuiala(id_cheltuiala,lista)
    #cautare_cheltuiala_dupa_id(lista,id_cheltuiala)
    for cheltuiala in lista:
        if get_id(cheltuiala) == id_cheltuiala:
            return cheltuiala