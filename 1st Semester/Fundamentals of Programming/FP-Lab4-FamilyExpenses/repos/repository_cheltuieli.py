from domain.cheltuieli import cheltuieli_identice, get_id


def adaugare_cheltuiala_lista(lista,cheltuiala):
    """
    adauga cheltuiala de tip cheltuiala in lista de cheltuieli, cu restrictia ca fiecare cheltuiala trebuie sa aiba un id unic
    :param lista: lista de cheltuieli de tipurile "mancare" , "intretinere" , "telefon" , "imbracaminte" , "altele" , unic definite pentru
    o anumita zi a lunii
    :param cheltuiala: cheltuiala
    :return: - ( daca cheltuiala introdusa nu are ziua si tipul egale deja cu o cheltuiala adaugata anterior )
    :raises: ValueError - cu mesajul "cheltuiala invalida!\n" daca ziua si tipul cheltuielii introduse sunt egale cu o alta cheltuiala din lista
    """
    for _cheltuiala in lista:
        if cheltuieli_identice(_cheltuiala,cheltuiala)==True:
            raise ValueError("cheltuiala invalida!\n")
    lista.append(cheltuiala)

# incearca sa returnezi cheltuiala efectiva, nu index-ul! verifica daca dupa modificare merge actualizarea din repos + teste ( singurele locuri in care
# folosesc functia asta)
# modifica cu return cheltuiala cautata dupa id, si foloseste la crearea tuplului adaugat in stiva de undo
def cautare_cheltuiala_dupa_id(lista,id_cheltuiala):
    """
    returneaza cheltuiala din lista de cheltuieli care are id-ul respectiv
    :param lista: cheltuieli
    :param id_cheltuiala: int
    :return: rezultatul: int index, pozitia din lista pe care se afla cheltuiala cautata
    """
    gasit=False
    for index in range(0,len(lista)):
        if id_cheltuiala == get_id(lista[index]):
            gasit = True
            return lista[index]
    if gasit == False:
        raise ValueError("nu exista cheltuiala introdusa!\n")


def actualizare_cheltuiala(lista,id_cheltuiala,caracteristica,val_noua):
    """
    actualizeaza o cheltuiala deja introdusa in lista prin specificarea caracteristicii asupra careia vrem sa facem modificari si a noii valori
    pe care o va lua caracteristica, corespunzatoare tipului de data a variabilei
    :param lista: cheltuieli
    :param id_cheltuiala: int
    :param caracteristica: string-ul corespunzator caracteristicii cheltuielii respective
    :param val_noua: noua valoare pe care o va lua caracteristica, in functie de tipul acesteia
    :return: - ( caracteristica cheltuielii introduse va fi modifica cu noua valoare )
    """
    #if index >=0 and index <= len(lista):
    cautare_cheltuiala_dupa_id(lista,id_cheltuiala)[caracteristica] = val_noua
    #pun in lista_undo o copie a intregii cheltuieli dinainte de modificare si o schimb, fara sa fie nevoie sa retin doar caracteristica
    #la care am facut schimbari


#def stergere_cheltuieli_zi(lista,zi): #PUNE SI PARTEA ASTA DE INSTRUCTIUNI IN SERVICE // MODIFICAT COMPLET, FARA CRITERIU DE STERGERE
#    """
#    sterge cheltuielile de toate tipurile din lista care au fost efectuate intr-o zi data
#    :param lista: cheltuieli
#    :param zi: int
#    :return: - ( daca ziua introdusa este valida si exista cheltuieli efectuate in acea zi )
#    """
#    # cheltuieli = [i for i in cheltuieli if not (i['zi'] == rzi)]
#    list_of_bool = [True for i in lista if zi == i["zi"]]
#    if any(list_of_bool)==False:
#        raise ValueError("nu exista cheltuieli efectuate in ziua data!\n")
#    #lista_noua =[ i for i in lista if i["zi"] != zi]
#    lista_noua = []
#    for x in lista:
#       if x['zi'] != zi:
#            lista_noua.append(x)
#    #lista_noua = list(filter(lambda i: i['zi'] != zi, lista))
#   lista = lista_noua
#   return lista
#    #print(lista)
#    #lista creata este buna, insa se pierd valorile la apelul in functia din services

def sterge_cheltuieli(lista,cheltuiala):
    """
    elimina din lista de cheltuiala o cheltuiala introdusa
    :param lista: cheltuieli
    :param cheltuiala: cheltuiala
    :return: - ( se elimina din lista cheltuiala data ca parametru )
    """
    #lista.pop()
    lista[:] = [x for x in lista if not (x == cheltuiala)]


def numar_cheltuieli_lista(lista):
    """
    preia numarul de cheltuieli adaugate pana in momentul actual in lista de cheltuieli de familie
    :param lista: lista de cheltuieli de tipurile "mancare" , "intretinere" , "telefon" , "imbracaminte" , "altele" , unic definite pentru
    o anumita zi a lunii
    :return: rezultatul: int - numarul de cheltuieli din lista denumita lista
    """
    return len(lista)

def get_cheltuieli_lista(lista):
    """
    afiseaza cheltuielile introduse in lista de cheltuieli pana in momentul actual
    :param lista: cheltuieli
    :return: lista de cheltuieli
    """
    return lista[:]

def get_index_cheltuiala(lista,cheltuiala): #MUTA IN DOMAIN(??)
    """
    returneaza int-ul index al intrarii de tip cheltuiala din lista de cheltuieli, in cazul in care aceasta exista
    :param lista: cheltuieli
    :param cheltuiala: cheltuiala
    :return: int index al cheltuielii cautate
    :raises: ValueError - cu mesajul "cheltuiala inexistenta!\n" daca cheltuiala introdusa nu exista in lista
    """
    if cheltuiala not in lista:
        raise ValueError("cheltuiala inexistenta!\n")
    else:
        for index in range(0,len(lista)):
            if lista[index] == cheltuiala:
                return index