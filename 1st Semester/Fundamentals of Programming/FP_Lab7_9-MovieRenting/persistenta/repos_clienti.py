from erori.exceptii import RepoError

class RepoClient(object):

    def __init__(self):
        """
        Initializez depozitul de clienti sub forma unui dictionar.
        """
        self._clienti = {}

    def __len__(self):
        """
        returneaza lungimea listei de clienti retinuti in baza de date
        :return: int-ul len, egal cu numarul de clienti din baza de date
        """
        return len(self._clienti)

    def adauga_client(self, client):
        """
        adauga un client in baza de date si verifica ca id-ul acestuia sa fie unic
        :param client: Client
        :return: - ( adauga clientul dat in lista de clienti )
        """
        if client.get_id_client() in self._clienti:
            raise RepoError("client existent!")
        for id in self._clienti:
            if client.get_cnp_client() == self._clienti[id].get_cnp_client() and client.get_id_client() != self._clienti[id].get_id_client():
                raise RepoError("cnp existent!")
        self._clienti[client.get_id_client()] = client
        #print(self.__clienti)

    def cauta_client_dupa_id(self, id_client):
        """
        cauta in baza de date clientul specificat prin id, aruncand o eroare corespunzatoare in cazul in care nu exista un client cu id-ul dat
        :param id_client: int
        :return: - ( clientul cu id-ul specificat)
        """
        if id_client not in self._clienti:
            raise RepoError("client inexistent!")
        return self._clienti[id_client]

    def modifica_client(self, client):
        """
        inlocuieste datele unui client dat din lista de clienti cu noile date introduse de utilizator, in cazul in care exista clientul pentru care
        se doreste a se realiza modificari
        :param client: Client
        :return: - ( se va modifica clientul dat si atributele sale in cazul in care acesta exista )
        """
        if client.get_id_client() not in self._clienti:
            raise RepoError("client inexistent!")

    # VERIFICA SI PT CNP MODIFICAT DEJA IN LISTA DE CLIENTI!
        #if client.get_cnp_client() in self.__clienti and client.get_id_client() != self.__clienti[client.get_id_client()]:
            #raise RepoError("modificare invalida!")

        for id in self._clienti:
            if client.get_cnp_client() == self._clienti[id].get_cnp_client() and client.get_id_client() != self._clienti[id].get_id_client():
                raise RepoError("cnp modificat existent!")
        self._clienti[client.get_id_client()] = client

    def get_all_clienti(self):
        """
        afiseaza toti clientii din baza de date sub forma unei lista iterabile
        :return: o lista in care sunt salvate toate obiectele de tip Client introduse in baza de date
        """
        lista = []
        for id_client in self._clienti:
            client = self._clienti[id_client]
            lista.append(client)
        return lista

    def sterge_client_dupa_id(self, id_client):
        """
        cauta si elimina din baza de date clientul corespunzator id-ului dat in cazul in care acesta exista, in caz contrat aruncand o eroare corespunzatoare
        :param id_client: int
        :return: - ( elimina din baza de date clientul dat prin id daca acesta exista )
        """
        if id_client not in self._clienti:
            raise RepoError("client inexistent!")
        del self._clienti[id_client]
