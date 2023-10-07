class Film(object):
    """
    creeaza un obiect de tip Film, care primeste un id unic, un titlu, un gen si o descriere.
    """
    def __init__(self,id_film,titlu_film,gen_film,descriere_film):
        self.__id_film = id_film
        self.__titlu_film = titlu_film
        self.__gen_film = gen_film
        self.__descriere_film = descriere_film
        #self.__status_film = True


    def get_id_film(self):
        return self.__id_film

    def get_titlu_film(self):
        return self.__titlu_film

    def get_descriere_film(self):
        return self.__descriere_film

    def get_gen_film(self):
        return self.__gen_film

    #def get_status_film(self):
        #return self.__status_film

    def set_titlu_film(self,value):
        self.__titlu_film = value

    def set_descriere_film(self,value):
        self.__descriere_film = value

    def set_gen_film(self,value):
        self.__gen_film = value

    #def set_status_film(self,value):
        #self.__status_film = value

    def __eq__(self,other):
        return self.__id_film == other.__id_film

    def __str__(self):
        return f"[{self.__id_film}] {self.__titlu_film} ({self.__descriere_film}) - {self.__gen_film}"
