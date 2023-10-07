class Client(object):
    """
    creeaza un obiect de tipul Client, care va primi un id unic, un nume si un cnp
    """
    def __init__(self,id_client,nume_client,cnp_client):
        self.__id_client = id_client
        self.__nume_client = nume_client
        self.__cnp_client = cnp_client
        #self.__status_client = True


    def get_id_client(self):
        return self.__id_client

    def get_nume_client(self):
        return self.__nume_client

    def get_cnp_client(self):
        return self.__cnp_client

    #def get_status_client(self):
        #return self.__status_client

    def set_nume_client(self,value):
        self.__nume_client = value

    def set_cnp_client(self,value):
        self.__cnp_client = value

    #def set_status_client(self,value):
        #self.__status_client = value

    def __eq__(self,other):
        return self.__id_client == other.__id_client or self.__cnp_client == other.__cnp_client

    def __str__(self):
        return f"[{self.__id_client}] {self.__nume_client} - ({self.__cnp_client})"

    #def __str__(self):
        #return f"{self.__id_client} {self.__nume_client} {self.__cnp_client}"
