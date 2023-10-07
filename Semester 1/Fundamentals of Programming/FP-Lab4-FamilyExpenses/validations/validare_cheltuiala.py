from domain.cheltuieli import get_zi, get_suma, get_tip, set_tip, get_id


def valideaza_cheltuiala(cheltuiala):
    """
    verifica daca int-ul id este >=0
    int-ul zi este >0 si <=31
    float-ul suma este > 0.0
    si string-ul tip nu e vid si apartine listei de tipuri de cheltuieli posibile
    :param cheltuiala: cheltuiala
    :return: - ( daca datele cheltuielii sunt valide )
    :raises ValueError: - daca int-ul zi este <=0 sau >31 "zi invalida!\n"
                        - daca float-ul suma <=0 "suma invalida!\n"
                        - daca string-ul tip este vid "tip invalid!\n"
                        - daca string-ul tip nu este vid, dar diferit de lista de tipuri, cheltuiala va fi automat trecuta in tipul "altele"
                        in cazul in care restul parametrilor sunt valizi
        va fi concatenat la string-ul de eroare
    """
    tipuri_cheltuieli = [ "mancare", "intretinere", "imbracamine", "telefon" , "altele"]
    erori = ""
    if get_id(cheltuiala) < 0:
        erori+= "id invalid!\n"
    if get_zi(cheltuiala)<=0 or get_zi(cheltuiala)>31 or get_zi(cheltuiala) != int(get_zi(cheltuiala)):
        erori += "zi invalida!\n"
    if get_suma(cheltuiala)<=0 or abs(float(get_suma(cheltuiala))-get_suma(cheltuiala))>0.0001:
        erori += "suma invalida!\n"
    if get_tip(cheltuiala) == "" or get_tip(cheltuiala) != str(get_tip(cheltuiala)) or get_tip(cheltuiala).isnumeric()==True:
        erori += "tip invalid!\n"
    if get_zi(cheltuiala)>0 and get_zi(cheltuiala)<=31 and get_zi(cheltuiala) == int(get_zi(cheltuiala)) and get_suma(cheltuiala)>0.0 and abs(float(get_suma(cheltuiala))-get_suma(cheltuiala))<0.0001 and get_tip(cheltuiala)!="" and get_tip(cheltuiala) == str(get_tip(cheltuiala)) and get_tip(cheltuiala) not in tipuri_cheltuieli:
        set_tip(cheltuiala,"altele")
    if len(erori)>0:
        raise ValueError(erori)


def valideaza_caracteristica_cheltuiala(caracteristica):
            """
            verifica daca string-ul caracteritstica este unul valid, "zi" , "suma" sau "tip"
            :param caracteristica: string
            :return: - ( daca caracteristica cheltuielii este valida )
            :raises: ValueError - cu mesajul "caracteristica invalida!\n" daca string-ul caracteristica nu este "zi" , "suma" sau "tip"
                                - cu mesajul "caracteristica invalida!\n" daca string-ul este vid
            """
            caracteristici_cheltuieli = ["zi", "suma", "tip"]
            #tipuri_cheltuieli = ["mancare", "intretinere", "imbracamine", "telefon" , "altele"]
            if caracteristica not in caracteristici_cheltuieli or caracteristica == "":
                raise ValueError("caracteristica invalida!\n")


def valideaza_valoare_noua_cheltuiala(caracteristica,val_noua):
    """
    verifica daca noua valoare introdusa pentru caracteristica cheltuielii pe care vrem sa o actualizam este valida
    :param caracteristica:string
    :param val_noua: int/flow/string in functie de tipul de caracteristica
    :return: - ( daca valoarea noua pentru caracteristica este valida )
    """
    tipuri_cheltuieli = ["mancare", "intretinere", "imbracamine", "telefon" , "altele"]
    if caracteristica == "id":
        if val_noua != int(val_noua) or val_noua < 0:
            raise ValueError("id invalid!\n")
    if caracteristica == "zi":
        if val_noua != int(val_noua) or (val_noua<=0 and val_noua>31):
            raise ValueError("valoare invalida!\n")
    elif caracteristica == "suma":
        if abs(val_noua-float(val_noua))>0.0001 or val_noua<=0:
            raise ValueError("valoare invalida!\n")
    elif caracteristica == "tip":
        if val_noua not in tipuri_cheltuieli or val_noua=="":
            raise ValueError("valoare invalida!\n")


def valideaza_id_cheltuiala(id_cheltuiala: object, lista: object) -> object:
    """
    verifica daca id-ul introdus corespunde unei cheltuieli din lista
    :param id_cheltuiala: int
    :param lista: cheltuieli
    :return: - ( daca id-ul este valid )
    :raises: ValueError - cu mesajul "id cheltuiala invalid!\n" daca id-ul introdus nu se regaseste in lista
    """
    valid = False
    for i in range(0,len(lista)):
        if lista[i]["id"] == id_cheltuiala:
            valid = True
    if valid == False:
        raise ValueError("id invalid!\n")


def valideaza_cheltuiala_actualizata(lista,id_cheltuiala,caracteristica,val_noua):
    """
    verifica daca dupa actualizarea cheltuielii date, se respecta regula ca fiecare cheltuiala sa aiba id unic
    :param lista: cheltuieli
    :param id_cheltuiala: int
    :param caracteristica: string
    :param val_noua: int/flow/string
    :return: - ( daca cheltuiala actualizata indeplineste toate conditiile de existenta )
    """
    #index = cautare_cheltuiala_dupa_id(lista,id_cheltuiala)
    #copie_lista = lista
    #actualizare_cheltuiala(lista,id_cheltuiala,caracteristica,val_noua)
    #cheltuiala = get_cheltuiala(lista,index)
    #valideaza_cheltuiala(cheltuiala)
    #adaugare_cheltuiala_lista(lista,cheltuiala)
    for i in range(0,len(lista)):
            if lista[i]["id"] == val_noua:
                raise ValueError("cheltuiala invalida!\n")


def valideaza_zi(zi):
    """
    verifica daca int-ul ziua introdusa pentru stergerea cheltuielilor efectuate atunci este valid
    :param zi: int
    :return: - ( daca int-ul ziua este valid )
    """
    if zi<=0 or zi>31 or zi != int(zi):
        raise ValueError("zi invalida!\n")


def valideaza_suma(suma):
    if suma<=0:
        raise ValueError("suma invalida!\n")

def valideaza_criteriu(criteriu):
    if criteriu != "crescator" and criteriu != "descrescator":
        raise ValueError("criteriu invalid!\n")


def valideaza_tip_cheltuiala(tip):
    """
    verifica daca tipul de cheltuiala introdus este valid
    :param tip: string
    :return: - ( daca tipul de cheltuiala este valid )
    """
    tipuri_cheltuieli = ["mancare", "intretinere", "imbracaminte", "telefon", "altele"]
    if tip not in tipuri_cheltuieli:
        raise ValueError("tip invalid!\n")


def valideaza_lista_noua(lista_noua):
    if len(lista_noua) ==0:
        raise ValueError("nu au fost efectuate modificari asupra listei!\n")