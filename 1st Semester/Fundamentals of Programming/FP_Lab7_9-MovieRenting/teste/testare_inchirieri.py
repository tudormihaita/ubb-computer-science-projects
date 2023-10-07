from domain.inchirieri import Inchiriere
from domain.clienti import Client
from domain.filme import Film
from erori.exceptii import ValidationError,RepoError
from validare.validator_inchirieri import ValidatorInchiriere
from persistenta.repos_inchirieri import RepoInchiriere
from persistenta.file_repo_inchirieri import FileRepoInchirieri
from persistenta.repos_filme import RepoFilm
from persistenta.file_repo_filme import FileRepoFilme
from persistenta.repos_clienti import RepoClient
from persistenta.file_repo_clienti import FileRepoClienti
from business.servicii_inchirieri import ServiceInchiriere
from domain.data_transfer_objects.inchirieriDTO import InchiriereDTO

class TesteInchirieri(object):

    def __init__(self):
        client = Client(68,"Andrei","1020405118923")
        film = Film(56,"Titanic","Drama","Un mare clasic")
        self.__repo_filme = RepoFilm()
        self.__repo_clienti = RepoClient()
        self.__repo_filme.adauga_film(film)
        self.__repo_clienti.adauga_client(client)
        self.__id_inchiriere = 36
        self.__client = client
        self.__film = film
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"
        self.__file_path = "test.txt"

        self.__inchiriere_dto = InchiriereDTO(self.__id_inchiriere, self.__client.get_id_client(), self.__film.get_id_film(), self.__data_inchiriere, self.__status_inchiriere)
        self.__inchiriere = Inchiriere(self.__id_inchiriere,self.__client,self.__film,self.__data_inchiriere, self.__status_inchiriere)

    def __ruleaza_teste_domeniu_inchirieri(self):
        assert(self.__inchiriere.get_id_inchiriere() == self.__id_inchiriere)
        assert(self.__inchiriere.get_film_inchiriere() == self.__film)
        assert(self.__inchiriere.get_client_inchiriere() == self.__client)
        assert(self.__inchiriere.get_data_inchiriere() == self.__data_inchiriere)

        clona_inchiriere = Inchiriere(self.__id_inchiriere, self.__client, self.__film, self.__data_inchiriere, self.__status_inchiriere)
        assert(self.__inchiriere == clona_inchiriere)
        assert(self.__inchiriere.__eq__(clona_inchiriere))
        assert(self.__inchiriere.__str__() == "[36] (12/05/2022) Andrei - Titanic")

    def __ruleaza_teste_validare_inchiriere(self):
        self.__validator_inchiriere = ValidatorInchiriere()
        self.__validator_inchiriere.valideaza(self.__inchiriere)
        self.__id_inchiriere_invalida = -23
        self.__data_invalida = "32/04/2021"
        self.__inchiriere_invalida = Inchiriere(self.__id_inchiriere_invalida, self.__client, self.__film,
                                                self.__data_invalida, self.__status_inchiriere)
        try:
            self.__validator_inchiriere.valideaza(self.__inchiriere_invalida)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "id invalid!\ndata invalida!\n")


    def __ruleaza_teste_repo_inchirieri(self):
        self.__repo_inchirieri = RepoInchiriere()
        assert(len(self.__repo_inchirieri) == 0)
        assert(self.__repo_inchirieri.__len__() == 0)
        self.__repo_inchirieri.adauga_inchiriere(self.__inchiriere_dto)
        assert(len(self.__repo_inchirieri) == 1)
        inchiriere_gasita = self.__repo_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere)
        assert(inchiriere_gasita.get_data_inchiriere() == self.__inchiriere.get_data_inchiriere())
        #print(self.__inchiriere_dto.get_status_inchiriere())
        try:
            self.__repo_inchirieri.adauga_inchiriere(self.__inchiriere)
            assert False
        except RepoError as re:
            assert(str(re) == "inchiriere existenta!")

        self.__id_inchiriere_inexistenta = 101
        try:
            self.__repo_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere_inexistenta)
            assert False
        except RepoError as re:
            assert(str(re) == "inchiriere inexistenta!")

        self.__data_inchiriere_nou = "12/12/2022"
        self.__inchiriere_modificata = InchiriereDTO(self.__id_inchiriere, self.__client.get_id_client(), self.__film.get_id_film(), self.__data_inchiriere_nou, self.__status_inchiriere)
        self.__repo_inchirieri.modifica_inchiriere(self.__inchiriere_modificata)
        assert (len(self.__repo_inchirieri) == 1)
        inchiriere_gasita = self.__repo_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere)
        assert(inchiriere_gasita.get_data_inchiriere() == self.__data_inchiriere_nou)


        self.__inchiriere_inexistenta = InchiriereDTO(self.__id_inchiriere_inexistenta,self.__client.get_id_client(),self.__film.get_id_film(),None,"True")
        try:
            self.__repo_inchirieri.modifica_inchiriere(self.__inchiriere_inexistenta)
            assert False
        except RepoError as re:
            assert(str(re) == "inchiriere inexistenta!")

        self.__client_nou = Client(24, "George", "1041108307892")
        self.__film_nou = Film(89, "Interstellar", "Sci-Fi", "De neratat")
        self.__repo_clienti.adauga_client(self.__client_nou)
        self.__repo_filme.adauga_film(self.__film_nou)
        self.__alta_inchiriere = InchiriereDTO(self.__id_inchiriere_inexistenta, self.__client_nou.get_id_client(), self.__film_nou.get_id_film(),self.__data_inchiriere_nou,self.__status_inchiriere)
        self.__repo_inchirieri.adauga_inchiriere(self.__alta_inchiriere)
        assert(len(self.__repo_inchirieri) ==2)
        inchirieri = self.__repo_inchirieri.get_all_inchirieri()
        assert(len(inchirieri) ==2)


        self.__id_alta_inchiriere = 11
        self.__repo_inchirieri.sterge_inchiriere_dupa_id(self.__id_inchiriere)
        assert(len(self.__repo_inchirieri) ==1)
        try:
            self.__repo_inchirieri.sterge_inchiriere_dupa_id(self.__id_inchiriere)
            assert False
        except RepoError as re:
            assert(str(re) == "inchiriere inexistenta!")



    def __ruleaza_teste_service_inchirieri(self):
        self.__repo_inchirieri = RepoInchiriere()
        self.__service_inchirieri = ServiceInchiriere(self.__repo_inchirieri,self.__validator_inchiriere,self.__repo_clienti,
                                                      self.__repo_filme,self.__file_path)
        assert(self.__service_inchirieri.size() ==0)
        self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere,self.__status_inchiriere)
        assert(self.__service_inchirieri.size() ==1)
        inchiriere_gasita = self.__service_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere)
        assert(inchiriere_gasita.get_data_inchiriere() == self.__data_inchiriere)
        try:
            self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere,self.__client_nou.get_id_client(),self.__film_nou.get_id_film(),self.__data_inchiriere_nou,self.__status_inchiriere)
            assert False
        except RepoError as re:
            assert(str(re) == "inchiriere existenta!")

        try:
            self.__service_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere_inexistenta)
            assert False
        except RepoError as re:
            assert (str(re) == "inchiriere inexistenta!")
        try:
            self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere_invalida,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_invalida,self.__status_inchiriere)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "id invalid!\ndata invalida!\n" )


        try:
            self.__service_inchirieri.modifica_inchiriere(self.__id_inchiriere_inexistenta,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere_nou)
            assert False
        except RepoError as re:
            assert(str(re) == "inchiriere inexistenta!")

        self.__service_inchirieri.modifica_inchiriere(self.__id_inchiriere,self.__client_nou.get_id_client(),self.__film_nou.get_id_film(),self.__data_inchiriere_nou)
        inchiriere_gasita = self.__service_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere)
        assert(inchiriere_gasita.get_data_inchiriere() == self.__data_inchiriere_nou)

        try:
            self.__service_inchirieri.sterge_inchiriere_dupa_id(self.__id_inchiriere_inexistenta)
            assert False
        except RepoError as re:
            assert (str(re) == "inchiriere inexistenta!")

        self.__service_inchirieri.sterge_inchiriere_dupa_id(self.__id_inchiriere)
        assert(self.__service_inchirieri.size() == 0)


    def __ruleaza_teste_rapoarte_inchirieri(self):
        self.__repo_inchirieri = RepoInchiriere()
        self.__service_inchirieri = ServiceInchiriere(self.__repo_inchirieri, self.__validator_inchiriere,
                                                      self.__repo_clienti, self.__repo_filme,self.__file_path)
        self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere, self.__client.get_id_client(),
                                                    self.__film.get_id_film(), self.__data_inchiriere,self.__status_inchiriere)

        self.__client_1 = Client(127, "Vlad", "1090807113413")
        self.__film_1 = Film(158, "Interstellar", "Sci-Fi", "De neratat")
        self.__repo_filme.adauga_film(self.__film_1)
        self.__repo_clienti.adauga_client(self.__client_1)

        self.__client_2 = Client(44, "Andreea", "2050603028934")
        self.__film_2 = Film(4, "Avatar", "Fantasy", "Un blockbuster reusit")
        self.__repo_filme.adauga_film(self.__film_2)
        self.__repo_clienti.adauga_client(self.__client_2)

        self.__service_inchirieri.adauga_inchiriere(421, self.__client_1.get_id_client(),
                                                    self.__film_1.get_id_film(), "04/08/2021", self.__status_inchiriere)
        self.__service_inchirieri.adauga_inchiriere(200, self.__client_2.get_id_client(),
                                                    self.__film_2.get_id_film(), "03/11/2019", self.__status_inchiriere)

        self.__service_inchirieri.adauga_inchiriere(307, self.__client_1.get_id_client(),
                                                    self.__film_2.get_id_film(), "14/02/2019", self.__status_inchiriere)

        rez = self.__service_inchirieri.sorteaza_clienti_nr_filme_inchiriate()
        #print(rez)
        client_situatie = rez[0]
        assert(client_situatie.get_client_situatie().get_id_client() == self.__client_1.get_id_client())

        rez_1 = self.__service_inchirieri.sorteaza_clienti_nume()
        assert(rez_1[0].get_client_situatie().get_nume_client() == self.__client_2.get_nume_client())

        rez_2 = self.__service_inchirieri.sorteaza_filme_cele_mai_inchiriate()
        #print(rez_2)
        lista = self.__service_inchirieri.get_all_inchirieri()
        #for film in rez_2:
        #    print(film)
        assert(rez_2[0].get_film_situatie().get_titlu_film() == self.__film_2.get_titlu_film())


    def __clear_file(self,file_path):
        with open(file_path,"w") as f:
            pass
        f.close()

    def __ruleaza_teste_file_repo_inchireri(self):
        file_path = "teste/teste_inchirieri.txt"
        file_repo_filme = FileRepoFilme("teste/teste_filme.txt")
        file_repo_clienti = FileRepoClienti("teste/teste_clienti.txt")
        self.__clear_file(file_path)
        self.__file_repo_inchirieri = FileRepoInchirieri(file_path)
        assert(self.__file_repo_inchirieri.size() == 0)

        #file_client = Client(87, "Diana", "2030609038743")
        #self.__file_repo_clienti.adauga_client(file_client)

        #file_film = Film(31, "Titanic", "Drama", "Un mare clasic")
        #self.__file_repo_filme.adauga_film(file_film)

        file_client = file_repo_clienti.cauta_client_dupa_id(87)
        file_film = file_repo_filme.cauta_film_dupa_id(31)

        file_inchiriere = InchiriereDTO(24, file_client.get_id_client(), file_film.get_id_film(), "10/10/2020", self.__status_inchiriere)
        self.__file_repo_inchirieri.adauga_inchiriere(file_inchiriere)
        #print(file_inchiriere.get_status_inchiriere())
        assert(self.__file_repo_inchirieri.size() == 1)

        inchiriere = InchiriereDTO(52, file_client.get_id_client(), file_film.get_id_film(), "10/12/2020", self.__status_inchiriere)
        self.__file_repo_inchirieri.adauga_inchiriere(inchiriere)
        assert(self.__file_repo_inchirieri.size() == 2)

        #file_repo_filme.sterge_film_dupa_id(31)
        #assert(file_repo_inchirieri.size() == 0)





    def ruleaza_toate_testele_inchirieri(self):
        print("ruleaza teste domeniu inchirieri...")
        self.__ruleaza_teste_domeniu_inchirieri()
        print("teste domeniu inchirieri terminate cu succes!")
        print("ruleaza teste validare inchirieri...")
        self.__ruleaza_teste_validare_inchiriere()
        print("teste validare inchirieri terminate cu succes!")
        print("ruleaza teste repositories inchirieri...")
        self.__ruleaza_teste_repo_inchirieri()
        print("teste repositories inchirieri trecute cu succes!")
        print("ruleaza teste servicii inchirieri...")
        self.__ruleaza_teste_service_inchirieri()
        print("teste servicii inchirieri trecute cu succes!")
        print("ruleaza teste rapoarte inchirieri...")
        self.__ruleaza_teste_rapoarte_inchirieri()
        print("teste rapoarte inchirieri trecute cu succes!")
        print("ruleaza teste file repo inchirieri...")
        self.__ruleaza_teste_file_repo_inchireri()
        print("teste file repo inchirieri trecute cu succes!")
