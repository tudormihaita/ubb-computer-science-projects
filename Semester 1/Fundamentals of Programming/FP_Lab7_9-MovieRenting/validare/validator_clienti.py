from erori.exceptii import ValidationError

class ValidatorClient(object):
    """"
    valideaza atributele id, nume si cnp introduse pentru crearea unui obiect de tip Client.
    """
    def valideaza(self, client):
        erori = ""
        if client.get_id_client() < 0:
            erori += "id invalid!\n"
        if client.get_nume_client() == "" or len(client.get_nume_client()) < 2:
            erori += "nume invalid!\n"

        cnp_invalid = False
        if len(client.get_cnp_client()) != 13:
            cnp_invalid = True

        if cnp_invalid == False:
            cnp_s = client.get_cnp_client()[0]
            cnp_aa = client.get_cnp_client()[1] + client.get_cnp_client()[2]
            cnp_ll = client.get_cnp_client()[3] + client.get_cnp_client()[4]
            cnp_zz = client.get_cnp_client()[5] + client.get_cnp_client()[6]
            cnp_jj = client.get_cnp_client()[7] + client.get_cnp_client()[8]
            cnp_nnn = client.get_cnp_client()[9] + client.get_cnp_client()[10] + client.get_cnp_client()[11]
            cnp_c = client.get_cnp_client()[12]
            cnp_s = int(cnp_s)
            cnp_aa = int(cnp_aa)
            cnp_ll = int(cnp_ll)
            cnp_zz = int(cnp_zz)
            cnp_jj = int(cnp_jj)
            cnp_nnn = int(cnp_nnn)
            cnp_c = int(cnp_c)
            if cnp_s < 1 or cnp_s > 8:
                cnp_invalid = True
            if (cnp_s == 5 and cnp_aa > 22) or (cnp_aa > 22 and cnp_s == 6):
                cnp_invalid = True
            if cnp_ll < 1 or cnp_ll > 12:
                cnp_invalid = True
            if cnp_zz < 1 or cnp_zz > 31:
                cnp_invalid = True
            # JJ - cod judet intre 1 si 52
            if cnp_jj < 1 or cnp_jj > 52:
                cnp_invalid = True
            if cnp_nnn < 1 or cnp_nnn > 999:
                cnp_invalid = True
            if cnp_c < 0:
                cnp_invalid = True

        if cnp_invalid == True:
            erori += "cnp invalid!\n"

        if len(erori) > 0:
            raise ValidationError(erori)

