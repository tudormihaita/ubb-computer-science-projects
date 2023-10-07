import random
import string

class GeneratorClient(object):

    def __init__(self, service_clienti):
        """
        initializeaza ServiceClienti necesar pentru adaugarea clientilor generati
        :param service_clienti:
        """
        self.__service_clienti = service_clienti

    def genereaza_client(self):
        """
        genereaza random un id valid, un nume valid si un cnp valid si returneaza datele de creare a unui client
        :return: id,nume,cnp
        """
        self.__id_client = random.randint(1,999)
        self.__nume_client = random.choice(["Andrei", "George", "Daniel", "Mihaita", "Tudor", "Razvan", "Vasile", "Roxana",
                                            "Vlad", "Andreea", "Diana", "Alexandra", "Alina", "Alexandru", "Gabriel", "Maria"])
        self.__cnp_s = random.randint(1,8)
        ##self.__cnp_aa = random.randint(1,99)
        self.__cnp_ll = random.randint(1,12)
        self.__cnp_zz = random.randint(1,31)
        self.__cnp_jj = random.randint(1,52)
        self.__cnp_nnn = random.randint(1,999)
        self.__cnp_c = random.randint(0,9)
        self.__cnp_client = ""

        self.__cnp_client += str(self.__cnp_s)
        #print(str(self.__cnp_s))

        if self.__cnp_s in [1,2,3,4]:
            self.__cnp_aa = random.randint(1,99)
        else:
            self.__cnp_aa = random.randint(0,22)

        if self.__cnp_aa < 10:
            self.__cnp_client = self.__cnp_client + "0" + str(self.__cnp_aa)
        else:
            self.__cnp_client += str(self.__cnp_aa)
        #print(str(self.__cnp_aa))

        if self.__cnp_ll < 10:
            self.__cnp_client = self.__cnp_client + "0" + str(self.__cnp_ll)
        else:
            self.__cnp_client += str(self.__cnp_ll)
        #print(str(self.__cnp_ll))

        if self.__cnp_zz < 10:
            self.__cnp_client = self.__cnp_client + "0" + str(self.__cnp_zz)
        else:
            self.__cnp_client += str(self.__cnp_zz)
        #print(str(self.__cnp_zz))

        if self.__cnp_jj < 10:
            self.__cnp_client = self.__cnp_client + "0" + str(self.__cnp_jj)
        else:
            self.__cnp_client += str(self.__cnp_jj)
        #print(str(self.__cnp_jj))

        if self.__cnp_nnn < 10:
            self.__cnp_client = self.__cnp_client + "00" + str(self.__cnp_nnn)
        elif self.__cnp_nnn > 10 and self.__cnp_nnn < 100:
            self.__cnp_client = self.__cnp_client + "0" + str(self.__cnp_nnn)
        else:
            self.__cnp_client += str(self.__cnp_nnn)

        #print(str(self.__cnp_nnn))

        self.__cnp_client += str(self.__cnp_c)
        #print(str(self.__cnp_c))

        return self.__id_client,self.__nume_client, self.__cnp_client

    def adauga_clienti_generati(self, num):
        """
        creeaza un numar de num clienti cu datele generate id,nume,cnp si ii adauga in baza de date
        :param num: int
        :return: - ( adauga in baza de date cei num clienti generati )
        """
        for i in range(num):
            id, nume, cnp = self.genereaza_client()
            #print(cnp)
            self.__service_clienti.adauga_client(id, nume, cnp)


    def genereaza_string_random_cifre(self, length):
        letters = string.digits
        result_str = ''.join(random.choice(letters) for i in range(length))
        return result_str