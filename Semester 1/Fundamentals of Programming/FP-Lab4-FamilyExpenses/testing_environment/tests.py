from domain.cheltuieli import creeaza_cheltuiala, get_zi, get_suma, get_tip, get_id
from repos.repository_cheltuieli import adaugare_cheltuiala_lista, numar_cheltuieli_lista, \
    actualizare_cheltuiala, cautare_cheltuiala_dupa_id
from services.servicii_cheltuieli import get_numar_cheltuieli_lista, adaugare_cheltuiala_lista_service, \
    actualizare_cheltuiala_service, \
    cheltuieli_mai_mari_decat_suma_service, suma_totala_tip_cheltuiala, \
    determinare_cheltuieli_anumit_tip, filtrare_cheltuieli_anumit_tip_service, sterge_cheltuieli_dupa_zi_service, \
    sterge_cheltuieli_interval_timp_service, sterge_cheltuieli_tip_service, \
    tiparire_cheltuieli_inainte_de_o_zi_mai_mici_decat_suma_service, determinare_zi_suma_maxima_service, \
    tiparire_cheltuieli_anumita_suma_service, afisare_cheltuieli_sortate_criteriu_service, undo_service, \
    filtrare_cheltuieli_mai_mici_suma_service, afisare_cheltuieli_sortate_tip_service
from validations.validare_cheltuiala import valideaza_cheltuiala


def run_teste_creare_cheltuieli():
    id_chl = 31
    zi_chl = 21
    suma_chl = 124.89
    tip_chl = "intretinere"
    cheltuiala = creeaza_cheltuiala(id_chl,zi_chl,suma_chl,tip_chl)
    assert(id_chl == get_id(cheltuiala))
    assert(zi_chl == get_zi(cheltuiala))
    assert(abs(suma_chl - get_suma(cheltuiala))<0.00001)
    assert(tip_chl == get_tip(cheltuiala))

def run_teste_validare_cheltuieli():
    id_chl = 19
    zi_chl =  27
    suma_chl = 789.87
    tip_chl = "telefon"
    cheltuiala = creeaza_cheltuiala(id_chl,zi_chl,suma_chl,tip_chl)
    valideaza_cheltuiala(cheltuiala)

    id_chl_gresita = -45
    zi_chl_gresita = 36
    suma_chl_gresita = 0.0
    tip_chl_gresita = ""
    cheltuiala_gresita = creeaza_cheltuiala(id_chl_gresita,zi_chl_gresita,suma_chl_gresita,tip_chl_gresita)
    try:
        valideaza_cheltuiala(cheltuiala_gresita)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "id invalid!\nzi invalida!\nsuma invalida!\ntip invalid!\n")

    id_chl_valida = 21
    zi_chl_valida = 8
    suma_chl_valida = 80.56
    tip_chl_negasita = "chirie"
    cheltuiala_noua = creeaza_cheltuiala(id_chl_valida,zi_chl_valida,suma_chl_valida,tip_chl_negasita)
    valideaza_cheltuiala(cheltuiala_noua)

    id_chl_ok = 101
    zi_chl_ok = 14
    suma_chl_invalida = -19.8
    tip_chl_ok = "altele"
    cheltuiala_invalida = creeaza_cheltuiala(id_chl_ok,zi_chl_ok,suma_chl_invalida,tip_chl_ok)
    try:
        valideaza_cheltuiala(cheltuiala_invalida)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve)=="suma invalida!\n")


