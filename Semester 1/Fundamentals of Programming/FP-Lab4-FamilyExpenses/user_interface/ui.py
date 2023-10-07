from domain.cheltuieli import afisare_cheltuiala
from services.servicii_cheltuieli import adaugare_cheltuiala_lista_service, get_numar_cheltuieli_lista, \
    get_cheltuieli_service, actualizare_cheltuiala_service, \
    cheltuieli_mai_mari_decat_suma_service, suma_totala_tip_cheltuiala, determinare_cheltuieli_anumit_tip, \
    filtrare_cheltuieli_anumit_tip_service, sterge_cheltuieli_dupa_zi_service, sterge_cheltuieli_interval_timp_service, \
    sterge_cheltuieli_tip_service, tiparire_cheltuieli_inainte_de_o_zi_mai_mici_decat_suma_service, \
    determinare_zi_suma_maxima_service, tiparire_cheltuieli_anumita_suma_service, \
    afisare_cheltuieli_sortate_criteriu_service, undo_service, afisare_cheltuieli_sortate_tip_service, \
    filtrare_cheltuieli_mai_mici_suma_service, cautare_cheltuiala_id_service
from validations.validare_cheltuiala import valideaza_zi


def printMenu():
    print("Aplicatia urmatoare permite gestionarea cheltuielilor unei familii, pentru fiecare cheltuiala fiind mentionate ziua lunii,")
    print("suma achitata si tipul cheltuielii ( mancare, intretinere, imbracaminte, telefon, altele ).")
    print("Aplicatia permite accesarea urmatoarelor functionalitati:")
    print("  >>>adauga_cheltuiala  [id], [zi] , [suma] , [tip]")
    print("  >>>afiseaza_cheltuieli")
    print("  >>>modifca_cheltuiala [id] , [caracteristica] , [valoare noua]")
    print("  >>>sterge_cheltuieli [zi]")
    print("  >>>afiseaza_cheltuieli_mai_mari [suma minima]")
    print("  >>>afiseaza_suma_totala_tip [tipul cautat]")
    print("  >>>afiseaza_cheltuieli_tip [tipul cautat]")
    print("  >>>filtreaza_cheltuieli_tip [tipul cautat]")
    print("  >>>filtreaza_cheltuieli_mai_mici_suma [suma_max]")
    print("  >>>sterge_cheltuieli_interval [zi_start], [zi final]")
    print("  >>>sterge_cheltuieli_tip [tipul cautat]")
    print("  >>>tipareste_cheltuieli_zi_suma [zi_max], [suma_max]")
    print("  >>>gaseste_zi_suma_maxima")
    print("  >>>tipareste_cheltuieli_anumita_suma [suma]")
    print("  >>>afiseaza_cheltuieli_sortate_criteriu [caracteristica] [criteriu: crescator/descrescator]")
    print("  >>>sorteaza_cheltuieli_tip")
    print("  >>>undo_ultima_operatie")


def ui_adauga_cheltuiala(lista,lista_undo,params):
    if len(params)!=4:
        print("numar parametri invalid!")
        return
    else:
        try:
            id_cheltuiala = int(params[0])
        except ValueError:
            print("id invalid!\n")
            return
        try:
            zi_cheltuiala = int(params[1])
        except ValueError:
            print("zi invalida!\n")
            return
        try:
            suma_cheltuiala = float(params[2])
        except ValueError:
            print("suma invalida!\n")
            return
        tip_cheltuiala = params[3]
        adaugare_cheltuiala_lista_service(lista,lista_undo,id_cheltuiala,zi_cheltuiala,suma_cheltuiala,tip_cheltuiala)
        print("intrare adaugata cu succes!")



def ui_afisare_cheltuieli(lista,lista_undo,params):
    if len(params)!=0:
        print("numar parametri invalid!")
        return
    elif get_numar_cheltuieli_lista(lista)==0:
        print("nu exista cheltuieli adaugate inca!")
        return
    else:
        cheltuieli = get_cheltuieli_service(lista)
        for cheltuiala in cheltuieli:
            print(afisare_cheltuiala(cheltuiala))


