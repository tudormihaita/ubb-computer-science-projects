from erori.exceptii import RepoError

class RepoFilm(object):

    def __init__(self):
        """
        Initializez depozitul de filme din baza de date sub forma unui dictionar.
        """
        self._filme = {}

    def __len__(self):
        """
        returneaza lungimea listei de filme din baza de date, corespunzatoare numarului de filme din depozit.
        :return: int-ul len egal cu numarul de filme din baza de date
        """
        return len(self._filme)

    def adauga_film(self, film):
        """
        adauga un obiect film in baza de date si verifica daca id-ul sau este unic in momentul adaugarii, aruncand o eroare corespunzatoare
        in caz contrar
        :param film: Film
        :return: - ( va adauga in baza de date filmul dat, pastrand unicitatea prin id )
        """
        if film.get_id_film() in self._filme:
            raise RepoError("film existent!")
        self._filme[film.get_id_film()] = film

    def cauta_film_dupa_id(self, id_film):
        """
        cauta in baza de date filmul specificat prin id, returnandu-l in cazul in care exista
        :param id_film: int
        :return: filmul specificat prin id daca acesta exista
        """
        if id_film not in self._filme:
            raise RepoError("film inexistent!")
        return self._filme[id_film]

    def modifica_film(self, film):
        """
        modifica in baza de datele atributele unui film dat prin inlocuirea acestora cu noi date, in cazul in care filmul care se doreste a fi
        modificat exista
        :param film: Film
        :return: - ( se vor modifica datele filmului daca acesta exista )
        """
        if film.get_id_film() not in self._filme:
            raise RepoError("film inexistent!")
        self._filme[film.get_id_film()] = film

    def get_all_filme(self):
        """
        returneaza toate filmele din baza de date sub forma unei lista iterabile
        :return: lista de filme din baza de date
        """
        lista = []
        for id_film in self._filme:
            film = self._filme[id_film]
            lista.append(film)
        return lista

    def sterge_film_dupa_id(self, id_film):
        """
        cauta si elimina filmul din baza de date specificat prin id, in cazul in care acesta exista, iar in caz contrar va arunca o eroare corespunzatoare
        :param id_film: int
        :return: - ( va sterge din baza de date filmul dat prin id )
        """
        if id_film not in self._filme:
            raise RepoError("film inexistent!")
        del self._filme[id_film]