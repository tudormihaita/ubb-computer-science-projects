from domain.clienti import Client
from erori.exceptii import ValidationError, RepoError
from validare.validator_clienti import ValidatorClient
from persistenta.repos_clienti import RepoClient
from persistenta.file_repo_clienti import FileRepoClienti
from persistenta.repos_inchirieri import RepoInchiriere
from business.servicii_clienti import ServiceClient

class TesteClienti(object):

    def __init__(self):
        self.__id_client = 98
        self.__nume_client = "Andrei"
        self.__cnp_client = "1050408375201"
        self.__client = Client(self.__id_client,self.__nume_client,self.__cnp_client)


    def __ruleaza_teste_domeniu_clienti(self):
        assert(self.__client.get_id_client() == self.__id_client)
        assert(self.__client.get_nume_client() == self.__nume_client)
        assert(self.__client.get_cnp_client() == self.__cnp_client)

        clona_client = Client(self.__id_client,self.__nume_client,self.__cnp_client)
        assert(self.__client == clona_client)
        assert(self.__client.__eq__(clona_client))
        assert(self.__client.__str__() == "[98] Andrei - (1050408375201)")

    def __ruleaza_teste_validare_client(self):
        self.__validator_client = ValidatorClient()
        self.__validator_client.valideaza(self.__client)
        self.__id_client_invalid = -78
        self.__nume_client_invalid = ""
        self.__cnp_client_invalid = "12345"
        self.__client_invalid = Client(self.__id_client_invalid, self.__nume_client_invalid, self.__cnp_client_invalid)
        try:
            self.__validator_client.valideaza(self.__client_invalid)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "id invalid!\nnume invalid!\ncnp invalid!\n")


    def __ruleaza_teste_repo_clienti(self):
        self.__repo_clienti = RepoClient()
        assert(len(self.__repo_clienti) == 0)
        assert(self.__repo_clienti.__len__() ==0)
        self.__repo_clienti.adauga_client(self.__client)
        assert(len(self.__repo_clienti) == 1)
        client_gasit = self.__repo_clienti.cauta_client_dupa_id(self.__id_client)
        assert(client_gasit.get_nume_client() == self.__client.get_nume_client())
        try:
            self.__repo_clienti.adauga_client(self.__client)
            assert False
        except RepoError as re:
            assert(str(re) == "client existent!")

        self.__id_client_inexistent = 101
        try:
            self.__repo_clienti.cauta_client_dupa_id(self.__id_client_inexistent)
            assert False
        except RepoError as re:
            assert(str(re) == "client inexistent!")

        self.__nume_client_nou = "George"
        self.__cnp_client_nou = "3071104356403"
        self.__client_modificat = Client(self.__id_client, self.__nume_client_nou, self.__cnp_client_nou)
        self.__repo_clienti.modifica_client(self.__client_modificat)
        assert ( len(self.__repo_clienti) == 1)
        client_gasit = self.__repo_clienti.cauta_client_dupa_id(self.__id_client)
        assert(client_gasit.get_nume_client() == self.__nume_client_nou)
        assert(client_gasit.get_cnp_client() == self.__cnp_client_nou)

        self.__client_inexistent = Client(self.__id_client_inexistent,"Vlad","1020406211234")
        try:
            self.__repo_clienti.modifica_client(self.__client_inexistent)
            assert False
        except RepoError as re:
            assert(str(re) == "client inexistent!")

        ####
        self.__cnp = "2040506226784"
        self.__alt_client = Client(self.__id_client_inexistent,self.__nume_client_nou,self.__cnp)
        self.__repo_clienti.adauga_client(self.__alt_client)
        assert(len(self.__repo_clienti) ==2)
        clienti = self.__repo_clienti.get_all_clienti()
        assert(len(clienti) ==2)
        self.__repo_clienti.sterge_client_dupa_id(self.__id_client)
        assert(len(self.__repo_clienti) ==1)
        try:
            self.__repo_clienti.sterge_client_dupa_id(self.__id_client)
            assert False
        except RepoError as re:
            assert(str(re) == "client inexistent!")


    def __ruleaza_teste_service_clienti(self):
        self.__repo_clienti = RepoClient()
        self.__repo_inchirieri = RepoInchiriere()
        self.__service_clienti = ServiceClient(self.__repo_clienti,self.__validator_client,self.__repo_inchirieri)
        assert( self.__service_clienti.size() ==0)
        self.__service_clienti.adauga_client(self.__id_client,self.__nume_client,self.__cnp_client)
        assert(self.__service_clienti.size() ==1)
        client_gasit = self.__service_clienti.cauta_client_dupa_id(self.__id_client)
        assert(client_gasit.get_nume_client() == self.__nume_client)
        try:
            self.__service_clienti.adauga_client(self.__id_client,"Alex","1040806456702")
            assert False
        except RepoError as re:
            assert(str(re) == "client existent!")

        try:
            self.__service_clienti.cauta_client_dupa_id(self.__id_client_inexistent)
            assert False
        except RepoError as re:
            assert (str(re) == "client inexistent!")
        try:
            self.__service_clienti.adauga_client(self.__id_client_invalid,self.__nume_client_invalid,self.__cnp_client_invalid)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "id invalid!\nnume invalid!\ncnp invalid!\n")

        try:
            self.__service_clienti.modifica_client(self.__id_client_inexistent,"Mircea","1060712456703")
            assert False
        except RepoError as re:
            assert(str(re) == "client inexistent!")

        self.__service_clienti.modifica_client(self.__id_client,self.__nume_client_nou,self.__cnp_client_nou)
        client_gasit = self.__service_clienti.cauta_client_dupa_id(self.__id_client)
        assert(client_gasit.get_nume_client() == self.__nume_client_nou)
        try:
            self.__service_clienti.sterge_client_dupa_id(self.__id_client_inexistent)
            assert False
        except RepoError as re:
            assert (str(re) == "client inexistent!")

        self.__service_clienti.sterge_client_dupa_id(self.__id_client)
        assert(self.__service_clienti.size() ==0)

    def __clear_file(self,file_path):
        with open(file_path,"w") as f:
            pass
        f.close()

    def __ruleaza_teste_file_repo_clienti(self):
        file_path = "teste/teste_clienti.txt"
        self.__clear_file(file_path)
        file_repo_clienti = FileRepoClienti(file_path)
        assert(file_repo_clienti.size() == 0)
        client = Client(87,"Diana","2030609038743")
        file_repo_clienti.adauga_client(client)
        assert (file_repo_clienti.size() == 1)

    def ruleaza_toate_testele_clienti(self):
        print("ruleaza teste domeniu clienti...")
        self.__ruleaza_teste_domeniu_clienti()
        print("teste domeniu clienti terminate cu succes!")
        print("ruleaza teste validare clienti...")
        self.__ruleaza_teste_validare_client()
        print("teste validare clienti terminate cu succes!")
        print("ruleaza teste repositories clienti...")
        self.__ruleaza_teste_repo_clienti()
        print("teste repositories clienti trecute cu succes!")
        print("ruleaza teste servicii clienti...")
        self.__ruleaza_teste_service_clienti()
        print("teste servicii clienti trecute cu succes!")
        print("ruleaza teste file repo clienti...")
        self.__ruleaza_teste_file_repo_clienti()
        print("teste file repo clienti trecute cu succes!")