def ui_modificare_cheltuiala(lista,lista_undo,params):
    if len(params)!=3:
        print("numar parametri invalid!")
        return
    else:
        id = int(params[0])
        caracteristica = params[1]
        if caracteristica == "id":
                val_noua = int(params[2])
        elif caracteristica == "zi":
            try:
                val_noua = int(params[2])
                valideaza_zi(val_noua)
            except ValueError:
                print("valoare invalida!\n")
                return
        elif caracteristica == "suma":
            val_noua=float(params[2])
        elif caracteristica == "tip":
            val_noua = params[2]
        else:
            print("caracteristica invalida!\n")
            return
        #val_noua = params[2]
        actualizare_cheltuiala_service(lista,lista_undo,id,caracteristica,val_noua)
        #actualizare_cheltuiala_service(lista,params[0]-1,params[1],params[2])


def ui_sterge_cheltuieli_dupa_zi(lista,lista_undo,params):
    if len(params) != 1:
        print("numar parametri invalid!")
        return
    else:
        try:
            zi_stergere = int(params[0])
        except ValueError:
            print("zi invalida!\n")
            return
        sterge_cheltuieli_dupa_zi_service(lista,lista_undo,zi_stergere)
        if len(lista) == 0:
            print("Au fost sterse toate elementele listei!")


def ui_cheltuieli_suma(lista,lista_undo,params):
    if len(params)!=1:
        print("numar parametri invalid!")
        return
    #else:
        #try:
            #suma_min = float(params[0])
            #cheltuieli_mai_mari_decat_suma_service(lista,suma_min)
        #except ValueError:
            #print("suma introdusa este invalida!")
    try:
        suma_min=float(params[0])
    except ValueError:
        print("suma invalida!")
        return
    lista_noua = cheltuieli_mai_mari_decat_suma_service(lista, suma_min)
    #for _cheltuiala in lista_noua:
        #afisare_cheltuiala(_cheltuiala)
    print(lista_noua)


def ui_suma_totala_tip(lista,lista_undo,params):
    if len(params)!=1:
        print("numar parametri invalid!")
        return
    tip = params[0]
    suma_totala = suma_totala_tip_cheltuiala(lista,tip)
    print(suma_totala)


def ui_afisare_cheltuieli_tip(lista,lista_undo,params):
    if len(params)!=1:
        print("numar parametri invalid!")
        return
    tip = params[0]
    lista_noua = determinare_cheltuieli_anumit_tip(lista,tip)
    print(lista_noua)


def ui_filtrare_cheltuieli_tip(lista,lista_undo,params):
    if len(params)!=1:
        print("numar parametri invalid!")
        return
    tip = params[0]
    lista_noua = filtrare_cheltuieli_anumit_tip_service(lista,tip)
    if len(lista_noua)>0:
        print(lista_noua)
    else:
        print("nu au fost efectuate modificari asupra listei!\n")


def ui_sterge_cheltuieli_interval(lista,lista_undo,params):
    if len(params) != 2:
        print("numar parametri invalid!")
        return
    else:
        try:
            zi_start = int(params[0])
        except ValueError:
            print("zi invalida!\n")
            return
        try:
            zi_end = int(params[1])
        except ValueError:
            print("zi invalida!\n")
            return
        sterge_cheltuieli_interval_timp_service(lista,lista_undo,zi_start, zi_end)
        if len(lista) == 0:
            print("Au fost sterse toate elementele listei!")


def ui_sterge_cheltuieli_tip(lista,lista_undo,params):
    if len(params)!=1:
        print("numar parametri invalid!")
        return
    else:
        tip = params[0]
        sterge_cheltuieli_tip_service(lista,lista_undo,tip)
        if len(lista)== 0:
            print("Au fost sterse toate elementele listei!")


def ui_tipareste_cheltuieli_zi_suma(lista,lista_undo,params):
    if len(params)!=2:
        print("numar parametri invalid!")
        return
    else:
        try:
            zi = int(params[0])
        except ValueError:
            print("zi invalida!\n")
            return
        try:
            suma_max = float(params[1])
        except ValueError:
            print("suma maxima invalida!\n")
            return
        lista_noua = tiparire_cheltuieli_inainte_de_o_zi_mai_mici_decat_suma_service(lista,zi,suma_max)
        print(lista_noua)


