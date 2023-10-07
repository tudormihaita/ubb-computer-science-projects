import unittest
from erori.exceptii import ValidationError,RepoError
from domain.clienti import Client
from domain.filme import Film
from domain.inchirieri import Inchiriere
from persistenta.file_repo_inchirieri import FileRepoInchirieri
from persistenta.file_repo_clienti import FileRepoClienti
from persistenta.file_repo_filme import FileRepoFilme
from validare.validator_inchirieri import ValidatorInchiriere
from business.servicii_inchirieri import ServiceInchiriere
from domain.data_transfer_objects.inchirieriDTO import InchiriereDTO


class TesteClienti(unittest.TestCase):

    def setUp(self):
        self.__validator_inchiriere = ValidatorInchiriere()
        self.__repo_clienti = FileRepoClienti("teste_pyunit_clienti.txt")
        self.__repo_filme = FileRepoFilme("teste_pyunit_filme.txt")
        self.__repo_inchirieri = FileRepoInchirieri("teste_pyunit_inchirieri.txt")
        self.__service_inchirieri = ServiceInchiriere(self.__repo_inchirieri,self.__validator_inchiriere,self.__repo_clienti,self.__repo_filme,"test.txt")

        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.__client = Client(self.__id_client,self.__nume_client,self.__cnp_client)
        self.__repo_clienti.adauga_client(self.__client)

        self.__id_film = 31
        self.__titlu_film = "Titanic"
        self.__gen_film = "Drama"
        self.__descriere_film = "Un mare clasic"
        self.__film = Film(self.__id_film, self.__titlu_film, self.__gen_film, self.__descriere_film)

        self.__repo_filme.adauga_film(self.__film)



    def tearDown(self):
        # pass
        with open("teste_pyunit_inchirieri.txt", "w") as f:
            pass
        f.close()
        with open("teste_pyunit_clienti.txt", "w") as f:
            pass
        f.close()
        with open("teste_pyunit_filme.txt", "w") as f:
            pass
        f.close()

    # -------- WHITEBOX TESTING --------
    def test_domeniu_inchirieri(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"
        self.__inchiriere = Inchiriere(self.__id_inchiriere,self.__client,self.__film,self.__data_inchiriere, self.__status_inchiriere)

        self.assertTrue(self.__inchiriere.get_id_inchiriere() == self.__id_inchiriere)
        self.assertTrue(self.__inchiriere.get_client_inchiriere() == self.__client)
        self.assertTrue(self.__inchiriere.get_film_inchiriere() == self.__film)
        self.assertTrue(self.__inchiriere.get_data_inchiriere() == self.__data_inchiriere)

        clona_inchiriere = Inchiriere(self.__id_inchiriere,self.__client,self.__film,self.__data_inchiriere, self.__status_inchiriere)
        self.assertTrue(self.__inchiriere == clona_inchiriere)
        self.assertTrue(self.__inchiriere.__str__() == "[56] (12/05/2022) Andrei - Titanic")


    def test_validare_inchirieri(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"
        self.__inchiriere = Inchiriere(self.__id_inchiriere, self.__client, self.__film, self.__data_inchiriere, self.__status_inchiriere)

        self.assertTrue(self.__validator_inchiriere.valideaza(self.__inchiriere) == None)

        self.__id_inchiriere_invalida = -23
        self.__data_invalida = "32/04/2021"
        self.__inchiriere_invalida = Inchiriere(self.__id_inchiriere,self.__client,self.__film,self.__data_invalida, self.__status_inchiriere)

        with self.assertRaises(ValidationError) as ve:
            self.__validator_inchiriere.valideaza(self.__inchiriere_invalida)
        self.assertTrue(str(ve.exception),"id invalid!\ndata invalida!\n")


    def test_adaugare_repo_inchirieri(self):
        self.assertTrue(len(self.__repo_inchirieri) == 0)
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"
        self.__inchiriere = InchiriereDTO(self.__id_inchiriere, self.__client.get_id_client(), self.__film.get_id_film(), self.__data_inchiriere, self.__status_inchiriere)

        self.assertTrue(self.__repo_inchirieri.adauga_inchiriere(self.__inchiriere) == None)
        self.assertTrue(len(self.__repo_inchirieri) == 1)

        self.__id_inchiriere_nou = 47
        self.__data_inchiriere_nou = "04/08/2021"
        self.__inchiriere_nou = InchiriereDTO(self.__id_inchiriere_nou, self.__client.get_id_client(), self.__film.get_id_film(), self.__data_inchiriere_nou, self.__status_inchiriere)

        self.assertTrue(self.__repo_inchirieri.adauga_inchiriere(self.__inchiriere_nou) == None)
        self.assertTrue(len(self.__repo_inchirieri) == 2)

        with self.assertRaises(RepoError) as re:
            self.__repo_inchirieri.adauga_inchiriere(self.__inchiriere)
        self.assertEqual(str(re.exception),"inchiriere existenta!")


    def test_cautare_repo_inchirieri(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"
        self.__inchiriere = InchiriereDTO(self.__id_inchiriere, self.__client.get_id_client(), self.__film.get_id_film(), self.__data_inchiriere, self.__status_inchiriere)

        self.assertTrue(self.__repo_inchirieri.adauga_inchiriere(self.__inchiriere) == None)

        inchiriere_gasita = self.__repo_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere)
        self.assertTrue(inchiriere_gasita.get_id_client_inchiriere() == self.__client.get_id_client())
        self.assertTrue(inchiriere_gasita.get_data_inchiriere() == self.__inchiriere.get_data_inchiriere())


        self.__id_inchiriere_inexistenta = 101
        with self.assertRaises(RepoError) as re:
            self.__repo_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere_inexistenta)
        self.assertEqual(str(re.exception), "inchiriere inexistenta!")



    def test_modifica_repo_inchirieri(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"
        self.__inchiriere = InchiriereDTO(self.__id_inchiriere, self.__client.get_id_client(), self.__film.get_id_film(), self.__data_inchiriere, self.__status_inchiriere)

        self.assertTrue(self.__repo_inchirieri.adauga_inchiriere(self.__inchiriere) == None)

        self.__data_inchiriere_nou = "19/07/2021"
        self.__inchiriere_modificata = InchiriereDTO(self.__id_inchiriere,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere_nou, self.__status_inchiriere)

        self.assertTrue(self.__repo_inchirieri.modifica_inchiriere(self.__inchiriere_modificata) == None)

        inchiriere_gasita = self.__repo_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere)
        self.assertTrue(inchiriere_gasita.get_data_inchiriere() == self.__data_inchiriere_nou)

        self.__id_inchiriere_inexistenta = 101
        self.__inchiriere_inexistenta = InchiriereDTO(self.__id_inchiriere_inexistenta,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere, self.__status_inchiriere)
        with self.assertRaises(RepoError) as re:
            self.__repo_inchirieri.modifica_inchiriere(self.__inchiriere_inexistenta)
        self.assertEqual(str(re.exception), "inchiriere inexistenta!")


    def test_stergere_repo_inchirieri(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"
        self.__inchiriere = InchiriereDTO(self.__id_inchiriere, self.__client.get_id_client(), self.__film.get_id_film(), self.__data_inchiriere, self.__status_inchiriere)

        self.assertTrue(self.__repo_inchirieri.adauga_inchiriere(self.__inchiriere) == None)

        self.assertTrue(self.__repo_inchirieri.sterge_inchiriere_dupa_id(self.__id_inchiriere) == None)
        self.assertTrue(len(self.__repo_inchirieri) == 0)
        with self.assertRaises(RepoError) as re:
            self.__repo_inchirieri.sterge_inchiriere_dupa_id(self.__id_inchiriere)
        self.assertEqual(str(re.exception), "inchiriere inexistenta!")


    def test_adaugare_service_inchirieri(self):
        self.assertTrue(self.__service_inchirieri.size() == 0)
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"

        self.assertTrue(self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere, self.__status_inchiriere) == None)
        self.assertTrue(self.__service_inchirieri.size() == 1)

        with self.assertRaises(RepoError) as re:
            self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere, self.__status_inchiriere)
        self.assertEqual(str(re.exception),"inchiriere existenta!")

        self.__id_inchiriere_invalid = -11
        self.__data_inchiriere_invalida = "44/13/1800"
        with self.assertRaises(ValidationError) as ve:
            self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere_invalid,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere_invalida, self.__status_inchiriere)
        self.assertEqual(str(ve.exception),"id invalid!\ndata invalida!\n")


    def test_cautare_service_inchirieri(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"
        self.assertTrue(self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere, self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere, self.__status_inchiriere) == None)

        inchiriere_gasita = self.__service_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere)
        self.assertTrue(inchiriere_gasita.get_client_inchiriere() == self.__client)
        self.assertTrue(inchiriere_gasita.get_data_inchiriere() == self.__data_inchiriere)

        self.__id_inchiriere_inexistenta = 101
        with self.assertRaises(RepoError) as re:
            self.__service_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere_inexistenta)
        self.assertEqual(str(re.exception), "inchiriere inexistenta!")


    def test_modifica_service_inchirieri(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"

        self.assertTrue(self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere, self.__client.get_id_client(), self.__film.get_id_film(), self.__data_inchiriere,self.__status_inchiriere) == None)

        self.__data_inchiriere_noua = "19/07/2021"
        self.__id_inchiriere_inexistenta = 101
        with self.assertRaises(RepoError) as re:
            self.__service_inchirieri.modifica_inchiriere(self.__id_inchiriere_inexistenta,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere_noua)
        self.assertEqual(str(re.exception), "inchiriere inexistenta!")

        self.assertTrue(self.__service_inchirieri.modifica_inchiriere(self.__id_inchiriere,self.__client.get_id_client(),self.__film.get_id_film(),self.__data_inchiriere_noua) == None)
        inchiriere_gasita = self.__service_inchirieri.cauta_inchiriere_dupa_id(self.__id_inchiriere)
        self.assertTrue(inchiriere_gasita.get_data_inchiriere() == self.__data_inchiriere_noua)


    def test_stergere_service_inchirieri(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"

        self.assertTrue(self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere, self.__client.get_id_client(),self.__film.get_id_film(), self.__data_inchiriere, self.__status_inchiriere) == None)

        self.__id_inchiriere_inexistenta = 101
        with self.assertRaises(RepoError) as re:
            self.__service_inchirieri.sterge_inchiriere_dupa_id(self.__id_inchiriere_inexistenta)
        self.assertEqual(str(re.exception), "inchiriere inexistenta!")

        self.assertTrue(self.__service_inchirieri.sterge_inchiriere_dupa_id(self.__id_inchiriere) == None)
        self.assertTrue(self.__service_inchirieri.size() == 0)



    # -------- BLACKBOX TESTING --------

    def test_adaugare_inchiriere_blackbox(self):
        self.__id_inchiriere = 56
        self.__data_inchiriere = "12/05/2022"
        self.__status_inchiriere = "True"

        self.assertTrue(self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere, self.__client.get_id_client(),
                                                                    self.__film.get_id_film(), self.__data_inchiriere,self.__status_inchiriere) == None)

        with self.assertRaises(RepoError) as re:
            self.__service_inchirieri.adauga_inchiriere(self.__id_inchiriere,self.__client.get_id_client(),self.__film.get_id_film(),"04/06/2020",self.__status_inchiriere)
        self.assertEqual(str(re.exception), "inchiriere existenta!")

        with self.assertRaises(ValidationError) as ve:
            self.__service_inchirieri.adauga_inchiriere(-10,self.__client.get_id_client(),self.__film.get_id_film(),"34/02/2017",self.__status_inchiriere)
        self.assertEqual(str(ve.exception), "id invalid!\ndata invalida!\n")