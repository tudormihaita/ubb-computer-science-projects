from erori.exceptii import ValidationError

class ValidareSpectacole(object):

    def valideaza(self, spectacol):
        """
        verifica daca spectacolul dat este valid, adica indeplineste conditiile:
        titlu, nume_artist- string-uri nevide
        durata - numar intreg strict pozitiv
        gen - string, unul dintre: ["Comedie", "Concert", "Balet", "Altele"]
        :param spectacol: spectacol
        :return: - (verifica daca obiectul spectacol este valid)
        :raises: ValidationError: str(erori) daca unul sau mai multe dintre atributele spectacolului sunt invalide
        """
        erori = ""
        genuri = ["Comedie", "Concert", "Balet", "Altele"]

        if spectacol.get_titlu_spectacol() == "":
            erori += "Titlu nevid!\n"

        if spectacol.get_artist_spectacol() == "":
            erori += "Nume artist nevid!\n"

        if spectacol.get_durata_spectacol() < 0:
            erori += "Durata trebuie sa fie intreg pozitiv!\n"

        if spectacol.get_gen_spectacol() not in genuri:
            erori += "Genul trebuie sa fie unul dintre: Comedie, Concert, Balet, Altele!\n"

        if len(erori) > 0:
            raise ValidationError(erori)