def ui_determinare_zi_suma_maxima(lista,lista_undo,params):
    if len(params)!=0:
        print("numar parametri invalid!")
        return
    else:
        zi_suma_max = determinare_zi_suma_maxima_service(lista)
        print("Ziua pentru care se obtine suma maxima cheltuita este:")
        print(zi_suma_max)


def ui_tiparire_cheltuieli_anumita_suma(lista,lista_undo,params):
    if len(params)!=1:
        print("numar parametri invalid!")
        return
    else:
        try:
            suma = float(params[0])
        except ValueError:
            print("suma invalida!\n")
            return
        lista_noua = tiparire_cheltuieli_anumita_suma_service(lista,suma)
        if len(lista_noua) == 0:
            print("Nu exista cheltuieli care au valoarea sumei cea introdusa!\n")
        else:
            print(lista_noua)

def ui_afisare_cheltuieli_sortate_criteriu(lista,lista_undo,params):
    if len(params)!=2:
        print("numar parametri invalid!")
        return
    else:
        if len(lista)== 0:
            print("Nu exista intrari adaugate, nu se poate efectua sortarea!")
            return
        caracteristica = params[0]
        criteriu = params[1]
        afisare_cheltuieli_sortate_criteriu_service(lista,caracteristica,criteriu)
        cheltuieli = get_cheltuieli_service(lista)
        for cheltuiala in cheltuieli:
            print(afisare_cheltuiala(cheltuiala))


def ui_sortare_cheltuieli_tip(lista,lista_undo,params):
    if len(params)!=0:
        print("numar parametri invalid!")
        return
    afisare_cheltuieli_sortate_tip_service(lista)
    cheltuieli = get_cheltuieli_service(lista)
    for cheltuiala in cheltuieli:
        print(afisare_cheltuiala(cheltuiala))

def ui_filtrare_cheltuieli_mai_mici_suma(lista,lista_undo,params):
    if len(params)!=1:
        print("numar parametri invalid!")
        return
    try:
        suma_max = float(params[0])
    except ValueError:
        print("suma invalida!\n")
        return
    lista_noua = filtrare_cheltuieli_mai_mici_suma_service(lista,suma_max)
    if len(lista_noua)>0:
        print(lista_noua)
    else:
        print("nu au fost efectuate modificari asupra listei!\n")

def ui_undo(lista,lista_undo,params):
    if len(params)!=0:
        print("numar parametri invalid!")
        return
    undo_service(lista,lista_undo)


def ui_cautare_cheltuiala(lista,lista_undo,params):
    if len(params)!=1:
        print("numar parametri invalid!")
        return
    #try:
    id_cheltuiala = int(params[0])
    #except ValueError:
        #print("id invalid!\n")
        #return
    #cheltuiala_cautata = cautare_cheltuiala_id_service(lista,id_cheltuiala)
    #print(afisare_cheltuiala(cheltuiala_cautata))
    print(cautare_cheltuiala_id_service(lista,id_cheltuiala))

