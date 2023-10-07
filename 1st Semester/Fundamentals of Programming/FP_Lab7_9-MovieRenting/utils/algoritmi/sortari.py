"""
def partition(lista, left, right, key, reverse):
    pivot = lista[left]
    i = left
    j = right
    while i != j:
        # while lista[j] >= pivot and i < j:
        while not cmp(lista[j], pivot, key, reverse) and i < j:
            j -= 1
        lista[i] = lista[j]
        # while lista[i] <= pivot and i < j:
        while cmp(lista[i], pivot, key, reverse) and i < j:
            i += 1
        lista[j] = lista[i]
    lista[i] = pivot
    return i


def QuickSortRec(lista, left, right, key, reverse):
    pos = partition(lista, left, right, key, reverse)

    if left < pos - 1:
        # if cmp(left, pos - 1, key, reverse):
        QuickSortRec(lista, left, pos - 1, key, reverse)
    if pos + 1 < right:
        # if cmp(pos + 1, right, key, reverse):
        QuickSortRec(lista, pos + 1, right, key, reverse)
    return lista
"""

##################################################################################################

def cmp(a, b, key, reverse):
    if reverse is False:
        return key(a) < key(b)
    elif reverse is True:
        return key(a) > key(b)


# de modificat : gasit modalitatea de accesare a celeilalte valori a tuplului transmis drept key
def cmp_2(a, b, key, reverse):
    if reverse is False:
        if key(a)[0] < key(b)[0]:
            return True
        elif key(a)[0] == key(b)[0]:
            if key(a)[0] < key(b)[0]:
                return True
    elif reverse is True:
        if key(a)[0] > key(b)[0]:
            return True
        elif key(a)[0] == key(b)[0]:
            if key(a)[0] > key(b)[0]:
                return True
    return False


def QuickSort(lista, cmp, key, reverse):
    if len(lista) <= 1:
        return lista
    pivot = lista.pop()
    # lesser = QuickSort([x for x in lista if x < pivot])
    lesser = QuickSort([x for x in lista if cmp(x, pivot, key, reverse)], cmp, key, reverse)
    # greater = QuickSort([x for x in lista if x >= pivot])
    greater = QuickSort([x for x in lista if not cmp(x, pivot, key, reverse)], cmp, key, reverse)
    return lesser + [pivot] + greater


def merge(left, right, key, reverse):
    result = []
    i = 0
    j = 0

    while i < len(left) and j < len(right):
        if cmp(left[i], right[j], key, reverse) is True:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    while i < len(left):
        result.append(left[i])
        i += 1

    while j < len(right):
        result.append(right[j])
        j += 1

    return result


def MergeSort(lista, cmp, key, reverse):
    """
    returneaza lista initiala sortata prin intermediul algoritmului de MergeSort crescator sau descrescator in functie de
    parametrul reverse, criteriul fiind stabilit in functie de criteriul furnizat prin parametrul key
    :param lista: lista de entitati preluate prin metoda get_all()
    :param key: parametru preluat prin functia lambda
    :param reverse: bool
    :return: lista sortata
    """
    if len(lista) <= 1:
        return lista
    mid = len(lista) // 2
    left = MergeSort(lista[:mid], cmp, key, reverse)
    right = MergeSort(lista[mid:], cmp, key, reverse)
    return merge(left, right, key, reverse)


def minMax(lista, key, reverse):
    min = max = lista[0]
    for i in range(1, len(lista)):
        if cmp(lista[i], min, key, reverse):
            min = lista[i]
        if cmp(max, lista[i], key, reverse):
            max = lista[i]
    return min, max


def BingoSort(lista, cmp, key, reverse):
    """
    returneaza lista initiala sortata prin intermediul algoritmului de BingoSort crescator sau descrescator in functie de
    parametrul reverse, criteriul fiind stabilit in functie de criteriul furnizat prin parametrul key
    :param lista: lista de entitati preluate prin metoda get_all()
    :param key: parametru preluat prin functia lambda
    :param reverse: bool
    :return: lista sortata
    """
    bingo, nextBingo = minMax(lista, key, reverse)
    largestElement = nextBingo
    nextElementPos = 0
    # print(bingo,nextBingo)
    while cmp(bingo, nextBingo, key, reverse):
        startPos = nextElementPos
        for i in range(startPos, len(lista)):
            if lista[i] == bingo:
                lista[i], lista[startPos] = lista[startPos], lista[i]
                nextElementPos += 1
            elif cmp(lista[i], nextBingo, key, reverse):
                nextBingo = lista[i]
        bingo = nextBingo
        nextBingo = largestElement

    return lista


def sorteaza(lista, method, cmp, key, reverse):
    """
    Metoda generala de apelare a algoritmilor de sortare, in functie de preferinta utilizatorului
    :param lista: structura de date de tip lista care contine datele de intrare ce urmeaza a fi sortate
    :param method: algoritmul de sortare utilizat
    :param cmp: metoda care seteaza relatia de comparare stabilita intre elemente pentru a determina ordinea in lista sortata
    :param key: metoda reprezentata de functia anonima lambda prin care se furnieaza criteriile dupa care vor fi sortate elementele listei
    :param reverse: criteriul ( crescator/descrescator) pe baza caruia se va stabili sortarea listei, cat si conditia de comparare
    :return: lista sortata in functie de criteriile specificate
    """
    metode_sortari = {
        "MergeSort": MergeSort,
        "BingoSort": BingoSort,
        "QuickSort": QuickSort
    }

    return metode_sortari[method](lista, cmp, key, reverse)

