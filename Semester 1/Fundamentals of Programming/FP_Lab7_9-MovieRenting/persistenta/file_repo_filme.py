from persistenta.repos_filme import RepoFilm
from domain.filme import Film

class FileRepoFilme(RepoFilm):

    def __init__(self, file_path):
        RepoFilm.__init__(self)
        self.__file_path = file_path

    def __read_all_from_file(self):
        """
        Deschide fisierul corespunzator datelor pentru filme in modul read si incarca in memorie intrarile valide.
        :return: - ( Preia din fisier intrarile pentru filme adaugate pana la momentul actual )
        """
        with open(self.__file_path,"r") as f:
            lines = f.readlines()
            self._filme.clear()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(" ")
                    id_film = int(parts[0].strip("[]"))
                    titlu_film = parts[1]
                    gen_film = parts[2]
                    descriere_film = parts[3:]
                    string_descriere = ' '.join(str(x) for x in descriere_film)
                    string_descriere.strip()

                    film = Film(id_film,titlu_film,gen_film,string_descriere)
                    self._filme[id_film] = film
        f.close()


    def __write_all_to_file(self):
        """
        Deschide fisierul corespunzator datelor pentru filme in modul write si depune intrarile din memorie in acesta in urma operatiilor efectuate
        :return: - ( Populeaza fisierul cu intrarile pentru filme din memorie adaugate pana la momentul actual )
        """
        with open(self.__file_path, "w") as f:
            for film in self._filme.values():
                f.write(f"{film.get_id_film()} {film.get_titlu_film()} {film.get_gen_film()} {film.get_descriere_film()}"+"\n")

        f.close()


    def adauga_film(self, film):
        """
        adauga un obiect film in baza de date si verifica daca id-ul sau este unic in momentul adaugarii, aruncand o eroare corespunzatoare
        in caz contrar
        :param film: Film
        :return: - ( va adauga in baza de date filmul dat, pastrand unicitatea prin id )
        """
        self.__read_all_from_file()
        RepoFilm.adauga_film(self, film)
        self.__write_all_to_file()

    def modifica_film(self, film):
        """
        modifica in baza de datele atributele unui film dat prin inlocuirea acestora cu noi date, in cazul in care filmul care se doreste a fi
        modificat exista
        :param film: Film
        :return: - ( se vor modifica datele filmului daca acesta exista )
        """
        self.__read_all_from_file()
        RepoFilm.modifica_film(self, film)
        self.__write_all_to_file()

    def sterge_film_dupa_id(self, id_film):
        """
        cauta si elimina filmul din baza de date specificat prin id, in cazul in care acesta exista, iar in caz contrar va arunca o eroare corespunzatoare
        :param id_film: int
        :return: - ( va sterge din baza de date filmul dat prin id )
        """
        self.__read_all_from_file()
        RepoFilm.sterge_film_dupa_id(self, id_film)
        self.__write_all_to_file()

    def cauta_film_dupa_id(self, id_film):
        """
        cauta in baza de date filmul specificat prin id, returnandu-l in cazul in care exista
        :param id_film: int
        :return: filmul specificat prin id daca acesta exista
        """
        self.__read_all_from_file()
        return RepoFilm.cauta_film_dupa_id(self, id_film)

    def get_all_filme(self):
        """
        returneaza toate filmele din baza de date sub forma unei lista iterabile
        :return: lista de filme din baza de date
        """
        self.__read_all_from_file()
        return RepoFilm.get_all_filme(self)

    def size(self):
        """
        returneaza lungimea listei de filme din baza de date, corespunzatoare numarului de filme din depozit.
        :return: int-ul len egal cu numarul de filme din baza de date
        """
        self.__read_all_from_file()
        return RepoFilm.__len__(self)