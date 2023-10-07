

class InchiriereDTO(object):

    def __init__(self,id_inchiriere,id_client,id_film,data_inchiriere,status_inchiriere):
        self.__id_inchiriere = id_inchiriere
        self.__id_client = id_client
        self.__id_film = id_film
        self.__data_inchiriere = data_inchiriere
        self.__status_inchiriere = status_inchiriere

    def get_id_inchiriere(self):
        return self.__id_inchiriere

    def get_id_client_inchiriere(self):
        return self.__id_client

    def get_id_film_inchiriere(self):
        return self.__id_film

    def get_data_inchiriere(self):
        return self.__data_inchiriere

    def get_status_inchiriere(self):
        return self.__status_inchiriere

    def set_status_inchiriere(self,value):
        self.__status_inchiriere = value

    def __eq__(self,other):
        return self.__id_inchiriere == other.get_id_inchiriere()


    #def get_status_client(self):
    #    return self.__status_client

    #def get_status_film(self):
    #    return self.__status_film

    #def set_status_client(self,value):
    #    self.__status_client = value

    #def set_status_film(self,value):
    #    self.__status_film = value