def run_ui():
    #print("Aplicatia urmatoare permite gestionarea cheltuielilor unei familii, pentru fiecare cheltuiala fiind mentionate ziua lunii,")
    #print("suma achitata si tipul cheltuielii ( mancare, intretinere, imbracaminte, telefon, altele ).")
    #print("Aplicatia permite accesarea urmatoarelor functionalitati:")
    cheltuieli = []
    lista_undo = []
    comenzi = {
        "adauga_cheltuiala" : ui_adauga_cheltuiala,                                         # F1
        "afiseaza_cheltuieli" : ui_afisare_cheltuieli,                                      # F3
        "modifica_cheltuiala" : ui_modificare_cheltuiala,                                   # F2
        "sterge_cheltuieli_zi" : ui_sterge_cheltuieli_dupa_zi,                              # F5
        "afiseaza_cheltuieli_mai_mari" : ui_cheltuieli_suma,                                # F8
        "afiseaza_suma_totala_tip" : ui_suma_totala_tip,                                    # F11
        "afiseaza_cheltuieli_tip" : ui_afisare_cheltuieli_tip,                              # F10
        "filtreaza_cheltuieli_tip" : ui_filtrare_cheltuieli_tip,                            # F15
        "sterge_cheltuieli_interval" : ui_sterge_cheltuieli_interval,                       # F6
        "sterge_cheltuieli_tip" : ui_sterge_cheltuieli_tip,                                 # F7
        "tipareste_cheltuieli_zi_suma" : ui_tipareste_cheltuieli_zi_suma,                   # F9
        "gaseste_zi_suma_maxima" : ui_determinare_zi_suma_maxima,                           # F12
        "tipareste_cheltuieli_anumita_suma" : ui_tiparire_cheltuieli_anumita_suma,          # F13
        "afiseaza_cheltuieli_sortate_criteriu" : ui_afisare_cheltuieli_sortate_criteriu,    # F4
        "filtreaza_cheltuieli_mai_mici_suma" : ui_filtrare_cheltuieli_mai_mici_suma,        # F16
        "sorteaza_cheltuieli_tip" : ui_sortare_cheltuieli_tip,                              # F14
        "undo_ultima_operatie" : ui_undo                                                    # F17

    }
    val = True
    while val == True:
        #printMenu()
        comanda = input(">>>")
        comanda = comanda.strip()
        if comanda == "":
            continue
        if comanda == "exit":
            val = False
            return
        parts = comanda.split()
        nume_comanda = parts[0]
        params = parts[1:]
        if nume_comanda in comenzi:
            try:
                comenzi[nume_comanda](cheltuieli,lista_undo,params)
            except ValueError as string_ve:
                print(string_ve)
        else:
            print("Comanda invalida!")


def run_ui_test():
    cheltuieli = []
    lista_undo = []
    lista_comenzi = []
    comenzi = {
        "adauga_cheltuiala": ui_adauga_cheltuiala,  # F1
        "afiseaza_cheltuieli": ui_afisare_cheltuieli,  # F3
        "sterge_cheltuieli_zi": ui_sterge_cheltuieli_dupa_zi,  # F5
        "filtreaza_cheltuieli_tip": ui_filtrare_cheltuieli_tip,  # F15
        "sterge_cheltuieli_tip": ui_sterge_cheltuieli_tip,       #F7
        "cautare_cheltuiala": ui_cautare_cheltuiala

    }
    val = True
    while val == True:
        # printMenu()
        sir_comenzi = input(">>>")
        #sir_comenzi = sir_comenzi.strip()
        if sir_comenzi == "":
            continue
        lista_comenzi_copie = sir_comenzi.split(";")
        #print(sir_comenzi)
        print(lista_comenzi_copie)
        #for i in range(0,len(lista_comenzi_copie)//2):
        for i in range(0,len(lista_comenzi_copie)):
            lista_comenzi = lista_comenzi_copie[i].split()
            #lista_comenzi = sir_comenzi.split(";",1)
            #new_string = string.split(",", 1)[1]
            #sir_comenzi = sir_comenzi.split(";",1)[1]
            #print(lista_comenzi)
            parts = lista_comenzi
            #print(parts)
            nume_comanda = parts[0].strip()
           #print(nume_comanda)
            params = parts[1:]
            #print(params)
            if nume_comanda == "exit":
                val = False
                return
            if nume_comanda in comenzi:
                try:
                    comenzi[nume_comanda](cheltuieli,lista_undo,params)
                except ValueError as string_ve:
                    print(string_ve)
            else:
                print("Comanda invalida!")
            #lista_comenzi_copie.pop(0)
            #lista_comenzi.pop(0)

        """
        if comanda == "exit":
            val = False
            return
        parts = comanda.split()
        nume_comanda = parts[0]
        params = parts[1:]
        if nume_comanda in comenzi:
            try:
                comenzi[nume_comanda](cheltuieli, lista_undo, params)
            except ValueError as string_ve:
                print(string_ve)
        else:
            print("Comanda invalida!")
        """
#elif nume_comanda == "sterge_cheltuieli":
        #    try:
        #        cheltuieli = comenzi[nume_comanda](cheltuieli,params)
                #print(cheltuieli)
        #    except ValueError as string_ve:
        #        print(string_ve)