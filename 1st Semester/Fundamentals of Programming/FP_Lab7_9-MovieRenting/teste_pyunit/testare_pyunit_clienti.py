import unittest
from erori.exceptii import ValidationError,RepoError
from domain.clienti import Client
from persistenta.repos_inchirieri import RepoInchiriere
from persistenta.repos_clienti import RepoClient
from persistenta.file_repo_clienti import FileRepoClienti
from validare.validator_clienti import ValidatorClient
from business.servicii_clienti import ServiceClient


class TesteClienti(unittest.TestCase):

    def setUp(self):
        self.__repo_clienti = FileRepoClienti("teste_pyunit_clienti.txt")
        self.__validator_client = ValidatorClient()
        self.__repo_inchirieri = RepoInchiriere()
        self.__service_clienti = ServiceClient(self.__repo_clienti,self.__validator_client,self.__repo_inchirieri)

    def tearDown(self):
        #pass
        with open("teste_pyunit_clienti.txt", "w") as f:
            pass
        f.close()

    # ----------  WHITEBOX TESTING -----------
    def test_domeniu_clienti(self):
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.__client = Client(self.__id_client,self.__nume_client,self.__cnp_client)

        self.assertTrue(self.__client.get_id_client() == self.__id_client)
        self.assertTrue(self.__client.get_nume_client() == self.__nume_client)
        self.assertTrue(self.__client.get_cnp_client() == self.__cnp_client)

        self.assertFalse(self.__client.get_id_client() == 22)
        self.assertFalse(self.__client.get_nume_client() == "Vlad")

        self.__clona_client = Client(self.__id_client,self.__nume_client,self.__cnp_client)
        self.assertTrue(self.__client == self.__clona_client)
        self.assertTrue(self.__client.__str__() == "[27] Andrei - (1030802118932)")

    def test_validare_clienti(self):
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.__client = Client(self.__id_client, self.__nume_client, self.__cnp_client)

        self.assertTrue(self.__validator_client.valideaza(self.__client) == None)
        self.__id_client_invalid = -78
        self.__nume_client_invalid = ""
        self.__cnp_client_invalid = "123"

        self.__client_invalid = Client(self.__id_client_invalid,self.__nume_client_invalid,self.__cnp_client_invalid)
        with self.assertRaises(ValidationError) as ve:
            self.__validator_client.valideaza(self.__client_invalid)
        self.assertEqual(str(ve.exception),"id invalid!\nnume invalid!\ncnp invalid!\n")

    def test_repo_clienti(self):
        self.assertTrue(len(self.__repo_clienti) == 0)

        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.__client = Client(self.__id_client, self.__nume_client, self.__cnp_client)

        self.assertTrue(self.__repo_clienti.adauga_client(self.__client) == None)
        self.assertTrue(len(self.__repo_clienti) == 1)

        client_gasit = self.__repo_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__client.get_nume_client())

        with self.assertRaises(RepoError) as re:
            self.__repo_clienti.adauga_client(self.__client)
        self.assertEqual(str(re.exception), "client existent!")

        self.__id_client_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__repo_clienti.cauta_client_dupa_id(self.__id_client_inexistent)
        self.assertEqual(str(re.exception),"client inexistent!")

        self.__nume_client_nou = "George"
        self.__cnp_client_nou = "3071104356403"
        self.__client_modificat = Client(self.__id_client, self.__nume_client_nou, self.__cnp_client_nou)
        self.assertTrue(self.__repo_clienti.modifica_client(self.__client_modificat) == None)

        client_gasit = self.__repo_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__nume_client_nou)
        self.assertTrue(client_gasit.get_cnp_client() == self.__cnp_client_nou)

        self.__client_inexistent = Client(self.__id_client_inexistent,"Vlad","1020406211234")
        with self.assertRaises(RepoError) as re:
            self.__repo_clienti.modifica_client(self.__client_inexistent)
        self.assertEqual(str(re.exception),"client inexistent!")

        self.__cnp = "2040506226784"
        self.__alt_client = Client(self.__id_client_inexistent, self.__nume_client_nou, self.__cnp)
        self.assertTrue(self.__repo_clienti.adauga_client(self.__alt_client) == None)
        self.assertTrue(len(self.__repo_clienti) == 2)
        clienti = self.__repo_clienti.get_all_clienti()
        self.assertTrue( len(clienti) == 2)
        self.assertTrue(self.__repo_clienti.sterge_client_dupa_id(self.__id_client) == None )
        self.assertTrue(len(self.__repo_clienti) == 1)
        with self.assertRaises(RepoError) as re:
            self.__repo_clienti.sterge_client_dupa_id(self.__id_client)
        self.assertEqual(str(re.exception),"client inexistent!")

    def test_adaugare_repo_clienti(self):
        self.assertTrue(len(self.__repo_clienti) == 0)

        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.__client = Client(self.__id_client, self.__nume_client, self.__cnp_client)

        self.assertTrue(self.__repo_clienti.adauga_client(self.__client) == None)
        self.assertTrue(len(self.__repo_clienti) == 1)

        self.__id_client_nou = 101
        self.__nume_client_nou = "George"
        self.__cnp_client_nou = "3071104356403"
        self.__alt_client = Client(self.__id_client_nou, self.__nume_client_nou, self.__cnp_client_nou)
        self.assertTrue(self.__repo_clienti.adauga_client(self.__alt_client) == None)
        self.assertTrue(len(self.__repo_clienti) == 2)

        with self.assertRaises(RepoError) as re:
            self.__repo_clienti.adauga_client(self.__alt_client)
        self.assertEqual(str(re.exception),"client existent!")


    def test_cautare_repo_clienti(self):
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.__client = Client(self.__id_client, self.__nume_client, self.__cnp_client)

        self.assertTrue(self.__repo_clienti.adauga_client(self.__client) == None)

        client_gasit = self.__repo_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__client.get_nume_client())

        self.__id_client_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__repo_clienti.cauta_client_dupa_id(self.__id_client_inexistent)
        self.assertEqual(str(re.exception), "client inexistent!")

        client_gasit = self.__repo_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__nume_client)
        self.assertTrue(client_gasit.get_cnp_client() == self.__cnp_client)


    def test_modifica_repo_clienti(self):
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.__client = Client(self.__id_client, self.__nume_client, self.__cnp_client)

        self.assertTrue(self.__repo_clienti.adauga_client(self.__client) == None)

        self.__nume_client_nou = "George"
        self.__cnp_client_nou = "3071104356403"
        self.__client_modificat = Client(self.__id_client, self.__nume_client_nou, self.__cnp_client_nou)
        self.assertTrue(self.__repo_clienti.modifica_client(self.__client_modificat) == None)

        client_gasit = self.__repo_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__nume_client_nou)
        self.assertTrue(client_gasit.get_cnp_client() == self.__cnp_client_nou)

        self.__id_client_inexistent = 101
        self.__client_inexistent = Client(self.__id_client_inexistent, "Vlad", "1020406211234")
        with self.assertRaises(RepoError) as re:
            self.__repo_clienti.modifica_client(self.__client_inexistent)
        self.assertEqual(str(re.exception), "client inexistent!")


    def test_stergere_repo_clienti(self):
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.__client = Client(self.__id_client, self.__nume_client, self.__cnp_client)

        self.assertTrue(self.__repo_clienti.adauga_client(self.__client) == None)

        self.assertTrue(self.__repo_clienti.sterge_client_dupa_id(self.__id_client) == None)
        self.assertTrue(len(self.__repo_clienti) == 0)
        with self.assertRaises(RepoError) as re:
            self.__repo_clienti.sterge_client_dupa_id(self.__id_client)
        self.assertEqual(str(re.exception), "client inexistent!")


    def test_service_clienti(self):
        self.assertTrue(self.__service_clienti.size() == 0)
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.assertTrue( self.__service_clienti.adauga_client(self.__id_client,self.__nume_client,self.__cnp_client) == None)
        self.assertTrue(self.__service_clienti.size() == 1)
        client_gasit = self.__service_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__nume_client)

        with self.assertRaises(RepoError) as re:
            self.__service_clienti.adauga_client(self.__id_client,self.__nume_client,self.__cnp_client)
        self.assertEqual(str(re.exception),"client existent!")

        self.__id_client_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__service_clienti.cauta_client_dupa_id(self.__id_client_inexistent)
        self.assertEqual(str(re.exception),"client inexistent!")

        self.__id_client_invalid = -78
        self.__nume_client_invalid = "a"
        self.__cnp_client_invalid = "1234"
        with self.assertRaises(ValidationError) as ve:
            self.__service_clienti.adauga_client(self.__id_client_invalid,self.__nume_client_invalid,self.__cnp_client_invalid)
        self.assertEqual(str(ve.exception), "id invalid!\nnume invalid!\ncnp invalid!\n")

        with self.assertRaises(RepoError) as re:
            self.__service_clienti.modifica_client(self.__id_client_inexistent,"Mircea","1060712456703")
        self.assertEqual(str(re.exception),"client inexistent!")

        self.__nume_client_nou = "George"
        self.__cnp_client_nou = "3071104356403"
        self.assertTrue(self.__service_clienti.modifica_client(self.__id_client, self.__nume_client_nou,self.__cnp_client_nou) == None)
        client_gasit = self.__service_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__nume_client_nou)

        with self.assertRaises(RepoError) as re:
            self.__service_clienti.sterge_client_dupa_id(self.__id_client_inexistent)
        self.assertEqual(str(re.exception), "client inexistent!")

        self.assertTrue(self.__service_clienti.sterge_client_dupa_id(self.__id_client) == None)
        self.assertTrue( self.__service_clienti.size() == 0)


    def test_adaugare_service_clienti(self):
        self.assertTrue(self.__service_clienti.size() == 0)
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.assertTrue(self.__service_clienti.adauga_client(self.__id_client, self.__nume_client, self.__cnp_client) == None)
        self.assertTrue(self.__service_clienti.size() == 1)

        with self.assertRaises(RepoError) as re:
            self.__service_clienti.adauga_client(self.__id_client,self.__nume_client,self.__cnp_client)
        self.assertEqual(str(re.exception),"client existent!")

        self.__id_client_invalid = -78
        self.__nume_client_invalid = "a"
        self.__cnp_client_invalid = "1234"
        with self.assertRaises(ValidationError) as ve:
            self.__service_clienti.adauga_client(self.__id_client_invalid, self.__nume_client_invalid, self.__cnp_client_invalid)
        self.assertEqual(str(ve.exception), "id invalid!\nnume invalid!\ncnp invalid!\n")


    def test_cautare_service_clienti(self):
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.assertTrue(self.__service_clienti.adauga_client(self.__id_client, self.__nume_client, self.__cnp_client) == None)

        client_gasit = self.__service_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__nume_client)

        self.__id_client_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__service_clienti.cauta_client_dupa_id(self.__id_client_inexistent)
        self.assertEqual(str(re.exception), "client inexistent!")

    def test_modifica_service_clienti(self):
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.assertTrue(self.__service_clienti.adauga_client(self.__id_client, self.__nume_client, self.__cnp_client) == None)

        self.__id_client_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__service_clienti.modifica_client(self.__id_client_inexistent, "Mircea", "1060712456703")
        self.assertEqual(str(re.exception), "client inexistent!")

        self.__nume_client_nou = "George"
        self.__cnp_client_nou = "3071104356403"
        self.assertTrue(self.__service_clienti.modifica_client(self.__id_client, self.__nume_client_nou, self.__cnp_client_nou) == None)
        client_gasit = self.__service_clienti.cauta_client_dupa_id(self.__id_client)
        self.assertTrue(client_gasit.get_nume_client() == self.__nume_client_nou)


    def test_stergere_service_clienti(self):
        self.__id_client = 27
        self.__nume_client = "Andrei"
        self.__cnp_client = "1030802118932"
        self.assertTrue(self.__service_clienti.adauga_client(self.__id_client, self.__nume_client, self.__cnp_client) == None)

        self.__id_client_inexistent = 101
        with self.assertRaises(RepoError) as re:
            self.__service_clienti.sterge_client_dupa_id(self.__id_client_inexistent)
        self.assertEqual(str(re.exception), "client inexistent!")

        self.assertTrue(self.__service_clienti.sterge_client_dupa_id(self.__id_client) == None)
        self.assertTrue(self.__service_clienti.size() == 0)



    # -------- BLACKBOX TESTING --------

    def test_adaugare_client_blackbox(self):
        self.__id_client = 23
        self.__nume_client = "George"
        self.__cnp_client = "1030407128932"

        self.assertTrue(self.__service_clienti.adauga_client(self.__id_client,self.__nume_client,self.__cnp_client) == None)

        with self.assertRaises(RepoError) as re:
            self.__service_clienti.adauga_client(self.__id_client,self.__nume_client,self.__cnp_client)
        self.assertEqual(str(re.exception), "client existent!")

        with self.assertRaises(ValidationError) as ve:
            self.__service_clienti.adauga_client(23,"a","12")
        self.assertEqual(str(ve.exception), "nume invalid!\ncnp invalid!\n")