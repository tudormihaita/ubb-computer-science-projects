
class SituatieFilmeInchiriere(object):
    """
    creeaza un obiect DTO pentru fiecare film inchiriat care contorizeaza clientii ce au inchiriat obiectul Film respectiv
    """
    def __init__(self, film, lista_clienti):
        self.__film = film
        self.__lista_clienti = lista_clienti
        self.__numar_clienti = len(self.__lista_clienti)
        #self.__file_path =  "rezultat_raport.txt"

    def get_film_situatie(self):
        return self.__film

    def get_clienti_film_inchiriat(self):
        return self.__lista_clienti

    def get_numar_clienti_situatie(self):
        return self.__numar_clienti

    def set_film_situatie(self, value):
        self.__film = value

    def set_clienti_situatie(self, value):
        self.__lista_clienti = value

    def __str__(self):
        return f"[{self.__film.get_id_film()}] {self.__film.get_titlu_film()} : {self.__lista_clienti} ({self.__numar_clienti})"

    #def write_to_file(self):
        #with open(self.__file_path, "w") as f:
            #pass
