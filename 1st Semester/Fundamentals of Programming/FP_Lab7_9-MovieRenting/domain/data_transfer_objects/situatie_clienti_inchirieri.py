
class SituatieClientiInchiriere(object):
    """
    creeaza un obiect DTO prin care pentru fiecare client cu inchirieri se vor contoriza toate inchirierile efectuate de acesta.
    """
    def __init__(self, client, lista_filme_inchiriate):
        self.__client = client
        self.__lista_filme_inchiriate = lista_filme_inchiriate
        self.__numar_filme_inchiriate = len(self.__lista_filme_inchiriate)

    def get_client_situatie(self):
        #return self.__dict["id"]
        return self.__client

    def get_filme_inchiriate(self):
        #return self.__dict["filme_inchiriate"]
        return self.__lista_filme_inchiriate

    def get_numar_filme_inchiriate(self):
        return self.__numar_filme_inchiriate

    def set_client_situatie(self,value):
        #self.__dict["id"] = value
        self.__client = value

    def set_filme_inchiriate(self,value):
        #self.__dict["filme_inchiriate"] = value
        self.__lista_filme_inchiriate = value

    def __str__(self):
        return f"[{self.__client.get_id_client()}] {self.__client.get_nume_client()} : {self.__lista_filme_inchiriate} ({self.__numar_filme_inchiriate})"