def run_teste_repos_cheltuieli():
    cheltuieli = []
    id_chl = 87
    zi_chl = 14
    suma_chl = 190.87
    tip_chl = "imbracaminte"
    cheltuiala = creeaza_cheltuiala(id_chl,zi_chl,suma_chl,tip_chl)
    assert(numar_cheltuieli_lista(cheltuieli) == 0)
    adaugare_cheltuiala_lista(cheltuieli,cheltuiala)
    assert(numar_cheltuieli_lista(cheltuieli) == 1)

    id_chl_identica = 87
    zi_chl_identica = 14
    suma_chl_identica = 89.657
    tip_chl_identica = "imbracaminte"
    cheltuiala_identica = creeaza_cheltuiala(id_chl_identica,zi_chl_identica,suma_chl_identica,tip_chl_identica)
    try:
        adaugare_cheltuiala_lista(cheltuieli,cheltuiala_identica)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "cheltuiala invalida!\n")


    id_chl_2 = 47
    zi_chl_2 = 19
    suma_chl_2 = 458.541
    tip_chl_2 = "intretinere"
    cheltuiala_2 = creeaza_cheltuiala(id_chl_2,zi_chl_2,suma_chl_2,tip_chl_2)
    adaugare_cheltuiala_lista(cheltuieli,cheltuiala_2)
    assert(numar_cheltuieli_lista(cheltuieli) == 2)


    id_chl_actualizare = 49
    zi_chl_actualizare = 30
    suma_chl_actualizare = 45.209
    tip_chl_actualizare = "mancare"
    id = 49
    cheltuiala_actualizare = creeaza_cheltuiala(id_chl_actualizare,zi_chl_actualizare,suma_chl_actualizare,tip_chl_actualizare)
    adaugare_cheltuiala_lista(cheltuieli,cheltuiala_actualizare)
    actualizare_cheltuiala(cheltuieli, id, "zi", 27)
    assert(get_zi(cheltuiala_actualizare) == 27 )



def run_teste_service_cheltuieli():
    cheltuieli =[]
    lista_undo = []
    id_chl = 38
    zi_chl = 17
    suma_chl = 196.894
    tip_chl = "mancare"
    #cheltuiala = creeaza_cheltuiala(zi_chl,suma_chl,tip_chl)
    assert(numar_cheltuieli_lista(cheltuieli) == 0)
    assert(get_numar_cheltuieli_lista(cheltuieli) == 0)
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl,zi_chl,suma_chl,tip_chl)
    assert (numar_cheltuieli_lista(cheltuieli) == 1)
    assert (get_numar_cheltuieli_lista(cheltuieli) == 1)
    #assert(get_index_cheltuiala(cheltuieli,cheltuiala) == 0)

    id_chl_identica = 38
    zi_chl_identica = 17
    suma_chl_identica = 56.982
    tip_chl_identica = "mancare"
    #cheltuiala_identica = creeaza_cheltuiala(zi_chl_identica,suma_chl_identica,tip_chl_identica)
    try:
        adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_identica,zi_chl_identica,suma_chl_identica,tip_chl_identica)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve)=="cheltuiala invalida!\n")

    id_chl_invalida = 19
    zi_chl_invalida = 30.9
    suma_chl_invalida = -12
    tip_chl_invalida = "cumparaturi"
    try:
        adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_invalida,zi_chl_invalida,suma_chl_invalida,tip_chl_invalida)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve)=="zi invalida!\nsuma invalida!\n")

    id_chl_actualizare = 16
    zi_chl_actualizare = 14
    suma_chl_actualizare = 135.89
    tip_chl_actualizare = "intretinere"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_actualizare,zi_chl_actualizare,suma_chl_actualizare,tip_chl_actualizare)
    assert(numar_cheltuieli_lista(cheltuieli)==2)
    #index_cheltuiala_actualizare = 2
    id_cheltuiala_actualizare = 16
    caractersitica_actualizare = "zi"
    valoare_noua_actualizare = 18
    actualizare_cheltuiala_service(cheltuieli,lista_undo,id_cheltuiala_actualizare,caractersitica_actualizare,valoare_noua_actualizare)
    #assert(get_zi(get_cheltuiala(cheltuieli,cautare_cheltuiala_dupa_id(cheltuieli,id_cheltuiala_actualizare))) == 18 )
    assert(get_zi(cautare_cheltuiala_dupa_id(cheltuieli,id_cheltuiala_actualizare))== 18)


    #index_cheltuiala_actualizare_gresita = 3
    id_cheltuiala_actualizare_gresit = 5
    caracteristica_actualizare_gresita = "suma"
    valoare_noua_actualizare_gresita = 129.453
    try:
        actualizare_cheltuiala_service(cheltuieli,lista_undo,id_cheltuiala_actualizare_gresit,caracteristica_actualizare_gresita,valoare_noua_actualizare_gresita)
        #valideaza_index_cheltuiala(index_cheltuiala_actualizare_gresita,cheltuieli)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "id invalid!\n")

    #index_cheltuiala_actualizare_valida = 1
    id_cheltuiala_actualizare_valida = 38
    caracteristica_actualizare_valida = "tip"
    valoare_noua_actualizare_valida = "intretinere"
    actualizare_cheltuiala_service(cheltuieli,lista_undo,id_cheltuiala_actualizare_valida,caracteristica_actualizare_valida,valoare_noua_actualizare_valida)
    #assert(get_tip(get_cheltuiala(cheltuieli,cautare_cheltuiala_dupa_id(cheltuieli,id_cheltuiala_actualizare_valida))) == "intretinere")
    assert(get_tip(cautare_cheltuiala_dupa_id(cheltuieli,id_cheltuiala_actualizare_valida)) == "intretinere")

    #index_cheltuiala_actualizare_existenta = 2
    id_cheltuiala_actualizare_existenta = 38
    caractersitica_actualizare_existenta = "id"
    valoare_noua_actualizare_existenta = 16
    try:
        actualizare_cheltuiala_service(cheltuieli,lista_undo,id_cheltuiala_actualizare_existenta,caractersitica_actualizare_existenta,valoare_noua_actualizare_existenta)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "caracteristica invalida!\n")

    id_chl_test2 = 94
    zi_chl_test2 = 31
    suma_chl_test2 = 560.876
    tip_chel_test2 = "altele"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_test2,zi_chl_test2,suma_chl_test2,tip_chel_test2)

    #index_chl_test2 = 3
    id_chl_test2_gresita = 38
    caracteristica_chl_test2_gresita = "cod"
    valoare_noua_chl_test2 = "altele"
    try:
        actualizare_cheltuiala_service(cheltuieli,lista_undo,id_chl_test2_gresita,caracteristica_chl_test2_gresita,valoare_noua_chl_test2)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "caracteristica invalida!\n")

    #index_chl_test3 = 3
    id_chl_test3 = 38
    caracteristica_chl_test3 = "suma"
    valoare_noua_chl_test3_gresita = -120
    try:
        actualizare_cheltuiala_service(cheltuieli,lista_undo,id_chl_test3,caracteristica_chl_test3,valoare_noua_chl_test3_gresita)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "valoare invalida!\n")


