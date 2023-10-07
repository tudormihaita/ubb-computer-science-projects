from persistenta.repos_inchirieri import RepoInchiriere
from utils.algoritmi import recursivitate


class FileRepoInchirieri(RepoInchiriere):

    def __init__(self, file_path):
        RepoInchiriere.__init__(self)
        self.__file_path = file_path
        #self.__repo_clienti = repo_clienti
        #self.__repo_filme = repo_filme


    def __read_all_from_file(self):
        """
        Deschide fisierul corespunzator datelor pentru inchirieri in modul read si incarca in memorie intrarile valide.
        :return: - ( Preia din fisier intrarile pentru inchirieri adaugate pana la momentul actual )
        """
        with open(self.__file_path,"r") as f:
            lines = f.readlines()
            self._inchirieri.clear()
            """
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(" ")
                    id_inchiriere = int(parts[0].strip())
                    id_client_inchiriere = int(parts[1].strip())
                    id_film_inchiriere = int(parts[2].strip())
                    data_inchiriere = parts[3]
                    #status_inchiriere = bool(strtobool(parts[4].strip()))
                    status_inchiriere = parts[4].strip()
                    #status_inchiriere = ast.literal_eval(parts[4].strip())
                    #print(status_inchiriere)
                    #client = self.__repo_clienti.cauta_client_dupa_id(id_client_inchiriere)
                    #film = self.__repo_filme.cauta_film_dupa_id(id_film_inchiriere)
                    inchiriere_dto = InchiriereDTO(id_inchiriere, id_client_inchiriere, id_film_inchiriere, data_inchiriere, status_inchiriere)
                    #if inchiriere_dto.get_status_inchiriere() is True:
                    self._inchirieri[id_inchiriere] = inchiriere_dto
            """
            recursivitate.read_all_from_file_inchirieri_recursiv(lines, self._inchirieri)

        f.close()


    def write_all_to_file(self):
        """
        Deschide fisierul corespunzator datelor pentru inchirieri in modul write si depune intrarile din memorie in acesta in urma operatiilor efectuate
        :return: - ( Populeaza fisierul cu intrarile pentru inchirieri din memorie adaugate pana la momentul actual )
        """
        with open(self.__file_path,"w") as f:
            for inchiriere_dto in self._inchirieri.values():
                    #print(inchiriere_dto.get_status_inchiriere())
                    f.write(f"{inchiriere_dto.get_id_inchiriere()} {inchiriere_dto.get_id_client_inchiriere()} "
                            f"{inchiriere_dto.get_id_film_inchiriere()} {inchiriere_dto.get_data_inchiriere()} {inchiriere_dto.get_status_inchiriere()}"+"\n")

        f.close()

    def adauga_inchiriere(self, inchiriere):
        """
        Creeaza o entitate de tip inchiriere cu un id, un client, un film inchiriat si o data a inchirierii, o valideaza si o adauga in baza de date
        daca datele acesteia sunt valide si daca atat clientul, cat si filmul exista in baza de date
        :param inchiriere:
        :return:
        """
        self.__read_all_from_file()
        RepoInchiriere.adauga_inchiriere(self, inchiriere)
        self.write_all_to_file()

    def modifica_inchiriere(self, inchiriere):
        """
        cauta in baza de date inchirierea data si ii va modifica atributele
        :param inchiriere: Inchiriere
        :return: - ( va modifica datele inchirierii date daca aceasta exista )
        """
        #STERGE READ FROM FILE DIN MODIFICARE SI UTILIZEAZA IN LOC DE UPDATE
        #self.__read_all_from_file()
        RepoInchiriere.modifica_inchiriere(self, inchiriere)
        self.write_all_to_file()

    # NU MAI E NEVOIE
    def update_inchiriere(self, inchiriere):
        """
        actualizeaza atributele inchirierii specificate in urma modificarilor aduse asupra statusului inchirierii, in cazul in care
        a fost sters un client care a efectuat inchirieri sau un film care a fost inchiriat
        :param inchiriere: Inchiriere
        :return: - ( actualizeaza o inchiriere in urma modificarii statusului acesteia )
        """
        with open(self.__file_path,"r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(" ")
                    id_inchiriere = int(parts[0].strip())
                    id_client_inchiriere = int(parts[1].strip())
                    id_film_inchiriere = int(parts[2].strip())
                    data_inchiriere = parts[3]
                    status_inchiriere = parts[4].strip()
                    if id_inchiriere == inchiriere.get_id_inchiriere():
                        #status_inchiriere = inchiriere.get_status_inchiriere()
                        self._inchirieri[id_inchiriere] = inchiriere
        f.close()
        self.write_all_to_file()



    def sterge_inchiriere_dupa_id(self, id_inchiriere):
        """
        marcheaza drept stearsa in baza de date o inchiriere specificata prin id in cazul in care exista
        :param id_inchiriere: int
        :return: - ( marcheaza drept eliminata inchirierea data prin id daca aceasta exista )
        """
        self.__read_all_from_file()
        RepoInchiriere.sterge_inchiriere_dupa_id(self, id_inchiriere)
        self.write_all_to_file()


    #def sterge_inchiriere_dupa_id(self, id_inchiriere):
    #    """
    #    marcheaza drept stearsa in baza de date o inchiriere specificata prin id in cazul in care exista
    #    :param id_inchiriere: int
    #    :return: - ( marcheaza drept eliminata inchirierea data prin id daca aceasta exista )
    #    """
    #    self.__read_all_from_file()
    #    if id_inchiriere not in self._inchirieri:
    #        raise RepoError("inchiriere inexistenta!")
    #    del self._inchirieri[id_inchiriere]
    #    self.__write_all_to_file()


    def cauta_inchiriere_dupa_id(self,id_inchiriere):
        """
        cauta in baza de date inchirierea data prin id si o va returna
        :param id_inchiriere: int
        :return: - ( va returnata inchirierea data prin id daca aceasta exista )
        """
        self.__read_all_from_file()
        return RepoInchiriere.cauta_inchiriere_dupa_id(self, id_inchiriere)

    def get_all_inchirieri(self):
        """
        returneaza toate inchirierile din baza de date sub forma unei liste iterabile
        :return: lista de inchirieri
        """
        self.__read_all_from_file()
        return RepoInchiriere.get_all_inchirieri(self)
        #self.__write_all_to_file()
        #return lista

    def size(self):
        """
        Determina lungimea inchirierilor valide afla in baza de date si returneaza lungimea int length
        :return: rezultatul: lungimea de tip int length
        """
        self.__read_all_from_file()
        return RepoInchiriere.__len__(self)