

class Inchiriere(object):
    """
    creeaza un obiecte de legatura Inchiriere intre clasele de clienti si filme, prin care se retine un id unic, un client care efectueaza inchirierea
    filmul inchiriat si data calendaristica la care s-a efectuat inchirierea respectiva.
    """
    def __init__(self,id_inchiriere, client, film, data_inchiriere,status_inchiriere):
        self.__id_inchiriere = id_inchiriere
        self.__client = client
        self.__film = film
        self.__data_inchiriere = data_inchiriere
        self.__status_inchiriere = status_inchiriere

    def get_id_inchiriere(self):
        return self.__id_inchiriere

    def get_client_inchiriere(self):
        return self.__client

    def get_film_inchiriere(self):
        return self.__film

    def get_data_inchiriere(self):
        return self.__data_inchiriere

    def get_status_inchiriere(self):
        return self.__status_inchiriere

    #def get_status_client(self):
    #    return self.__status_client

    #def get_status_film(self):
    #    return self.__status_film

    def set_data_inchiriere(self, value):
        self.__data_inchiriere = value

    def set_status_inchiriere(self, value):
        self.__status_inchiriere = value

    #def set_status_client(self,value):
    #    self.__status_client = value

    #def set_status_film(self,value):
    #    self.__status_film = value

    def __eq__(self,other):
        return self.__id_inchiriere == other.__id_inchiriere

    def __str__(self):
        return f"[{self.__id_inchiriere}] ({self.__data_inchiriere}) {self.__client.get_nume_client()} - {self.__film.get_titlu_film()}"