def run_teste_stergeri_cheltuieli():
    """
    cheltuieli = []
    id_chl = 4
    zi_chl = 13
    suma_chl = 123.232
    tip_chl = "mancare"
    adaugare_cheltuiala_lista_service(cheltuieli,id_chl,zi_chl,suma_chl,tip_chl)
    id_chl_2 = 9
    zi_chl_2 = 13
    suma_chl_2 = 433.329
    tip_chl_2 = "intretinere"
    adaugare_cheltuiala_lista_service(cheltuieli,id_chl_2,zi_chl_2,suma_chl_2,tip_chl_2)
    id_chl_3 = 76
    zi_chl_3 = 22
    suma_chl_3 = 78.630
    tip_chl_3 = "telefon"
    adaugare_cheltuiala_lista_service(cheltuieli,id_chl_3,zi_chl_3,suma_chl_3,tip_chl_3)
    zi_stergere = 13
    cheltuieli_actualizate = sterge_cheltuieli_dupa_zi_service(cheltuieli,zi_stergere)
    assert(numar_cheltuieli_lista(cheltuieli_actualizate) == 1)
    """
    cheltuieli = []
    lista_undo = []
    id_chl = 12
    zi_chl = 19
    suma_chl = 232.22
    tip_chl = "mancare"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl,zi_chl,suma_chl,tip_chl)

    id_chl_2 = 28
    zi_chl_2 = 27
    suma_chl_2 = 54.343
    tip_chl_2 = "altele"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_2,zi_chl_2,suma_chl_2,tip_chl_2)

    id_chl_3 = 91
    zi_chl_3 = 19
    suma_chl_3 = 892.232
    tip_chl_3 = "intretinere"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_3,zi_chl_3,suma_chl_3,tip_chl_3)

    #print(lista_undo)
    zi_stergere = 19
    sterge_cheltuieli_dupa_zi_service(cheltuieli,lista_undo,zi_stergere)
    assert(numar_cheltuieli_lista(cheltuieli) == 1)

    #print(lista_undo)
    zi_stergere_gresita = 29
    try:
        sterge_cheltuieli_dupa_zi_service(cheltuieli,lista_undo,zi_stergere_gresita)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "nu exista cheltuieli efectuate in ziua data!\n")

    #print(cheltuieli)
    id_chl_noua_2 = 87
    zi_chl_noua_2 = 25
    suma_chl_noua_2 = 890.2
    tip_chl_noua_2 = "intretinere"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_noua_2,zi_chl_noua_2,suma_chl_noua_2,tip_chl_noua_2)

    id_chl_noua_3 = 22
    zi_chl_noua_3 = 7
    suma_chl_noua_3 = 7576.908
    tip_chl_noua_3 = "telefon"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_noua_3,zi_chl_noua_3,suma_chl_noua_3,tip_chl_noua_3)

    zi_start = 23
    zi_end = 30
    sterge_cheltuieli_interval_timp_service(cheltuieli,lista_undo,zi_start,zi_end)
    assert(numar_cheltuieli_lista(cheltuieli) == 1)
    #print(len(cheltuieli))

    zi_start_gresita = 11
    zi_end_gresita = 16
    try:
        sterge_cheltuieli_interval_timp_service(cheltuieli,lista_undo,zi_start_gresita,zi_end_gresita)
    except ValueError as string_ve:
        assert(str(string_ve) == "nu exista cheltuieli efectuate in acest interval de timp\n")


    id_chl_4 = 44
    zi_chl_4 = 3
    suma_chl_4 = 900.2
    tip_chl_4 = "telefon"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_4,zi_chl_4,suma_chl_4,tip_chl_4)

    id_chl_5 = 102
    zi_chl_5 = 16
    suma_chl_5 = 784.3
    tip_chl_5 = "altele"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_5,zi_chl_5,suma_chl_5,tip_chl_5)

    tip_cautat = "telefon"
    sterge_cheltuieli_tip_service(cheltuieli,lista_undo,tip_cautat)
    assert(numar_cheltuieli_lista(cheltuieli) == 1)

    tip_cautat_gresit = ""
    try:
        sterge_cheltuieli_tip_service(cheltuieli,lista_undo,tip_cautat_gresit)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "tip invalid!\n")

    #suma_min_1 = 93.232
    #assert(len(cheltuieli_mai_mari_decat_suma_service(cheltuieli,suma_min_1))==2)
    #cheltuieli_mai_mari_decat_suma_service(cheltuieli,suma_min_1)

    #assert(determina_zi_suma_maxima(cheltuieli)==433.329)



