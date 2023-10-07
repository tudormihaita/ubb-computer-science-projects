import random
import string

class GeneratorFilm(object):

    def __init__(self, service_filme):
        """
        initializeaza ServiceFilme necesar generarii random de filme
        :param service_filme:
        """
        self.__service_filme = service_filme

    def genereaza_film(self):
        """
        creeaza random un id valid, un titlu valid, un gen valid si o descriere valida si le returneaza
        :return: id,titlu,gen,descriere
        """
        self.__id_film = random.randint(1,999)
        self.__titlu_film = random.choice(["Titanic","Django", "Godfather", "Pulp Fiction", "Shawshank Redemption", "Forrest Gump", "Fight Club", "Inception", "Interstellar",
                                           "Star Wars", "Psycho", "Reservoir Dogs", "Kill Bill", "Avengers", "Spiderman", "Batman", "Superman", "Tenet", "Avatar",
                                           "Toy Story", "Cars", "Up"])
        self.__gen_film = random.choice(["Drama", "Sci-Fi", "Actiune", "Biografie", "Animatie", "Comedie", "Documentar", "Fantasy", "Istoric", "Horror", "Musical", "Western", "Thriller", "Psihologic",
                                         "Politic", "Politist", "Aventura", "Romantic", "Stiintifico-fantastic"])
        self.__descriere_film = random.choice(["Un mare clasic", "De neratat", "O veritabila capodopera", "Captivant", "De vazut neaparat", "Un clasic instant", "In topul celor mai bune filme",
                                               "Impresionant", "O distributie de milioane", "Emotionant"])

        return self.__id_film, self.__titlu_film, self.__gen_film, self.__descriere_film


    def adauga_filme_generate(self, num):
        """
        creeaza un numar de num filme cu datele random id,titlu,gen,descriere si le adauga in lista de filme
        :param num: int
        :return: - ( adauga num filme in lista de filme )
        """
        for i in range(num):
            id, titlu, gen, descriere = self.genereaza_film()
            self.__service_filme.adauga_film(id,titlu,gen,descriere)