def creeaza_cheltuiala(id_cheltuiala,zi_cheltuiala,suma_cheltuiala,tip_cheltuaila):
    """
    creeaza o intrare de tip cheltuiala cu ziua in care a fost efectuata int zi_chl, valoarea cheltuielii float suma_chl si tipul
    cheltuielii string tip_chl
    :param zi_cheltuiala: int
    :param suma_cheltuiala: float
    :param tip_cheltuaila: string
    :return: rezultatul: o cheltuiala cu ziua efectuarii int zi_chl, valoarea float suma_chl si tipul string tip_chl
    """
    return {
        "id" : id_cheltuiala,
        "zi" : zi_cheltuiala,
        "suma" : suma_cheltuiala,
        "tip" : tip_cheltuaila
    }

def get_id(cheltuiala):
    """
    returneaza int-ul id alocat cheltuielii
    :param cheltuiala: cheltuiala
    :return: rezultatul: int - id-ul cheltuielii
    """
    return cheltuiala["id"]

def get_zi(cheltuiala):
    """
    returneaza int-ul zi in care a fost efectuala cheltuiala
    :param cheltuiala: cheltuiala
    :return: rezultatul: int - ziua in care a fost efectuala cheltuiala data
    """
    return cheltuiala["zi"]

def get_suma(cheltuiala):
    """
    returneaza float-ul suma egal cu valoarea cheltuielii respective
    :param cheltuiala: cheltuiala
    :return: rezultatul: float - suma egala cu valoarea cheltuielii date
    """
    return cheltuiala["suma"]

def get_tip(cheltuiala):
    """
    returneaza string-ul tip care specifica scopul cheltuielii
    :param cheltuiala: cheltuiala
    :return: rezultatul: string-ul tip al cheltuielii date
    """
    return cheltuiala["tip"]

def set_zi(cheltuiala,zi_noua):
    """
    seteaza ziua int a cheltuielii cheltuiala la valoarea zi_noua
    :param cheltuiala: cheltuiala
    :param zi_noua : int
    :return: - ( noua zi a cheltuielii este setata la zi_noua )
    """
    cheltuiala["zi"] = zi_noua


def set_suma(cheltuiala,suma_noua):
    """
    seteaza suma float a cheltuielii cheltuiala la valoarea suma_noua
    :param cheltuiala: cheltuiala
    :param suma_noua: float
    :return: - ( noua suma a cheltuielii este setata la suma_noua )
    """
    cheltuiala["suma"] = suma_noua


def set_tip(cheltuiala,tip_nou):
    """
    seteaza tipul string al cheltuielii la string-ul tip_nou
    :param cheltuiala: cheltuiala
    :param tip_nou: string
    :return: - ( noul tip al cheltuielii este setat la tip_nou )
    """
    cheltuiala["tip"] = tip_nou

def cheltuieli_identice(cheltuiala_1,cheltuiala_2):
    """
    verifica daca 2 cheltuieli au id-uri egale, ceea ce inseamna ca cele doua cheltuieli sunt identice
    :param cheltuiala_1: cheltuiala
    :param cheltuiala_2: cheltuiala
    :return: rezultatul: bool - True, daca cheltuielile introduse au acelasi id
                              - False, altfel
    """
    if get_id(cheltuiala_1) == get_id(cheltuiala_2):
        return True
    else:
        return False


def get_cheltuiala(lista,index):
    """
    preia din lista de cheltuieli cheltuiala cautata in functie de index
    :param lista: cheltuieli
    :param index: int
    :return: cheltuiala
    """
    return lista[index]

def replace_cheltuiala(lista,cheltuiala,cheltuiala_noua):
    """

    :param lista:
    :param cheltuiala:
    :param cheltuiala_noua:
    :return:
    """
    #for _cheltuiala in lista:
        #if _cheltuiala == cheltuiala:
            #_cheltuiala = cheltuiala_noua
    cheltuiala.clear()
    cheltuiala.update(cheltuiala_noua)
def afisare_cheltuiala(cheltuiala):
    return f"[{get_id(cheltuiala)}]{get_zi(cheltuiala)} - {get_suma(cheltuiala)} : {get_tip(cheltuiala)}"