def run_teste_tipariri_cheltuieli():
    cheltuieli = []
    lista_undo = []
    id_chl = 18
    zi_chl = 12
    suma_chl = 230.1
    tip_chl = "mancare"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl,zi_chl,suma_chl,tip_chl)

    id_chl_2 = 95
    zi_chl_2 = 19
    suma_chl_2 = 190.2
    tip_chl_2 = "mancare"

    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_2,zi_chl_2,suma_chl_2,tip_chl_2)

    suma_min = 200
    tip_cautat = "mancare"

    assert(abs(suma_totala_tip_cheltuiala(cheltuieli,tip_cautat)-float(suma_totala_tip_cheltuiala(cheltuieli,tip_cautat)))<0.0001)
    suma_totala_corecta = suma_totala_tip_cheltuiala(cheltuieli,tip_cautat)
    assert(suma_totala_corecta == suma_chl + suma_chl_2)

    tip_cautat_greist = "altele"

    try:
        suma_total = suma_totala_tip_cheltuiala(cheltuieli,tip_cautat_greist)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve)=="nu exista cheltuieli de acest tip!\n")

    assert (determinare_cheltuieli_anumit_tip(cheltuieli,tip_cautat) == cheltuieli)

    try:
        lista_noua = determinare_cheltuieli_anumit_tip(cheltuieli,tip_cautat_greist)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "nu exista cheltuieli de acest tip!\n")

    assert(cheltuieli_mai_mari_decat_suma_service(cheltuieli,150) == cheltuieli)

    try:
        lista_noua = cheltuieli_mai_mari_decat_suma_service(cheltuieli,400.324)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve)=="nu exista cheltuieli de valori mai mari decat suma data!")

    assert(len(filtrare_cheltuieli_anumit_tip_service(cheltuieli,"mancare"))==0)

    try:
        lista_noua = filtrare_cheltuieli_anumit_tip_service(cheltuieli,"altele")
        assert False
    except ValueError as string_ve:
        assert(str(string_ve)=="nu exista cheltuieli de acest tip!\n")

    id_chl_3 = 67
    zi_chl_3 = 25
    suma_chl_3 = 1232.232
    tip_chl_3 = "telefon"
    adaugare_cheltuiala_lista_service(cheltuieli,lista_undo,id_chl_3,zi_chl_3,suma_chl_3,tip_chl_3)

    assert(len(filtrare_cheltuieli_anumit_tip_service(cheltuieli,"mancare"))==1)

    zi = 15
    suma_max = 320.19
    assert(len(tiparire_cheltuieli_inainte_de_o_zi_mai_mici_decat_suma_service(cheltuieli,zi,suma_max)) == 1)

    suma_max_1 = 59.32
    try:
        lista_noua = tiparire_cheltuieli_inainte_de_o_zi_mai_mici_decat_suma_service(cheltuieli,zi,suma_max_1)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve)=="nu exista cheltuieli efectuate inainte de ziua data si cu o valoarea mai mica decat suma data!")

    assert(determinare_zi_suma_maxima_service(cheltuieli) == 25)

    suma = 1232.232
    assert(len(tiparire_cheltuieli_anumita_suma_service(cheltuieli,suma)) == 1)

    caracteristica = "suma"
    criteriu = "descrescator"
    afisare_cheltuieli_sortate_criteriu_service(cheltuieli, caracteristica, criteriu)
    assert (cheltuieli[0]["suma"] == 1232.232)

    caracteristica_2 = "zi"
    criteriu_2 = "crescator"
    afisare_cheltuieli_sortate_criteriu_service(cheltuieli,caracteristica_2,criteriu_2)
    assert(cheltuieli[0]["zi"] == 12)

