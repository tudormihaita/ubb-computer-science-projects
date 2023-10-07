from domain.inchirieri import Inchiriere
from domain.data_transfer_objects.situatie_clienti_inchirieri import SituatieClientiInchiriere
from domain.data_transfer_objects.situatie_filme_inchiriate import SituatieFilmeInchiriere
from domain.data_transfer_objects.inchirieriDTO import InchiriereDTO
from erori.exceptii import RepoError
from utils.algoritmi import sortari


class ServiceInchiriere(object):

    def __init__(self, __repo_inchirieri, __validator_inchirieri, __repo_clienti, __repo_filme, __file_path):
        """
        initializeaza repo-urile de filme,clienti si inchirieri, dar si validatorul de inchirieri
        :param __repo_inchirieri: RepoInchiriere
        :param __validator_inchirieri: ValidatorInchiriere
        :param __repo_clienti: RepoClient
        :param __repo_filme: RepoFilm
        """
        self.__repo_inchirieri = __repo_inchirieri
        self.__validator_inchirieri = __validator_inchirieri
        self.__repo_clienti = __repo_clienti
        self.__repo_filme = __repo_filme
        self.__file_path = __file_path

    def size(self):
        """
        returneaza numarul de inchirieri din baza de date
        :return: rez: int-ul len, egal cu numarul de inchirieri
        """
        return len(self.__repo_inchirieri)

    def adauga_inchiriere(self, id_inchiriere, id_client, id_film, data_inchiriere, status_inchiriere):
        """
        creeaza o entitate de tip inchiriere folosind un id, un client preluat prin id, un film preluat prin id si o data calendaristica corespunzatoare
        cu momentul efectuarii inchirierii
        valideaza datele introduse si adauga in baza de date inchirierea respectiva
        :param id_inchiriere: int
        :param id_client: int
        :param id_film: int
        :param data_inchiriere: string cu formatul dd/mm/yyyy
        :param status_inchiriere: bool True/False
        :return: - ( adauga in baza de date inchirierea valida creata )
        """
        # client = self.__repo_clienti.cauta_client_dupa_id(id_client)
        # film = self.__repo_filme.cauta_film_dupa_id(id_film)
        inchiriere = InchiriereDTO(id_inchiriere, id_client, id_film, data_inchiriere, status_inchiriere)

        self.__validator_inchirieri.valideaza(inchiriere)
        self.__repo_inchirieri.adauga_inchiriere(inchiriere)

    def cauta_inchiriere_dupa_id(self, id_inchiriere):
        """
        cauta in baza de date inchirierea corespunzatoarea int-ului id_inchiriere introdus, in cazul in care acesta exista si este valid
        :param id_inchiriere: int
        :return: o inchiriere cu id-ul introdus
        """
        inchiriere_dto = self.__repo_inchirieri.cauta_inchiriere_dupa_id(id_inchiriere)
        try:
            client = self.__repo_clienti.cauta_client_dupa_id(inchiriere_dto.get_id_client_inchiriere())
            film = self.__repo_filme.cauta_film_dupa_id(inchiriere_dto.get_id_film_inchiriere())
        except:
            raise RepoError("inchiriere inexistenta!")
        inchiriere = Inchiriere(inchiriere_dto.get_id_inchiriere(), client, film,
                                inchiriere_dto.get_data_inchiriere(), inchiriere_dto.get_status_inchiriere())
        return inchiriere

    def modifica_inchiriere(self, id_inchiriere, id_client, id_film, data_inchiriere):
        """
        pentru inchirierea specificata prin id, se modifica atributele acesteia in cazul in care exista, iar datele noi introduse sunt valide
        :param id_inchiriere: int
        :param id_client: int
        :param id_film: int
        :param data_inchiriere: string cu formatul dd/mm/yyyy
        :return: - ( se va modifica in baza de date inchirierea data prin id )
        """
        inchiriere_dto = self.__repo_inchirieri.cauta_inchiriere_dupa_id(id_inchiriere)
        client = self.__repo_clienti.cauta_client_dupa_id(id_client)
        film = self.__repo_filme.cauta_film_dupa_id(id_film)
        inchiriere = InchiriereDTO(id_inchiriere, id_client, id_film, data_inchiriere,
                                   inchiriere_dto.get_status_inchiriere())
        self.__validator_inchirieri.valideaza(inchiriere)
        self.__repo_inchirieri.modifica_inchiriere(inchiriere)

    def sterge_inchiriere_dupa_id(self, id_inchiriere):
        """
        cauta in baza de date inchirierea specificata prin int-ul id_inchiriere si o elimina in cazul in care exista ( o marcheaza ca fiind stearsa )
        :param id_inchiriere: int
        :return: - ( marcheaza ca fiind stearsa inchirierea specificata prin id )
        """
        self.__repo_inchirieri.sterge_inchiriere_dupa_id(id_inchiriere)

    def get_all_inchirieri(self):
        """
        returneaza toate inchirierile din baza de date, preluate sub forma de lista
        :return: o lista de inchirieri
        """
        lista_dto = self.__repo_inchirieri.get_all_inchirieri()
        lista = []
        for inchiriere_dto in lista_dto:
            try:
                client = self.__repo_clienti.cauta_client_dupa_id(inchiriere_dto.get_id_client_inchiriere())
                film = self.__repo_filme.cauta_film_dupa_id(inchiriere_dto.get_id_film_inchiriere())
                inchiriere = Inchiriere(inchiriere_dto.get_id_inchiriere(), client, film,
                                        inchiriere_dto.get_data_inchiriere(), inchiriere_dto.get_status_inchiriere())
                if inchiriere.get_status_inchiriere() == "True":
                    lista.append(inchiriere)
            except:
                continue

        return lista

    def genereaza_situatie_inchirieri_clienti(self):
        """
        creeaza un dictionar cu key-ul id_client, in care se vor contoriza intr-o lista id-urile de filme inchiriate de fiecare pentru a putea realiza
        o situatie a filmelor inchiriate
        :return: dict situate_inchirieri_clienti
        """
        all_inchirieri = self.get_all_inchirieri()
        situatie_inchirieri_clienti = {}
        for inchiriere in all_inchirieri:
            id_client = inchiriere.get_client_inchiriere().get_id_client()
            if id_client not in situatie_inchirieri_clienti:
                situatie_inchirieri_clienti[id_client] = []

            situatie_inchirieri_clienti[id_client].append(inchiriere.get_film_inchiriere().get_id_film())
            # dupa crearea dictionarului  de situatie inchirieri, creeaza o noua metoda de convertire a intrarilor in obiecte DTO,
            # care vor avea un client(cu id, nume, cnp) si filmele inchiriate de acesta(doar id, sau id si nume SAU doar numarul de filme)
            # dupa care, in functie de obiectele create, sortez lista noua de obiecte obtinuta

        return situatie_inchirieri_clienti

    def genereaza_situatie_inchirieri_filme(self):
        """
        creeaza un dictionar cu key-ul i_film, in care se vor contoriza intr-o lista id-urile de clienti care au inchiriat filmul
        respectiv pentru a putea realiza o situatie a filmelor inchiriate
        :return: dict situatie_inchirieri_filme
        """
        all_inchirieri = self.get_all_inchirieri()
        situatie_inchirieri_filme = {}
        for inchiriere in all_inchirieri:
            id_film = inchiriere.get_film_inchiriere().get_id_film()
            if id_film not in situatie_inchirieri_filme:
                situatie_inchirieri_filme[id_film] = []

            situatie_inchirieri_filme[id_film].append(inchiriere.get_client_inchiriere().get_id_client())

        return situatie_inchirieri_filme

    def creeaza_situatii_DTO_clienti(self):
        """
        preia perechile (key,value) din dictionarul de situatie_inchirieri_clienti si le converteste in obiecte DTO ( Data Transfer Object ) de tip SituatieClientiInchiriere
        pentru a realiza repoartele in functie de filmele inchiriate de fiecare client
        :return: rez - o lista de obiecte DTO SituatieClientiInchirieri cu un client, o lista de filme inchiriate si un numar de filme inchiriate
        """
        rez = []
        situatie_inchirieri_clienti = self.genereaza_situatie_inchirieri_clienti()

        for id_client in situatie_inchirieri_clienti:
            client = self.__repo_clienti.cauta_client_dupa_id(id_client)
            lista_filme_inchiriate = []
            for id_film in situatie_inchirieri_clienti[id_client]:
                lista_filme_inchiriate.append(id_film)
            situatie_DTO = SituatieClientiInchiriere(client, lista_filme_inchiriate)
            # print(situatie_client)
            rez.append(situatie_DTO)

        return rez

    def creeaza_situatii_DTO_filme(self):
        """
        preia perechile (key,value) din dictionarul de situatie_inchirieri_filme si le converteste in obiecte DTO ( Data Transfer Object ) de tip SituatieFilmeInchiriere
        pentru a realiza repoartele in functie de filmele inchiriate si de ce clienti au inchiriat fiecare film
        :return: rez - o lista de obiecte DTO SituatieFilmeInchirieri cu un film, o lista de clienti care au inchiriat filmul dat
         si un numar de clienti care au filmul respectiv inchiriat
        """
        rez = []
        situatie_inchiriere_filme = self.genereaza_situatie_inchirieri_filme()

        for id_film in situatie_inchiriere_filme:
            film = self.__repo_filme.cauta_film_dupa_id(id_film)
            lista_clienti = []
            for id_client in situatie_inchiriere_filme[id_film]:
                lista_clienti.append(id_client)
            situatie_DTO = SituatieFilmeInchiriere(film, lista_clienti)
            rez.append(situatie_DTO)

        return rez

    def sorteaza_clienti_nr_filme_inchiriate(self):
        """
        sorteaza in functie de numarul de filme inchiriate lista de obiecte DTO SituatieClientiInchiriere si le afiseaza in ordine descrescatoare
        :return: rez - lista de obiecte DTO SituatieClientiInchiriere sortata descrescator in functie de numarul de filme
        """
        rez = self.creeaza_situatii_DTO_clienti()

        # lista.sort(key=lambda x: x.get("tip"), reverse=False)
        rez.sort(key=lambda x: x.get_numar_filme_inchiriate(), reverse=True)
        #rez_sortat = sortari.sorteaza(rez, "BingoSort", cmp = sortari.cmp,
                                      #key=lambda x: (x.get_numar_filme_inchiriate(), x.get_client_situatie().get_nume_client() ), reverse=True)
        #return rez_sortat
        return rez

    def sorteaza_clienti_nume(self):
        """
        sorteaza alfabetic in functie de nume clientii care figureaza in baza de date drept avand filme inchiriate
        :return: rez - lista de obiecte DTO SituatieClientiInchiriere sortata alfabetic in functie de numele clientilor cu filme inchiriate
        """
        rez = self.creeaza_situatii_DTO_clienti()

        rez.sort(key=lambda x: x.get_client_situatie().get_nume_client(), reverse=False)
        return rez

    def sorteaza_filme_cele_mai_inchiriate(self):
        """
        sorteaza descrescator lista de obiecte DTO SituatieFilmeInchiriere in functie de numarul de inchirieri ale fiecarui film, pentru a determina
        cele mai inchiriate filme
        :return: rez - lista de obiecte DTO SituatieFilmeInchiriere sortata descrescator dupa numarul de inchirieri ale filmelor
        """
        rez = self.creeaza_situatii_DTO_filme()

        # rez.sort(key=lambda x: x.get_numar_clienti_situatie(), reverse=True)
        # return rez

        rez_sortat = sortari.sorteaza(rez, "MergeSort", cmp=sortari.cmp_2,
                                     key = lambda x: (x.get_numar_clienti_situatie(), x.get_film_situatie().get_titlu_film()), reverse=True)
        #rez_sortat = sortari.sorteaza(rez, "MergeSort", key=lambda x: x.get_numar_clienti_situatie(), reverse=True)
        #rez_sortat = sortari.sorteaza(rez, "BingoSort", key=lambda x: x.get_numar_clienti_situatie(), reverse=True)
        # rez_sortat = sortari.sorteaza(rez, "QuickSort", key=lambda x: x.get_numar_clienti_situatie(), reverse=True)
        # rez_sortat = recursivitate.QuickSortRecursiv(rez, 0, len(rez)-1, key=lambda x: x.get_numar_clienti_situatie(), reverse=True)
        return rez_sortat

    def sorteaza_clienti_procent_filme_inchiriate(self, procent):
        """
        sorteaza descrescator clientii din lista de obiecte DTO SituatieClientInchiriere in functie de numarul de filme inchiriate si afiseaza
        primii x% din acestia, unde x este un procent dat
        :return: primii x% clienti cu cele mai multe filme inchiriate
        """
        rez = self.creeaza_situatii_DTO_clienti()
        numar_intrari = int((procent * len(rez) / 100))
        rez.sort(key=lambda x: x.get_numar_filme_inchiriate(), reverse=True)

        return rez[:numar_intrari]

    def sorteaza_filme_titlu(self):
        """
        sorteaza alfabetic in functie de nume filmele care figureaza in baza de date drept fiind inchiriate de unul sau mai multi clienti
        :return: rez - lista de obiecte DTO SituatieFilmeInchiriere sortata alfabetic in functie de numele filmelor inchiriate
        """
        rez = self.creeaza_situatii_DTO_filme()
        # rez.sort(key=lambda x: x.get_film_situatie().get_titlu_film(), reverse=False)
        # return rez
        rez_sortat = sortari.sorteaza(rez, "BingoSort", cmp = sortari.cmp,
                                      key=lambda x: x.get_film_situatie().get_titlu_film(), reverse=False)
        return rez_sortat


    def clear_file(self):
        with open(self.__file_path, "w") as f:
            pass
        f.close()

    def write_rezultat_raport_file(self, rez):
        with open(self.__file_path, "w") as f:
            for situatie in rez:
                f.write(
                    f"{situatie.get_numar_filme_inchiriate()} {situatie.get_client_situatie().get_nume_client()} {situatie.get_filme_inchiriate()}" + "\n")
            f.close()

    def afiseaza_rezultat_raport_file(self):
        rez = self.sorteaza_clienti_nr_filme_inchiriate()
        self.write_rezultat_raport_file(rez)
