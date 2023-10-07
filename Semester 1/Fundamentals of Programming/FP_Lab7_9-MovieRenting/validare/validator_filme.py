from erori.exceptii import ValidationError

class ValidatorFilm(object):
    """
    valideaza atributele id, titlu, gen si descriere introduse pentru crearea unui obiect de tipul Film.
    """
    def valideaza(self, film):
        erori = ""
        if film.get_id_film()<0:
            erori += "id invalid!\n"
        if film.get_titlu_film() == "" or len(film.get_titlu_film()) < 2:
            erori += "titlu invalid!\n"
        if film.get_gen_film() == "" or len(film.get_gen_film()) < 2:
            erori += "gen invalid!\n"
        if film.get_descriere_film() == "" or len(film.get_descriere_film()) < 2:
            erori += "descriere invalida!\n"
        if len(erori)>0:
            raise ValidationError(erori)