def run_teste_undo():
    cheltuieli = []
    lista_undo = []
    id_chl = 18
    zi_chl = 12
    suma_chl = 230.1
    tip_chl = "mancare"
    adaugare_cheltuiala_lista_service(cheltuieli, lista_undo, id_chl, zi_chl, suma_chl, tip_chl)

    id_chl_2 = 95
    zi_chl_2 = 19
    suma_chl_2 = 190.2
    tip_chl_2 = "altele"
    adaugare_cheltuiala_lista_service(cheltuieli, lista_undo, id_chl_2, zi_chl_2, suma_chl_2, tip_chl_2)

    suma_max = 200.2
    assert (len(filtrare_cheltuieli_mai_mici_suma_service(cheltuieli, suma_max)) == 1)

    afisare_cheltuieli_sortate_tip_service(cheltuieli)
    assert(get_tip(cheltuieli[0]) == "altele")

    undo_service(cheltuieli,lista_undo)
    assert(get_numar_cheltuieli_lista(cheltuieli) == 1)
    undo_service(cheltuieli,lista_undo)
    assert(get_numar_cheltuieli_lista(cheltuieli) == 0)
    try:
        undo_service(cheltuieli,lista_undo)
        assert False
    except ValueError as string_ve:
        assert(str(string_ve) == "Nu se mai poate efectua operatia de undo!\n")


def run_all_tests():
    run_teste_creare_cheltuieli()
    print("teste cheltuiala trecute cu succes!")
    run_teste_validare_cheltuieli()
    print("teste validare cheltuieli trecute cu succes!")
    run_teste_repos_cheltuieli()
    print("teste cheltuieli repositories trecute cu succes!")
    run_teste_service_cheltuieli()
    print("teste cheltuieli services trecute cu succes!")
    run_teste_stergeri_cheltuieli()
    print("teste stergeri cheltuieli trecute cu succes!")
    run_teste_tipariri_cheltuieli()
    print("teste tipariri trecute cu succes!")
    run_teste_undo()
    print("teste undo ultima operatie efectuata trecute cu succes!")