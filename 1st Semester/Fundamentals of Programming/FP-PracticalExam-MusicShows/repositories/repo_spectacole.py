from domain.spectacole import Spectacol
from erori.exceptii import RepoError

class RepoSpectacole(object):

    def __init__(self, file_path):
        """
        initializeaza calea(numele fisierului) pus in legatura cu baza de date
        initializeaza depozitul de spectacole
        :param file_path: string
        """
        self.__file_path = file_path
        self.__spectacole = {}


    def _read_all_from_file(self):
        """
        citeste toate spectacolele din fisierul de intrare specificat in file_path si le incarca in memoria aplicatiei
        :return: - (spectacolele vor fi citite linie cu linie din fisier si adaugate in memorie)
        """
        with open(self.__file_path, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(", ")
                    titlu = parts[0].strip()
                    artist = parts[1].strip()
                    gen = parts[2].strip()
                    durata = int(parts[3].strip())
                    spectacol = Spectacol(titlu,artist,gen,durata)
                    self.__spectacole[(titlu,artist)] = spectacol
        f.close()


    def _write_all_to_file(self):
        """
        exporta spectacolele din memorie in fisierul de intrare, in urma eventualelor modificari aduse bazei de date
        :return: - (exporta spectacolele in fisier, afisate linie cu linie)
        """
        with open(self.__file_path, "w") as f:
            for spectacol in self.__spectacole.values():
                f.write(f"{spectacol.get_titlu_spectacol()}" + ", " + f"{spectacol.get_artist_spectacol()}" + ", " + f"{spectacol.get_gen_spectacol()}"
                        + ", " + f"{spectacol.get_durata_spectacol()}" + "\n")

            f.close()

    def clear_file(self):
        """
        sterge continutul fisierului de intrare specificat prin file_path
        :return: - (sterge continutul anterior din fisierul dat)
        """
        with open(self.__file_path, "w") as f:
            pass

        f.close()


    def adauga_spectacol(self, spectacol):
        """
        adauga obiectul de tip spectacol in baza de date
        verifica daca deja exista un spectacol cu acelasi titlu si artist
        :param spectacol: spectacol
        :return: - (adauga spectacolul in memorie si in fisierul de intrare daca acesta este unic identificat prin titlu si artist)
        :raises: RepoError - in cazul in care deja exista un spectacol cu titlul si artistul specificat
        """
        self._read_all_from_file()
        if (spectacol.get_titlu_spectacol(), spectacol.get_artist_spectacol()) in self.__spectacole:
            raise RepoError("Spectacol deja existent!\n")

        self.__spectacole[(spectacol.get_titlu_spectacol(),spectacol.get_artist_spectacol())] = spectacol
        self._write_all_to_file()

    def modifica_spectacol(self, spectacol):
        """
        modifica in baza de date genul si durata unui spectacol dat
        :param spectacol: spectacol
        :return: - (modifica atat in memorie cat si in fisierul de intrare atributele obiectului spectacol dat)
        :raises: RepoError: in cazul in care spectacolul dat, identificat prin titlu si artist, nu exista
        """
        if (spectacol.get_titlu_spectacol(), spectacol.get_artist_spectacol()) not in self.__spectacole:
            raise RepoError("Spectacol inexistent!\n")
        self.__spectacole[(spectacol.get_titlu_spectacol(), spectacol.get_artist_spectacol())] = spectacol
        self._write_all_to_file()

    def get_all_spectacole(self):
        """
        returneaza o lista cu toate spectacolele introduse in baza de date pana la momentul actual
        :return: lista_spectacole, o lista de obiecte de tip spectacol
        """
        self._read_all_from_file()
        lista_spectacole = []
        for (titlu,artist) in self.__spectacole:
            lista_spectacole.append(self.__spectacole[(titlu, artist)])

        return lista_spectacole

    def cauta_spectacol(self, titlu, artist):
        """
        cauta un spectacol in baza de date identificat prin titlul si artistul dat
        :param titlu: string
        :param artist: string
        :return: spectacolul identificat unic prin titlul si artistul dat
        :raises: RepoError: in cazul in care spectacolul specificat prin titlu si artist nu exista
        """
        if (titlu, artist) not in self.__spectacole:
            raise RepoError("Spectacol inexistent!\n")
        return self.__spectacole[(titlu, artist)]
