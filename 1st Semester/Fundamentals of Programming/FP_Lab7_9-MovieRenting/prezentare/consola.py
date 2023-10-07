from erori.exceptii import RepoError,ValidationError
from utils.algoritmi import recursivitate


class UI(object):

    def __init__(self,service_filme,service_clienti,service_inchirieri,generator_clienti,generator_filme):
        self.__service_filme = service_filme
        self.__service_clienti = service_clienti
        self.__service_inchirieri = service_inchirieri
        self.__generator_clienti = generator_clienti
        self.__generator_filme = generator_filme
        self.__comenzi = {
            "help" : self.__ui_help,
            "adauga_film" : self.__ui_adauga_film,
            "afiseaza_filme" : self.__ui_afiseaza_filme,
            "modifica_film" : self.__ui_modifica_film,
            "cauta_film" : self.__ui_cauta_film_dupa_id,
            "sterge_film" : self.__ui_sterge_film_dupa_id,
            "adauga_client" : self.__ui_adauga_client,
            "afiseaza_clienti" : self.__ui_afiseaza_clienti,
            "modifica_client" : self.__ui_modifica_client,
            "cauta_client" : self.__ui_cauta_client_dupa_id,
            "sterge_client" : self.__ui_sterge_client_dupa_id,
            "adauga_inchiriere" : self.__ui_adauga_inchiriere,
            "afiseaza_inchirieri" : self.__ui_afiseaza_inchirieri,
            "modifica_inchiriere" : self.__ui_modifica_inchiriere,
            "cauta_inchiriere" : self.__ui_cauta_inchiriere_dupa_id,
            "sterge_inchiriere" : self.__ui_sterge_inchiriere_dupa_id,
            "genereaza_clienti" : self.__ui_genereaza_clienti,
            "genereaza_filme" : self.__ui_genereaza_filme,
            "genereaza_situatie_inchirieri" : self.__ui_genereaza_situatie_inchirieri,
            "sorteaza_clienti_nr_filme_inchiriate" : self.__ui_sorteaza_clienti_nr_filme_inchiriate,
            "sorteaza_clienti_nume" : self.__ui_sorteaza_clienti_nume,
            "sorteaza_filme_cele_mai_inchiriate" : self.__ui_sorteaza_filme_cele_mai_inchiriate,
            "sorteaza_clienti_procent_filme_inchiriate" : self.__ui_sorteaza_clienti_procent_filme_inchiriate,
            "sorteaza_filme_titlu" : self.__ui_sorteaza_filme_titlu,
            "afiseaza_rezultat_raport_file" : self.__ui_afiseaza_rezultat_raport_file
        }


    def __ui_adauga_film(self):
        if len(self.__params)<4:
            print("numar parametri invalid!")
            return
        id_film = int(self.__params[0])
        titlu_film = self.__params[1]
        gen_film = self.__params[2]
        descriere_film = self.__params[3:]
        #print(descriere_film)
        string_descriere = ' '.join(str(x) for x in descriere_film)
        string_descriere.strip()
        #print(string_descriere)
        self.__service_filme.adauga_film(id_film,titlu_film,gen_film,string_descriere)
        print("filmul a fost adaugat cu succes!")


    def __ui_afiseaza_filme(self):
        if len(self.__params)!=0:
            print("numar parametri invalid!")
            return
        filme = self.__service_filme.get_all_filme()
        if len(filme)==0:
            print("nu exista filme inregistrate!")
            return
        # ITERATIV:
        """
        for film in filme:
            print(film)
        """
        # RECURSIV:
        recursivitate.afisare_ui_recursiv(filme)

    def __ui_modifica_film(self):
        if len(self.__params) < 4:
            print("numar parametri invalid!")
            return
        id_film_modificat = int(self.__params[0])
        titlu_film_modificat = self.__params[1]
        gen_film_modificat = self.__params[2]
        descriere_film_modificat = self.__params[3:]
        string_descriere = ' '.join(str(x) for x in descriere_film_modificat)
        string_descriere.strip()
        self.__service_filme.modifica_film(id_film_modificat,titlu_film_modificat,gen_film_modificat,string_descriere)

    def __ui_cauta_film_dupa_id(self):
        if len(self.__params) !=1:
            print("numar parametri invalid!")
            return
        id_film_cautat = int(self.__params[0])
        film_cautat = self.__service_filme.cauta_film_dupa_id(id_film_cautat)
        print(film_cautat)

    def __ui_sterge_film_dupa_id(self):
        if len(self.__params) !=1:
            print("numar parametri invalid!")
            return
        id_film_cautat = int(self.__params[0])
        self.__service_filme.sterge_film_dupa_id(id_film_cautat)
        print("film eliminat cu succes!")

    def __ui_adauga_client(self):
        if len(self.__params) != 3:
            print("numar parametri invalid!")
            return
        id_client = int(self.__params[0])
        nume_client = self.__params[1]
        cnp_client = self.__params[2]
        self.__service_clienti.adauga_client(id_client,nume_client,cnp_client)
        print("clientul a fost adaugat cu succes!")

    def __ui_afiseaza_clienti(self):
        if len(self.__params)!=0:
            print("numar parametri invalid!")
            return
        clienti = self.__service_clienti.get_all_clienti()
        if len(clienti)==0:
            print("nu exista clienti inregistrati!")
            return
        # ITERATIV:
        """
        for client in clienti:
            print(client)
        """
        # RECURSIV:
        recursivitate.afisare_ui_recursiv(clienti)

    def __ui_modifica_client(self):
        if len(self.__params) != 3:
            print("numar parametri invalid!")
            return
        id_client_modificat = int(self.__params[0])
        nume_client_modificat = self.__params[1]
        cnp_client_modificat = self.__params[2]
        self.__service_clienti.modifica_client(id_client_modificat,nume_client_modificat,cnp_client_modificat)

    def __ui_cauta_client_dupa_id(self):
        if len(self.__params) !=1:
            print("numar parametri invalid!")
            return
        id_client_cautat = int(self.__params[0])
        client_cautat = self.__service_clienti.cauta_client_dupa_id(id_client_cautat)
        print(client_cautat)

    def __ui_sterge_client_dupa_id(self):
        if len(self.__params) !=1:
            print("numar parametri invalid!")
            return
        id_client_cautat = int(self.__params[0])
        self.__service_clienti.sterge_client_dupa_id(id_client_cautat)
        print("client sters cu succes!")

    def __ui_adauga_inchiriere(self):
        if len(self.__params) != 4:
            print("numar parametri invalid!")
            return
        id_inchiriere = int(self.__params[0])
        id_client = int(self.__params[1])
        id_film = int(self.__params[2])
        data_inchiriere = self.__params[3]
        status_inchiriere = "True"
        self.__service_inchirieri.adauga_inchiriere(id_inchiriere,id_client,id_film,data_inchiriere,status_inchiriere)
        print("inchiriere adaugata cu succes!")

    def __ui_afiseaza_inchirieri(self):
        if len(self.__params) != 0:
            print("numar parametri invalid!")
            return
        inchirieri = self.__service_inchirieri.get_all_inchirieri()
        if len(inchirieri) == 0:
            print("nu exista inchirieri inregistrate!")
            return
        # ITERATIV:
        """
        for inchiriere in inchirieri:
            print(inchiriere)
        """
        # RECURSIV:
        recursivitate.afisare_ui_recursiv(inchirieri)

    def __ui_modifica_inchiriere(self):
        if len(self.__params) != 4:
            print("numar parametri invalid!")
            return
        id_inchiriere_modificata = int(self.__params[0])
        id_client_modificat = int(self.__params[1])
        id_film_modificat = int(self.__params[2])
        data_inchiriere_modificata = self.__params[3]
        self.__service_inchirieri.modifica_inchiriere(id_inchiriere_modificata,id_client_modificat,id_film_modificat,data_inchiriere_modificata)
        print("inchiriere modificata cu succes!")

    def __ui_cauta_inchiriere_dupa_id(self):
        if len(self.__params) != 1:
            print("numar parametri invalid!")
            return
        id_inchiriere_cautata = int(self.__params[0])
        inchiriere_cautata = self.__service_inchirieri.cauta_inchiriere_dupa_id(id_inchiriere_cautata)
        print(inchiriere_cautata)

    def __ui_sterge_inchiriere_dupa_id(self):
        if len(self.__params) != 1:
            print("numar parametri invalid!")
            return
        id_inchiriere_cautat = int(self.__params[0])
        self.__service_inchirieri.sterge_inchiriere_dupa_id(id_inchiriere_cautat)
        print("inchiriere stearsa cu succes!")


    def __ui_genereaza_clienti(self):
        if len(self.__params) !=1:
            print("numar parametri invalid!")
            return
        numar_clienti = int(self.__params[0])
        if numar_clienti < 1:
            print("numar clienti invalid!")
            return
        self.__generator_clienti.adauga_clienti_generati(numar_clienti)
        print("clienti generati cu succes!")


    def __ui_genereaza_filme(self):
        if len(self.__params) !=1:
            print("numar parametri invalid!")
            return
        numar_filme = int(self.__params[0])
        if numar_filme < 1:
            print("numar filme invalid!")
            return
        self.__generator_filme.adauga_filme_generate(numar_filme)
        print("filme generate cu succes!")


    def __ui_genereaza_situatie_inchirieri(self):
       # verifica generarea listei de obiecte DTO pentru efectuarea rapoartelor
        if len(self.__params) != 0:
            print("numar parametri invalid!")
            return
        situatie_inchirieri = self.__service_inchirieri.genereaza_situatie_inchirieri_filme()
        print(situatie_inchirieri)
        self.__service_inchirieri.creeaza_situatii_DTO_filme()
        rez = self.__service_inchirieri.sorteaza_clienti_nr_filme_inchiriate()
        for situatie_inchiriere in rez:
            print(situatie_inchiriere)



    def __ui_sorteaza_clienti_nr_filme_inchiriate(self):
        if len(self.__params) != 0:
            print("numar parametri invalid!")
            return

        rez = self.__service_inchirieri.sorteaza_clienti_nr_filme_inchiriate()
        if len(rez) == 0:
            print("nu exista inchirieri efectuate!")

        for situatie_inchiriere in rez:
            print(situatie_inchiriere)

    def __ui_sorteaza_clienti_nume(self):
        if len(self.__params) != 0:
            print("numar parametri invalid!")
            return

        rez = self.__service_inchirieri.sorteaza_clienti_nume()
        if len(rez) == 0:
            print("nu exista inchirieri efectuate!")

        for situatie_inchiriere in rez:
            print(situatie_inchiriere)

    def __ui_sorteaza_filme_cele_mai_inchiriate(self):
        if len(self.__params) != 0:
            print("numar parametri invalid!")
            return

        rez = self.__service_inchirieri.sorteaza_filme_cele_mai_inchiriate()
        if len(rez) == 0:
            print("nu exista inchiriere efectuate!")

        for situatie_inchiriere in rez:
            print(situatie_inchiriere)

    def __ui_sorteaza_clienti_procent_filme_inchiriate(self):
        if len(self.__params) != 1:
            print("numar parametri invalid!")

        procent = int(self.__params[0])
        if procent <= 0:
            print("procentul introdus este invalid!")
            return
        rez = self.__service_inchirieri.sorteaza_clienti_procent_filme_inchiriate(procent)

        for situatie_inchiriere in rez:
            print(situatie_inchiriere)

    def __ui_sorteaza_filme_titlu(self):
        if len(self.__params) != 0:
            print("numar parametri invalid!")
            return

        rez = self.__service_inchirieri.sorteaza_filme_titlu()
        if len(rez) == 0:
            print("nu exista inchirieri efectuate!")

        for situatie_inchiriere in rez:
            print(situatie_inchiriere)

    def __ui_afiseaza_rezultat_raport_file(self):
        if len(self.__params) != 0:
            print("numar parametri invalid!")
            return
        self.__service_inchirieri.clear_file()
        self.__service_inchirieri.afiseaza_rezultat_raport_file()


    def __ui_help(self):
        print("Introduceti entitatea pentru care doriti sa vizualizati comenzile: [filme] , [clienti], [inchirieri], [generari], [rapoarte]")
        optiune = input(">>>")
        optiune = optiune.strip()
        if optiune == "filme":
            print("Lista de comenzi disponibile in aplicatie si parametrii necesari efectuarii acestora:")
            print("adauga_film [id] [titlu] [gen] [descriere]")
            print("afiseaza_filme")
            print("modifica_film [id] [titlu_nou] [gen_nou] [descriere_noua]")
            print("cauta_film [id_film_cautat]")
            print("sterge_film [id_film_cautat]")
        elif optiune == "clienti":
            print("adauga_client [id] [nume] [cnp]")
            print("afiseaza_clienti")
            print("modifica_client [id] [nume_nou] [cnp_nou]")
            print("cauta_client [id_client_cautat]")
            print("sterge_client [id_client_cautat]")
        elif optiune == "inchrieri":
            print("adauga_inchiriere [id] [id_client] [id_film] [data_inchiriere]")
            print("afiseaza_inchirieri")
            print("modifica_inchiriere [id] [id_client_nou] [id_film_nou] [data_inchiriere_noua]")
            print("cauta_inchiriere [id_inchiriere_cautata]")
            print("sterge_inchiriere [id_inchiriere_cautata")
        elif optiune == "generari":
            print("genereaza_filme [nr_filme_dorite]")
            print("genereaza_clienti [nr_clienti_doriti]")
        elif optiune == "rapoarte":
            print("sorteaza_clienti_nr_filme_inchiriate")
            print("sorteaza_clienti_nume")
            print("sorteaza_filme_cele_mai_inchiriate")
            print("sorteaza_clienti_procent_filme_inchiriate [procent]")
            print("sorteaza_filme_titlu")
            print("afiseaza_rezultat_raport_file")
        else:
            print("comanda invalida!")
            return

    def run(self):
        while True:
            comanda = input(">>>")
            comanda = comanda.strip()
            if comanda == "":
                continue
            if comanda == "exit":
                return
            parti = comanda.split()
            nume_comanda = parti[0]
            self.__params = parti[1:]
            if nume_comanda in self.__comenzi:
                try:
                    self.__comenzi[nume_comanda]()
                except ValueError as ve:
                    print(ve)
                except ValidationError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)

            else:
                print("comanda invalida!")
