from domain.spectacole import Spectacol
import random
import string

class ServiceSpectacole(object):

    def __init__(self, __repo_spectacole, __validator_spectacole):
        """
        injecteaza dependenta in Service de clasele Repository si Validator
        :param __repo_spectacole: RepoSpectacole
        :param __validator_spectacole: ValidatorSpectacole
        """
        self.__repo_spectacole = __repo_spectacole
        self.__validator_spectacole = __validator_spectacole

    def size(self):
        """
        returneaza numarul de spectacole introduse pana la momentul actual
        :return: numarul de spectacol(int)
        """
        return len(self.__repo_spectacole.get_all_spectacole())

    def get_all_spectacole(self):
        """
        returneaza o lista cu toate spectacolele introduse pana la momentul actual
        :return: o lista de obiecte de tip spectacol
        """
        return self.__repo_spectacole.get_all_spectacole()

    def adauga_spectacol(self, titlu, artist, gen, durata):
        """
        creeaza un obiect de tip spectacol cu atributele titlu, artist, gen si durata
        valideaza daca obiectul creat este valid
        in caz afirmativ, il adauga in baza de date
        :param titlu: string
        :param artist: string
        :param gen: string
        :param durata: int, >= 0
        :return: - (daca spectacolul este valid, se adauga la baza de date)
        :raises: ValidationError - daca atributele introduse nu sunt valide
        :raises: RepoError - daca exista deja un spectacol in baza de date cu titlul si artistul dat
        """
        spectacol = Spectacol(titlu, artist, gen, durata)
        self.__validator_spectacole.valideaza(spectacol)
        self.__repo_spectacole.adauga_spectacol(spectacol)


    def modifica_spectacol(self, titlu_cautat, artist_cautat, gen_nou, durata_noua):
        """
        se dau titlul si artistul spectacolului cautat, noile valori pentru gen si durata
        se verifica daca obiectul modificat ramane inca valid
        se modifica in memorie genul si durata obiectului spectacol dat prin titlu si artist
        :param titlu_cautat: string
        :param artist_cautat: string
        :param gen_nou: string
        :param durata_noua: int, >= 0
        :return: - ( se modifica spectacolul dat daca noile atribute sunt valide)
        :raises: ValidationError: daca noile valori specificate pentru gen si durata sunt invalide
        :raises: RepoError: daca spectacolul dat prin titlu si artist nu exista
        """
        spectacol_modificat = Spectacol(titlu_cautat, artist_cautat, gen_nou, durata_noua)
        self.__validator_spectacole.valideaza(spectacol_modificat)
        self.__repo_spectacole.modifica_spectacol(spectacol_modificat)

    def cauta_spectacol(self, titlu_cautat, artist_cautat):
        """
        cauta un spectacol in baza de date identificat prin titlu si artist
        :param titlu_cautat: string
        :param artist_cautat: string
        :return: spectacolul cautat, daca acesta exista
        :raises: RepoError - daca spectacolul cautat nu exista
        """
        return self.__repo_spectacole.cauta_spectacol(titlu_cautat, artist_cautat)

    def genereaza_spectacole(self, nr_spectacole):
        """
        genereaza numarul dat de spectacole, care respecta urmatoarele reguli:
        titlul si numele artistului sunt string-uri de dimensiune [8,12], in care se alterneaza vocalele cu consoanele si contin un spatiu in interior
        genul este unul din cele date: Comedie, Concert, Balet, Altele
        durata este un numar intreg pozitiv [1000,9999]
        adauga spectacolele generate in baza de date
        :param nr_spectacole: int
        :return: o lista care contine spectacolele
        """
        nr_generari = nr_spectacole
        lista_generari = []
        genuri = ["Comedie", "Concert", "Balet", "Altele"]
        vocale = ["a", "e", "i", "o", "u", "A", "E", "I", "O", "U"]
        consoane = list(string.ascii_letters)
        for c in consoane:
            if c in vocale:
                consoane.remove(c)

        while nr_generari != 0:
            len_max_titlu = random.randint(9, 12)
            len1_titlu = random.randint(1, len_max_titlu-1) # un caracter rezervat pentru spatiu
            cuv1_titlu = ""
            for i in range(0, len1_titlu):
                if i % 2 != 0:
                    c = random.choice(vocale)
                else:
                    c = random.choice(consoane)
                cuv1_titlu += c

            len2_titlu = len_max_titlu - len1_titlu
            cuv2_titlu = ""
            for i in range(0, len2_titlu):
                if i % 2 != 0:
                    c = random.choice(vocale)
                else:
                    c = random.choice(consoane)
                cuv2_titlu += c

            titlu_general = cuv1_titlu + " " + cuv2_titlu

            len_max_artist = random.randint(9, 12)
            len1_artist = random.randint(1, len_max_artist - 1)
            cuv1_artist = ""
            for i in range(0, len1_artist):
                if i % 2 != 0:
                    c = random.choice(vocale)
                else:
                    c = random.choice(consoane)
                cuv1_artist += c

            len2_artist = len_max_artist - len1_artist
            cuv2_artist = ""
            for i in range(0, len2_artist):
                if i % 2 != 0:
                    c = random.choice(vocale)
                else:
                    c = random.choice(consoane)
                cuv2_artist += c

            artist_generat = cuv1_artist + " " + cuv2_artist

            gen_generat = random.choice(genuri)
            durata_generata = random.randint(1000, 9999)

            spectacol_generat = Spectacol(titlu_general, artist_generat, gen_generat, durata_generata)
            self.__validator_spectacole.valideaza(spectacol_generat)
            self.__repo_spectacole.adauga_spectacol(spectacol_generat)
            lista_generari.append(spectacol_generat)
            nr_generari -= 1

        return lista_generari

    def exporta_spectacole_sortate(self, file_path):
        """
        exporta in fisierul specificat prin file path toate spectacolele din baza de date, sortate dupa numele artistului si dupa titlul spectacolului
        sorteaza spectacolele din baza de date dupa numele artistului si titlul spectacolului
        afisea in fisierul dat spectacolele sortate, linie cu linie
        :param file_path: string
        :return: - (afiseaza in fisierul dat spectacolele sortate)
        """
        lista_spectacole = self.__repo_spectacole.get_all_spectacole()
        lista_spectacole.sort(key=lambda x: (x.get_artist_spectacol(), x.get_titlu_spectacol()), reverse=False)
        with open(file_path, "w") as f:
            for spectacol in lista_spectacole:
                f.write(f"{spectacol.get_artist_spectacol()}"+ ", " + f"{spectacol.get_titlu_spectacol()}" + ", "
                        + f"{spectacol.get_durata_spectacol()}" + ", " + f"{spectacol.get_gen_spectacol()}" + "\n")

        f.close()
        return lista_spectacole

