from domain.clienti import Client


class ServiceClient(object):
    def __init__(self, __repo_clienti, __validator_clienti, __repo_inchirieri):
        """
        initializez metodele din repozitorii si validatorul de client pentru a putea efectua functionalitatile asupra bazei de date
        :param __repo_clienti: RepoClient
        :param __validator_clienti: ValidatorClient
        :param __repo_inchirieri: RepoInchiriere
        """
        self.__repo_clienti = __repo_clienti
        self.__validator_clienti = __validator_clienti
        self.__repo_inchirieri = __repo_inchirieri

    def size(self):
        """
        returneaza numarul de clienti din baza de date
        :return: int - numarul de clienti introdusi pana la momentul respectiv
        """
        return len(self.__repo_clienti)

    def adauga_client(self, id_client, nume_client, cnp_client):
        """
        creeaza un client cu un id, nume si cnp, il valideaza si adauga in baza de date
        :param id_client: int
        :param nume_client: string
        :param cnp_client: string
        :return:
        """
        client = Client(id_client, nume_client, cnp_client)
        self.__validator_clienti.valideaza(client)
        self.__repo_clienti.adauga_client(client)

    def cauta_client_dupa_id(self, id_client):
        """
        cauta in baza de date clientul cu id-ul id_client
        :param id_client: int
        :return: Client cu id-ul id_client
        """
        return self.__repo_clienti.cauta_client_dupa_id(id_client)

    def modifica_client(self, id_client, nume_client, cnp_client):
        """
        modifica in baza de date clientul cu id-ul id_client, cu noi valori pentru nume si cnp, validandu-le ulterior
        :param id_client: int
        :param nume_client: string
        :param cnp_client: string
        :return:
        """
        client = Client(id_client, nume_client, cnp_client)
        self.__validator_clienti.valideaza(client)
        self.__repo_clienti.modifica_client(client)

    def sterge_client_dupa_id(self, id_client):
        """
        sterge din baza de date clientul cu id-ul id_client in cazul in care acesta exista
        :param id_client: int
        :return: - ( este eliminat din baza de date clientul cu id-ul id_client)
        :raises: RepoError: in cazul in care nu exista un client cu id-ul introdus
        """
        # self.__repo_inchirieri.__init__()
        for inchiriere in self.__repo_inchirieri.get_all_inchirieri():
            # if inchiriere.get_client_inchiriere().get_id_client() == id_client:
            if inchiriere.get_id_client_inchiriere() == id_client:
                inchiriere.set_status_inchiriere("False")
                # self.__repo_inchirieri.update_inchiriere(inchiriere)
                # statusul inchirierilor indisponibile in urma stergerii clientului vor fi rescrise in fisier prin modificare
                self.__repo_inchirieri.modifica_inchiriere(inchiriere)
        # self.__repo_inchirieri.write_all_to_file()
        self.__repo_clienti.sterge_client_dupa_id(id_client)

    def get_all_clienti(self):
        """
        returneaza toti clientii din baza de date introdusi pana la momentul actual
        :return: - ( lista de clienti )
        """
        return self.__repo_clienti.get_all_clienti()
