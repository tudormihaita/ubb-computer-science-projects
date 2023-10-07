from erori.exceptii import RepoError, ValidationError

class UI(object):

    def __init__(self, __service_spectacole):
        self.__service_spectacole = __service_spectacole
        self.__comenzi = {
            "afiseaza_spectacole": self.__ui_afiseaza_spectacole,
            "adauga_spectacol": self.__ui_adauga_spectacol,
            "modifica_spectacol": self.__ui_modifica_spectacol,
            "genereaza_spectacole": self.__ui_genereaza_spectacole,
            "exporta_spectacole_sortate": self.__ui_exporta_spectacole_sortate
        }

    def __ui_afiseaza_spectacole(self):
        lista_spectacole = self.__service_spectacole.get_all_spectacole()
        if len(lista_spectacole) == 0:
            print("Nu exista spectacole adaugate!\n")
            return
        for spectacol in lista_spectacole:
            print(spectacol)

    def __ui_adauga_spectacol(self):
        titlu = input("Introduceti titlul spectacolului:")
        artist = input("Introduceti numele artistului:")
        gen = input("Introduceti genul spectacolului:")
        durata = int(input("introduceti durata spectacolului:"))
        self.__service_spectacole.adauga_spectacol(titlu, artist, gen, durata)
        print("Spectacol adaugat cu succes!")

    def __ui_modifica_spectacol(self):
        titlu_cautat = input("Introduceti titlul spectacolului cautat:")
        artist_cautat = input("Introduceti numele artistului cautat:")
        gen_nou = input("Introduceti noul gen:")
        durata_noua = int(input("introduceti noua durata:"))
        self.__service_spectacole.modifica_spectacol(titlu_cautat, artist_cautat, gen_nou, durata_noua)
        print("Spectacol modificat cu succes!")

    def __ui_genereaza_spectacole(self):
        nr_generari = int(input("Introduceti numarul de specatcole pe care doriti sa-l generati:"))
        if nr_generari <= 0:
            print("Numar invalid de generari introdus, trebuie sa fie un numar intreg strict pozitiv si mai mare ca 0!\n")
            return
        lista_generari = self.__service_spectacole.genereaza_spectacole(nr_generari)
        print("Spectacole generate cu succes!")
        print("Urmatoarele spectacole au fost generate:")
        for spectacol in lista_generari:
            print(spectacol)

    def __ui_exporta_spectacole_sortate(self):
        file_path = input("Introduceti numele fisierului pentru export:")
        self.__service_spectacole.exporta_spectacole_sortate(file_path)
        print("Spectacole ordonate exportate cu succes!")

    def help(self):
        print("Comenzi disponibile in aplicatie:")
        print("[afiseaza_spectacole] - Afiseaza spectacolele introduse pana la momentul actual")
        print("[adauga_spectacol] - Ofera optiunea de adaugare a unui nou spectacol")
        print("[modifica_spectacol] - Ofera posibilitatea modificarii unui spectacol")
        print("[genereaza_spectacole] - Genereaza un numar dat de spectacole aleatoriu")
        print("[exporta_spectacole_sortate] - Exporta in fisierul cu numele dat spectacolele sortate dupa titlu si artist")

    def run(self):
        while True:
            comanda = input(">>>")
            comanda = comanda.strip()
            if comanda == "":
                continue
            if comanda == "exit":
                return
            if comanda in self.__comenzi:
                try:
                    self.__comenzi[comanda]()
                except ValueError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
                except ValidationError as ve:
                    print(ve)
            else:
                print("comanda invalida!")