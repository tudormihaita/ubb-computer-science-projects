
class Spectacol(object):

    def __init__(self, titlu, artist, gen, durata):
        """
        initialieaza atributele obiectului de tip spectacol
        :param titlu: string, nevid
        :param artist: string, nevid
        :param gen: string, una dintre: Comedie, Concert, Balet, Altele
        :param durata: int, strict pozitiv
        """
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__durata = durata

    def get_titlu_spectacol(self):
        """
        obtine atributul titlu de pe un obiect de tip spectacol
        :return: titlu (string)
        """
        return self.__titlu

    def get_artist_spectacol(self):
        """
        obtine atributul artist de pe un obiect de tip spectacol
        :return: artist (string)
        """
        return self.__artist

    def get_gen_spectacol(self):
        """
        obtine atributul gen de pe un obiect de tip spectacol
        :return: gen (string)
        """
        return self.__gen

    def get_durata_spectacol(self):
        """
        obtine atributul durata de pe un obiect de tip spectacol
        :return: durata (int)
        """
        return self.__durata

    def set_durata_spectacol(self, value):
        self.__durata = value

    def set_gen_spectacol(self, value):
        self.__gen = value

    def set_artist_spectacol(self, value):
        self.__artist = value

    def set_titlu_spectacol(self, value):
        self.__titlu = value

    def __eq__(self, other):
        """
        defineste egalitatea intre 2 obiecte de tip spectacol, unic identificate prin titlu si artist
        :param other: spectacol
        :return: True daca titlul si artistu ambelor obiecte sunt identice, False altfel
        """
        return self.__titlu == other.__titlu and self.__artist == other.__artist

    def __str__(self):
        """
        defineste formatul de afisare a unui obiect de tip spectacol cu atributele titlu, artist, gen, durata
        :return: string de afisare cu atributele obiectului separate prin spatiu
        """
        return f"{self.__titlu} {self.__artist} {self.__gen} {self.__durata}"