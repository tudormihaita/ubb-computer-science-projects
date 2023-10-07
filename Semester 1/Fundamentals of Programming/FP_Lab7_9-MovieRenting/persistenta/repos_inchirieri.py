from erori.exceptii import RepoError

class RepoInchiriere(object):

    def __init__(self):
        """
        Initializez depozitul pentru entitatile de tip Inchiriere, acesta fiind initial gol
        """
        self._inchirieri = {}

    def __len__(self):
        """
        Determina lungimea inchirierilor valide aflata in baza de date si returneaza lungimea int length
        :return: rezultatul: lungimea de tip int length
        """
        length = 0
        for id_inchiriere in self._inchirieri:
            inchiriere = self._inchirieri[id_inchiriere]
            if inchiriere.get_status_inchiriere() == "True":
                length += 1
        return length
        #return len(self.__inchirieri)


    #NU MAI E NEVOIE
    def update_inchiriere(self, inchiriere):
        """
        actualizeaza atributele inchirierii specificate in urma modificarilor aduse asupra statusului inchirierii, in cazul in care
        a fost sters un client care a efectuat inchirieri sau un film care a fost inchiriat
        :param inchiriere: Inchiriere
        :return: - ( actualizeaza o inchiriere in urma modificarii statusului acesteia )
        """
        for id_inchiriere in self._inchirieri:
            if id_inchiriere == inchiriere.get_id_inchiriere():
                self._inchirieri[id_inchiriere] = inchiriere


    def adauga_inchiriere(self,inchiriere):
        """
        Creeaza o entitate de tip inchiriere cu un id, un client, un film inchiriat si o data a inchirierii, o valideaza si o adauga in baza de date
        daca datele acesteia sunt valide si daca atat clientul, cat si filmul exista in baza de date
        :param inchiriere:
        :return:
        """
        if inchiriere.get_id_inchiriere() in self._inchirieri:
            raise RepoError("inchiriere existenta!")

        for id in self._inchirieri:
            if (self._inchirieri[id].get_data_inchiriere() == inchiriere.get_data_inchiriere()
                    and self._inchirieri[id].get_id_client_inchiriere() == inchiriere.get_id_client_inchiriere()
                    and self._inchirieri[id].get_id_film_inchiriere() == inchiriere.get_id_film_inchiriere()):
                raise RepoError("inchiriere existenta!")

        self._inchirieri[inchiriere.get_id_inchiriere()] = inchiriere

    def cauta_inchiriere_dupa_id(self,id_inchiriere):
        """
        cauta in baza de date inchirierea data prin id si o va returna
        :param id_inchiriere: int
        :return: - ( va returnata inchirierea data prin id daca aceasta exista )
        """
        if id_inchiriere not in self._inchirieri:
            raise RepoError("inchiriere inexistenta!")
        if id_inchiriere in self._inchirieri:
            if self._inchirieri[id_inchiriere].get_status_inchiriere() == "False":
                raise RepoError("inchiriere inexistenta!")
        if self._inchirieri[id_inchiriere].get_status_inchiriere() == "True":
            return self._inchirieri[id_inchiriere]

    def modifica_inchiriere(self, inchiriere):
        """
        cauta in baza de date inchirierea data si ii va modifica atributele
        :param inchiriere: Inchiriere
        :return: - ( va modifica datele inchirierii date daca aceasta exista )
        """
        if inchiriere.get_id_inchiriere() not in self._inchirieri:
            raise RepoError("inchiriere inexistenta!")
        id_inchiriere = inchiriere.get_id_inchiriere()
        if id_inchiriere in self._inchirieri:
            if self._inchirieri[id_inchiriere].get_status_inchiriere() == "False":
                #raise RepoError("inchiriere inexistenta!")
                self._inchirieri[inchiriere.get_id_inchiriere()] = inchiriere
        if self._inchirieri[id_inchiriere].get_status_inchiriere() == "True":
            self._inchirieri[inchiriere.get_id_inchiriere()] = inchiriere

    def get_all_inchirieri(self):
        """
        returneaza toate inchirierile din baza de date sub forma unei liste iterabile
        :return: lista de inchirieri
        """
        lista = []
        for id_inchiriere in self._inchirieri:
            inchiriere = self._inchirieri[id_inchiriere]
            #if inchiriere.get_status_inchiriere() == "True":
            lista.append(inchiriere)
        return lista


    def sterge_inchiriere_dupa_id(self,id_inchiriere):
        """
        marcheaza drept stearsa in baza de date o inchiriere specificata prin id in cazul in care exista
        :param id_inchiriere: int
        :return: - ( marcheaza drept eliminata inchirierea data prin id daca aceasta exista )
        """
        if id_inchiriere not in self._inchirieri:
            raise RepoError("inchiriere inexistenta!")
        if self._inchirieri[id_inchiriere].get_status_inchiriere() == "False":
            raise RepoError("inchiriere inexistenta!")
        #del self.__inchirieri[id_inchiriere]
        self._inchirieri[id_inchiriere].set_status_inchiriere("False")


