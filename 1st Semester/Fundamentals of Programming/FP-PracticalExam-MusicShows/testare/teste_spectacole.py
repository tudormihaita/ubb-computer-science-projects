from domain.spectacole import Spectacol
from erori.exceptii import RepoError,ValidationError
from repositories.repo_spectacole import RepoSpectacole
from controller.service_spectacole import ServiceSpectacole
from validator.validare_spectacole import ValidareSpectacole

class TestareSpectacole(object):

    def __init__(self):
        self.__titlu = "Vizita"
        self.__artist = "I. L. Caragiale"
        self.__gen = "Comedie"
        self.__durata = 4500
        self.__spectacol = Spectacol(self.__titlu,self.__artist, self.__gen, self.__durata)

    def __ruleaza_teste_domain_spectacole(self):
        assert(self.__spectacol.get_artist_spectacol() == self.__artist)
        assert(self.__spectacol.get_titlu_spectacol() == self.__titlu)
        assert(self.__spectacol.get_gen_spectacol() == self.__gen)
        assert(self.__spectacol.get_durata_spectacol() == self.__durata)
        clona_spectacol = Spectacol(self.__titlu,self.__artist,self.__gen,self.__durata)

        assert(self.__spectacol == clona_spectacol)
        assert(self.__spectacol.__str__() == "Vizita I. L. Caragiale Comedie 4500")

    def __ruleaza_teste_validare_spectacole(self):
        self.__validator_spectacole = ValidareSpectacole()
        self.__validator_spectacole.valideaza(self.__spectacol)

        spectacol_invalid = Spectacol("Back in Black", "", "Concert", -900)
        try:
            self.__validator_spectacole.valideaza(spectacol_invalid)
        except ValidationError as ve:
            assert(str(ve) == "Nume artist nevid!\nDurata trebuie sa fie intreg pozitiv!\n")

    def __ruleaza_teste_repo_spectacole(self):
        self.__file_path = "testare/teste_spectacole.txt"
        self.__repo_spectacole = RepoSpectacole(self.__file_path)
        self.__repo_spectacole.clear_file()
        self.__repo_spectacole.adauga_spectacol(self.__spectacol)
        assert(len(self.__repo_spectacole.get_all_spectacole()) == 1)

        try:
            self.__repo_spectacole.adauga_spectacol(self.__spectacol)
            assert False
        except RepoError as re:
            assert(str(re) == "Spectacol deja existent!\n")

    def __ruleaza_teste_service_spectacole(self):
        self.__file_path = "testare/teste_spectacole.txt"
        self.__repo_spectacole = RepoSpectacole(self.__file_path)
        self.__repo_spectacole.clear_file()
        self.__validator_spectacole = ValidareSpectacole()
        self.__service_spectacole = ServiceSpectacole(self.__repo_spectacole, self.__validator_spectacole)

        assert(self.__service_spectacole.size() == 0)
        self.__service_spectacole.adauga_spectacol(self.__titlu, self.__artist, self.__gen, self.__durata)
        assert(self.__service_spectacole.size() == 1)
        lista_spectacole = self.__service_spectacole.get_all_spectacole()
        assert(len(lista_spectacole) == 1)

        titlu_invalid = ""
        artist_invalid = ""
        gen_invalid = "Drama"
        durata_invalida = -700
        try:
            self.__service_spectacole.adauga_spectacol(titlu_invalid, artist_invalid, gen_invalid, durata_invalida)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "Titlu nevid!\nNume artist nevid!\nDurata trebuie sa fie intreg pozitiv!\nGenul trebuie sa fie unul dintre: Comedie, Concert, Balet, Altele!\n")

        durata_noua = 6780
        gen_nou = "Altele"
        self.__service_spectacole.modifica_spectacol(self.__titlu, self.__artist, gen_nou, durata_noua)
        spectacol_modificat = self.__service_spectacole.cauta_spectacol(self.__titlu, self.__artist)
        assert(spectacol_modificat.get_durata_spectacol() == durata_noua)
        assert(spectacol_modificat.get_gen_spectacol() == gen_nou)

        titlu_inexistent = "Dl. Goe"
        artist_inexistent = "I. L. Caragiale"
        try:
            self.__service_spectacole.modifica_spectacol(titlu_inexistent, artist_inexistent, gen_nou, durata_noua)
            assert False
        except RepoError as re:
            assert(str(re) == "Spectacol inexistent!\n")

        titlu1 = "Highway To Hell"
        artist1 = "AC/DC"
        gen1 = "Concert"
        durata1 = 4780
        test_path = "testare/test_export.txt"

        self.__service_spectacole.adauga_spectacol(titlu1, artist1, gen1, durata1)
        #assert(self.__service_spectacole.exporta_spectacole_sortate(test_path) == None)
        lista_sortata = self.__service_spectacole.exporta_spectacole_sortate(test_path)
        assert(lista_sortata[0].get_artist_spectacol() == artist1)

        nr_generari = 2
        assert(self.__service_spectacole.size() == 2)
        self.__service_spectacole.genereaza_spectacole(nr_generari)
        assert(self.__service_spectacole.size() == 4)


    def ruleaza_toate_testele(self):
        print("ruleaza teste domain spectacole...")
        self.__ruleaza_teste_domain_spectacole()
        print("teste domain spectacole trecute cu succes!")
        print("ruleaza teste validator spectacole...")
        self.__ruleaza_teste_validare_spectacole()
        print("teste validate spectacole trecute cu succes!")
        print("ruleaza teste repo spectacole...")
        self.__ruleaza_teste_repo_spectacole()
        print("teste repo spectacole trecute cu succes!")
        print("ruleaza teste service spectacole...")
        self.__ruleaza_teste_service_spectacole()
        print("teste service spectacole trecute cu succes!")