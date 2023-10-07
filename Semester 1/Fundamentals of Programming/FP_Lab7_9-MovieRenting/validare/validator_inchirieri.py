from erori.exceptii import ValidationError

class ValidatorInchiriere(object):
    """
    valideaza atributele unice pentru clasa de legatura de Inchirieri, id si data calendaristica, introduse pentru crearea unui nou obiect Inchiriere.
    """
    def valideaza(self, inchiriere):
        erori = ""
        if inchiriere.get_id_inchiriere() < 0:
            erori += "id invalid!\n"
        data_valida = True
        data = inchiriere.get_data_inchiriere().split("/")
        if len(data) < 3:
            data_valida = False
        data_zi = int(data[0])
        data_luna = int(data[1])
        data_an = int(data[2])
        if data_zi < 1 or ( data_zi > 31 and data_luna != 2 ) or (data_zi > 28 and data_luna == 2):
            data_valida = False
        if data_luna < 1 or data_luna > 12:
            data_valida = False
        if data_an < 2000 or data_an > 2022:
            data_valida = False

        if data_valida == False:
            erori += "data invalida!\n"

        if len(erori) > 0:
            raise ValidationError(erori)