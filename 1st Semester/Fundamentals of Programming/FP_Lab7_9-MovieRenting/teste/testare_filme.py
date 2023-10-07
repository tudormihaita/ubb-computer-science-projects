from domain.filme import Film
from erori.exceptii import ValidationError, RepoError
from validare.validator_filme import ValidatorFilm
from persistenta.repos_filme import RepoFilm
from persistenta.file_repo_filme import FileRepoFilme
from persistenta.repos_inchirieri import RepoInchiriere
from business.servicii_filme import ServiceFilm

class TesteFilme(object):

    def __init__(self):
        self.__id_film = 54
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        #self.__string_descriere = ""
        #for cuvant in self.__descriere_film:
            #self.__string_descriere = self.__string_descriere + cuvant + " "
        self.__film = Film(self.__id_film,self.__titlu_film,self.__gen_film,self.__descriere_film)


    def __ruleaza_teste_domeniu_filme(self):
        #print(self.__film.get_descriere_film())
        assert(self.__film.get_id_film() == self.__id_film)
        assert(self.__film.get_titlu_film() == self.__titlu_film)
        assert(self.__film.get_descriere_film() == self.__descriere_film)
        assert(self.__film.get_gen_film() == self.__gen_film)

        clona_film = Film(self.__id_film,self.__titlu_film,self.__gen_film,self.__descriere_film)
        assert(self.__film == clona_film)
        assert(self.__film.__eq__(clona_film))
        assert(self.__film.__str__() == "[54] Titanic (Un mare clasic) - Drama")

    def __ruleaza_teste_validare_film(self):
        self.__validator_film = ValidatorFilm()
        self.__validator_film.valideaza(self.__film)
        self.__id_film_invalid = -23
        self.__titlu_film_invalid = ""
        self.__descriere_invalida = ""
        self.__gen_invalid = "a"
        self.__film_invalid = Film(self.__id_film_invalid, self.__titlu_film_invalid, self.__gen_invalid, self.__descriere_invalida)
        try:
            self.__validator_film.valideaza(self.__film_invalid)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "id invalid!\ntitlu invalid!\ngen invalid!\ndescriere invalida!\n")


    def __ruleaza_teste_repo_filme(self):
        self.__repo_filme = RepoFilm()
        assert(len(self.__repo_filme) == 0)
        assert(self.__repo_filme.__len__() ==0)
        self.__repo_filme.adauga_film(self.__film)
        assert(len(self.__repo_filme) == 1)
        film_gasit = self.__repo_filme.cauta_film_dupa_id(self.__id_film)
        assert(film_gasit.get_titlu_film() == self.__film.get_titlu_film())
        try:
            self.__repo_filme.adauga_film(self.__film)
            assert False
        except RepoError as re:
            assert(str(re) == "film existent!")

        self.__id_film_inexistent = 101
        try:
            self.__repo_filme.cauta_film_dupa_id(self.__id_film_inexistent)
            assert False
        except RepoError as re:
            assert(str(re) == "film inexistent!")

        self.__titlu_film_nou = "Oceans Eleven"
        self.__descriere_film_noua = "Recunoscut international"
        self.__gen_film_nou = "Actiune"
        self.__film_modificat = Film(self.__id_film, self.__titlu_film_nou, self.__gen_film_nou, self.__descriere_film_noua)
        self.__repo_filme.modifica_film(self.__film_modificat)
        assert (len(self.__repo_filme) == 1)
        film_gasit = self.__repo_filme.cauta_film_dupa_id(self.__id_film)
        assert(film_gasit.get_titlu_film() == self.__titlu_film_nou)
        assert(film_gasit.get_gen_film() == self.__gen_film_nou)

        self.__film_inexistent = Film(self.__id_film_inexistent,None,None,None)
        try:
            self.__repo_filme.modifica_film(self.__film_inexistent)
            assert False
        except RepoError as re:
            assert(str(re) == "film inexistent!")

        self.__alt_film = Film(self.__id_film_inexistent,self.__titlu_film_nou,self.__gen_film_nou,self.__descriere_film_noua)
        self.__repo_filme.adauga_film(self.__alt_film)
        assert(len(self.__repo_filme) ==2)
        filme = self.__repo_filme.get_all_filme()
        assert(len(filme) ==2)
        self.__repo_filme.sterge_film_dupa_id(self.__id_film)
        assert(len(self.__repo_filme) ==1)
        try:
            self.__repo_filme.sterge_film_dupa_id(self.__id_film)
            assert False
        except RepoError as re:
            assert(str(re) == "film inexistent!")


    def __ruleaza_teste_service_filme(self):
        self.__repo_filme = RepoFilm()
        self.__repo_inchirieri = RepoInchiriere()
        self.__service_filme = ServiceFilm(self.__repo_filme,self.__validator_film,self.__repo_inchirieri)
        assert(self.__service_filme.size() ==0)
        self.__service_filme.adauga_film(self.__id_film,self.__titlu_film,self.__gen_film,self.__descriere_film)
        assert(self.__service_filme.size() ==1)
        film_gasit = self.__service_filme.cauta_film_dupa_id(self.__id_film)
        assert(film_gasit.get_titlu_film() == self.__titlu_film)
        try:
            self.__service_filme.adauga_film(self.__id_film,"Matrix","Clasic","Actiune")
            assert False
        except RepoError as re:
            assert(str(re) == "film existent!")

        try:
            self.__service_filme.cauta_film_dupa_id(self.__id_film_inexistent)
            assert False
        except RepoError as re:
            assert (str(re) == "film inexistent!")
        try:
            self.__service_filme.adauga_film(self.__id_film_invalid,self.__titlu_film_invalid,self.__gen_invalid,self.__descriere_invalida)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "id invalid!\ntitlu invalid!\ngen invalid!\ndescriere invalida!\n" )

        try:
            self.__service_filme.modifica_film(self.__id_film_inexistent,"Matrix","Actiune","Clasic")
            assert False
        except RepoError as re:
            assert(str(re) == "film inexistent!")

        self.__service_filme.modifica_film(self.__id_film,self.__titlu_film_nou,self.__gen_film_nou,self.__descriere_film_noua)
        film_gasit = self.__service_filme.cauta_film_dupa_id(self.__id_film)
        assert(film_gasit.get_titlu_film() == self.__titlu_film_nou)
        try:
            self.__service_filme.sterge_film_dupa_id(self.__id_film_inexistent)
            assert False
        except RepoError as re:
            assert (str(re) == "film inexistent!")

        self.__service_filme.sterge_film_dupa_id(self.__id_film)
        assert(self.__service_filme.size() ==0)


    def __clear_file(self,file_path):
        with open(file_path,"w") as f:
            pass
        f.close()

    def __ruleaza_teste_file_repo_filme(self):
        file_path = "teste/teste_filme.txt"
        self.__clear_file(file_path)
        file_repo_filme = FileRepoFilme(file_path)
        assert(file_repo_filme.size() == 0)
        film = Film(31,"Titanic","Drama","Un mare clasic")
        file_repo_filme.adauga_film(film)
        assert (file_repo_filme.size() == 1)


    def ruleaza_toate_testele_filme(self):
        print("ruleaza teste domeniu filme...")
        self.__ruleaza_teste_domeniu_filme()
        print("teste domeniu filme terminate cu succes!")
        print("ruleaza teste validare filme...")
        self.__ruleaza_teste_validare_film()
        print("teste validare filme terminate cu succes!")
        print("ruleaza teste repositories filme...")
        self.__ruleaza_teste_repo_filme()
        print("teste repositories filme trecute cu succes!")
        print("ruleaza teste servicii filme...")
        self.__ruleaza_teste_service_filme()
        print("teste servicii filme trecute cu succes!")
        print("ruleaza teste file repo filme...")
        self.__ruleaza_teste_file_repo_filme()
        print("teste file repo filme trecute cu succes!")
