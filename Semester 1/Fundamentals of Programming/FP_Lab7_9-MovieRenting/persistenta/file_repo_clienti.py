from persistenta.repos_clienti import RepoClient
from domain.clienti import Client

class FileRepoClienti(RepoClient):

    def __init__(self,file_path):
        RepoClient.__init__(self)
        self.__file_path = file_path

    def __read_all_from_file(self):
        """
        Deschide fisierul corespunzator datelor pentru clienti in modul read si incarca in memorie intrarile valide.
        :return: - ( Preia din fisier intrarile pentru clienti adaugate pana la momentul actual )
        """
        with open(self.__file_path,"r") as f:
            lines = f.readlines()
            self._clienti.clear()
            for line in lines:
                line = line.strip()
                if line != "":
                    #line = line.strip("-")
                    parts = line.split(" ")
                    id_client = int(parts[0].strip("[]"))
                    nume_client = parts[1]
                    cnp = parts[2].strip("()")
                    client = Client(id_client,nume_client,cnp)
                    self._clienti[id_client] = client
        f.close()

    def __write_all_to_file(self):
        """
        Deschide fisierul corespunzator datelor pentru clienti in modul write si depune intrarile din memorie in acesta in urma operatiilor efectuate
        :return: - ( Populeaza fisierul cu intrarile pentru clienti din memorie adaugate pana la momentul actual )
        """
        with open(self.__file_path, "w") as f:
            for client in self._clienti.values():
                #f.write(str(client)+"\n")
                f.write(f"{client.get_id_client()} {client.get_nume_client()} {client.get_cnp_client()}"+"\n")
        f.close()

    def adauga_client(self, client):
        """
        adauga un client in baza de date si verifica ca id-ul acestuia sa fie unic
        :param client: Client
        :return: - ( adauga clientul dat in lista de clienti )
        """
        self.__read_all_from_file()
        RepoClient.adauga_client(self,client)
        self.__write_all_to_file()

    def modifica_client(self,client):
        """
        inlocuieste datele unui client dat din lista de clienti cu noile date introduse de utilizator, in cazul in care exista clientul pentru care
        se doreste a se realiza modificari
        :param client: Client
        :return: - ( se va modifica clientul dat si atributele sale in cazul in care acesta exista )
        """
        self.__read_all_from_file()
        RepoClient.modifica_client(self,client)
        self.__write_all_to_file()

    def sterge_client_dupa_id(self,id_client):
        """
        cauta si elimina din baza de date clientul corespunzator id-ului dat in cazul in care acesta exista, in caz contrat aruncand o eroare corespunzatoare
        :param id_client: int
        :return: - ( elimina din baza de date clientul dat prin id daca acesta exista )
        """
        self.__read_all_from_file()
        RepoClient.sterge_client_dupa_id(self,id_client)
        self.__write_all_to_file()

    def cauta_client_dupa_id(self, id_client):
        """
        cauta in baza de date clientul specificat prin id, aruncand o eroare corespunzatoare in cazul in care nu exista un client cu id-ul dat
        :param id_client: int
        :return: - ( clientul cu id-ul specificat)
        """
        self.__read_all_from_file()
        return RepoClient.cauta_client_dupa_id(self,id_client)

    def get_all_clienti(self):
        """
        afiseaza toti clientii din baza de date sub forma unei lista iterabile
        :return: o lista in care sunt salvate toate obiectele de tip Client introduse in baza de date
        """
        self.__read_all_from_file()
        return RepoClient.get_all_clienti(self)

    def size(self):
        """
        returneaza numarul de clienti din baza de date
        :return: int-ul len corespunzator numarului de clienti
        """
        self.__read_all_from_file()
        return RepoClient.__len__(self)