import unittest
from erori.exceptii import ValidationError,RepoError
from domain.filme import Film
from persistenta.repos_inchirieri import RepoInchiriere
from persistenta.repos_filme import RepoFilm
from persistenta.file_repo_filme import FileRepoFilme
from validare.validator_filme import ValidatorFilm
from business.servicii_filme import ServiceFilm


class TesteFilm(unittest.TestCase):

    def setUp(self):
        self.__repo_filme = FileRepoFilme("teste_pyunit_filme.txt")
        self.__validator_film = ValidatorFilm()
        self.__repo_inchirieri = RepoInchiriere()
        self.__service_filme = ServiceFilm(self.__repo_filme,self.__validator_film,self.__repo_inchirieri)

    def tearDown(self):
        #pass
        with open("teste_pyunit_filme.txt", "w") as f:
            pass
        f.close()

    # ----------  WHITEBOX TESTING -----------
    def test_domeniu_filme(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.__film = Film(self.__id_film, self.__titlu_film, self.__gen_film,self.__descriere_film)

        self.assertTrue(self.__film.get_id_film() == self.__id_film)
        self.assertTrue(self.__film.get_titlu_film() == self.__titlu_film)
        self.assertTrue(self.__film.get_gen_film() == self.__gen_film)
        self.assertTrue(self.__film.get_descriere_film() == self.__descriere_film)

        self.assertFalse(self.__film.get_id_film() == 22)
        self.assertFalse(self.__film.get_titlu_film() == "Interstellar")

        self.__clona_film = Film(self.__id_film, self.__titlu_film, self.__gen_film,self.__descriere_film)
        self.assertTrue(self.__film == self.__clona_film)
        self.assertTrue(self.__film.__str__() == "[27] Titanic (Un mare clasic) - Drama")


    def test_validare_film(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.__film = Film(self.__id_film, self.__titlu_film, self.__gen_film, self.__descriere_film)
        self.assertTrue(self.__validator_film.valideaza(self.__film) == None)

        self.__id_film_invalid = -23
        self.__titlu_film_invalid = ""
        self.__descriere_invalida = ""
        self.__gen_invalid = "a"
        self.__film_invalid = Film(self.__id_film_invalid, self.__titlu_film_invalid, self.__gen_invalid,self.__descriere_invalida)

        with self.assertRaises(ValidationError) as ve:
            self.__validator_film.valideaza(self.__film_invalid)

        self.assertEqual(str(ve.exception), "id invalid!\ntitlu invalid!\ngen invalid!\ndescriere invalida!\n")


    def test_adaugare_repo_filme(self):
        self.assertTrue(len(self.__repo_filme) == 0)

        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.__film = Film(self.__id_film, self.__titlu_film, self.__gen_film, self.__descriere_film)

        self.assertTrue(self.__repo_filme.adauga_film(self.__film) == None)
        self.assertTrue(len(self.__repo_filme) == 1)

        self.__id_film_nou = 31
        self.__titlu_film_nou = "Interstellar"
        self.__gen_film_nou = "Sci-Fi"
        self.__descriere_film_nou = "De neratat"
        self.__alt_film = Film(self.__id_film_nou,self.__titlu_film_nou,self.__gen_film_nou,self.__descriere_film_nou)

        self.assertTrue(self.__repo_filme.adauga_film(self.__alt_film) == None)
        self.assertTrue(len(self.__repo_filme) == 2)

        with self.assertRaises(RepoError) as re:
            self.__repo_filme.adauga_film(self.__alt_film)
        self.assertEqual(str(re.exception), "film existent!")


    def test_cautare_repo_filme(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.__film = Film(self.__id_film, self.__titlu_film, self.__gen_film, self.__descriere_film)

        self.assertTrue(self.__repo_filme.adauga_film(self.__film) == None)

        film_gasit = self.__repo_filme.cauta_film_dupa_id(self.__id_film)
        self.assertTrue(film_gasit.get_titlu_film() == self.__film.get_titlu_film())
        self.assertTrue(film_gasit.get_gen_film() == self.__film.get_gen_film())

        self.__id_film_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__repo_filme.cauta_film_dupa_id(self.__id_film_inexistent)
        self.assertEqual(str(re.exception), "film inexistent!")


    def test_modifica_repo_filme(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.__film = Film(self.__id_film, self.__titlu_film, self.__gen_film, self.__descriere_film)

        self.assertTrue(self.__repo_filme.adauga_film(self.__film) == None)

        self.__titlu_film_nou = "Interstellar"
        self.__gen_film_nou = "Sci-Fi"
        self.__film_modificat = Film(self.__id_film,self.__titlu_film_nou,self.__gen_film_nou,self.__descriere_film)
        self.assertTrue(self.__repo_filme.modifica_film(self.__film_modificat) == None)

        film_gasit = self.__repo_filme.cauta_film_dupa_id(self.__id_film)
        self.assertTrue(film_gasit.get_titlu_film() == self.__titlu_film_nou)
        self.assertTrue(film_gasit.get_gen_film() == self.__gen_film_nou)

        self.__id_film_inexistent = 101
        self.__film_inexistent = Film(self.__id_film_inexistent,"Avatar","Fantasy","O productie de milioane")
        with self.assertRaises(RepoError) as re:
            self.__repo_filme.modifica_film(self.__film_inexistent)
        self.assertEqual(str(re.exception), "film inexistent!")


    def test_stergere_repo_filme(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.__film = Film(self.__id_film, self.__titlu_film, self.__gen_film, self.__descriere_film)

        self.assertTrue(self.__repo_filme.adauga_film(self.__film) == None)

        self.assertTrue(self.__repo_filme.sterge_film_dupa_id(self.__id_film) == None)
        self.assertTrue(len(self.__repo_filme) == 0)

        with self.assertRaises(RepoError) as re:
            self.__repo_filme.sterge_film_dupa_id(self.__id_film)
        self.assertEqual(str(re.exception), "film inexistent!")


    def test_adaugare_service_filme(self):
        self.assertTrue(self.__service_filme.size() == 0)
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.assertTrue(self.__service_filme.adauga_film(self.__id_film,self.__titlu_film,self.__gen_film,self.__descriere_film) == None)
        self.assertTrue(self.__service_filme.size() == 1)

        with self.assertRaises(RepoError) as re:
            self.__service_filme.adauga_film(self.__id_film,self.__titlu_film,self.__gen_film,self.__descriere_film)
        self.assertEqual(str(re.exception), "film existent!")

        self.__id_film_invalid = -19
        self.__titlu_film_invalid = ""
        self.__gen_film_invalid = "a"
        self.__descriere_invalida = ""
        with self.assertRaises(ValidationError) as ve:
            self.__service_filme.adauga_film(self.__id_film_invalid,self.__titlu_film_invalid,self.__gen_film_invalid,self.__descriere_invalida)
        self.assertEqual(str(ve.exception), "id invalid!\ntitlu invalid!\ngen invalid!\ndescriere invalida!\n")


    def test_cautare_service_filme(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.assertTrue(self.__service_filme.adauga_film(self.__id_film, self.__titlu_film, self.__gen_film,self.__descriere_film) == None)

        film_gasit = self.__service_filme.cauta_film_dupa_id(self.__id_film)
        self.assertTrue(film_gasit.get_titlu_film() == self.__titlu_film)

        self.__id_film_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__service_filme.cauta_film_dupa_id(self.__id_film_inexistent)
        self.assertEqual(str(re.exception), "film inexistent!")


    def test_modifica_service_filme(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.assertTrue(self.__service_filme.adauga_film(self.__id_film, self.__titlu_film, self.__gen_film,self.__descriere_film) == None)

        self.__id_film_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__service_filme.modifica_film(self.__id_film_inexistent,"Avatar","Fantasy","Capodopera")
        self.assertEqual(str(re.exception), "film inexistent!")

        self.__titlu_film_nou = "Interstellar"
        self.__gen_film_nou = "Sci-Fi"
        self.__descriere_film_nou = "De neratat"
        self.assertTrue(self.__service_filme.modifica_film(self.__id_film,self.__titlu_film_nou,self.__gen_film_nou,self.__descriere_film_nou) == None)

        film_gasit = self.__service_filme.cauta_film_dupa_id(self.__id_film)
        self.assertTrue(film_gasit.get_titlu_film() == self.__titlu_film_nou)


    def test_stergere_service_filme(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.assertTrue(self.__service_filme.adauga_film(self.__id_film, self.__titlu_film, self.__gen_film,self.__descriere_film) == None)

        self.__id_film_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__service_filme.sterge_film_dupa_id(self.__id_film_inexistent)
        self.assertEqual(str(re.exception), "film inexistent!")

        self.assertTrue(self.__service_filme.sterge_film_dupa_id(self.__id_film) == None)
        self.assertTrue(self.__service_filme.size() == 0)


    # -------- BLACK BOX TESTING --------

    def test_adaugare_film_blackbox(self):
        self.__id_film = 27
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.assertTrue(self.__service_filme.adauga_film(self.__id_film, self.__titlu_film, self.__gen_film,self.__descriere_film) == None)

        with self.assertRaises(RepoError) as re:
            self.__service_filme.adauga_film(self.__id_film,self.__titlu_film,self.__gen_film,self.__descriere_film)
        self.assertEqual(str(re.exception), "film existent!")

        with self.assertRaises(ValidationError) as ve:
            self.__service_filme.adauga_film(56,"a","","O capodopera")
        self.assertEqual(str(ve.exception), "titlu invalid!\ngen invalid!\n")