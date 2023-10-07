from domain.filme import Film


class ServiceFilm(object):

    def __init__(self, __repo_filme, __validator_filme, __repo_inchirieri):
        """
        initializeaza repozitoarele pentru filme si validatorul pentru film
        :param __repo_filme: RepoFilm
        :param __validator_filme: ValidatorFilm
        :param __repo_inchirieri: RepoInchiriere
        """
        self.__repo_filme = __repo_filme
        self.__validator_filme = __validator_filme
        self.__repo_inchirieri = __repo_inchirieri

    def size(self):
        """
        returneaza numar de filme din colectie
        :return: int ( numarul de filme din colectie la momentul actual )
        """
        return len(self.__repo_filme)

    def adauga_film(self, id_film, titlu, gen, descriere):
        """
        creeaza un film cu un id, titlu, descriere si gen, valideaza datele acestuia si il adauga in colectie
        :param id_film: int
        :param titlu: string
        :param gen: string
        :param descriere: string
        :return: - ( in colectie va fi adaugat filmul introdus )
        """
        film = Film(id_film,titlu,gen,descriere)

        self.__validator_filme.valideaza(film)
        self.__repo_filme.adauga_film(film)

    def cauta_film_dupa_id(self, id_film):
        """
        se cauta in colectia de filme filmul cu id-ul id_film in cazul in care exista si se returneaza acesta
        :param id_film: int
        :return: Film cu id_film cautat
        :raises: RepoError : in cazul in care nu exista niciun film cu id-ul introdus
        """
        return self.__repo_filme.cauta_film_dupa_id(id_film)

    def modifica_film(self, id_film, titlu, gen, descriere):
        """
        se cauta in colectia de filme filmul cu id-ul id_film si se modifica datele acestuia cu noile valori pentru titlu, descriere si gen.
        in cazul in care aceste valori sunt valide
        :param id_film: int
        :param titlu: string
        :param gen: string
        :param descriere : string
        :return: - ( in colectia de filme va fi modificat corespunzator filmul respectiv )
        """
        film = Film(id_film,titlu,gen,descriere)
        self.__validator_filme.valideaza(film)

        self.__repo_filme.modifica_film(film)

    def sterge_film_dupa_id(self, id_film):
        """
        se va sterge din colectie filmul cu id-ul respectiv
        :param id_film: int
        :return:
        :raises: RepoError : in cazul in care nu exista niciun film cu id-ul id_film
        """
        #self.__repo_inchirieri.__init__()
        for inchiriere in self.__repo_inchirieri.get_all_inchirieri():
            #if inchiriere.get_film_inchiriere().get_id_film() == id_film:
            if inchiriere.get_id_film_inchiriere() == id_film:
                inchiriere.set_status_inchiriere("False")
                #self.__repo_inchirieri.update_inchiriere(inchiriere)
                # statusul inchirierilor efectuate cu filmul sters vor fi rescrise in fisier prin metoda de modificare
                self.__repo_inchirieri.modifica_inchiriere(inchiriere)
        self.__repo_filme.sterge_film_dupa_id(id_film)

    def get_all_filme(self):
        """
        returneaza colectia de filme
        :return: - ( se va returna colectia de filme introduse pana la momentul actual )
        """
        return self.__repo_filme.get_all_filme()