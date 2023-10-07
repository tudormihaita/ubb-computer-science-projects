from domain.data_transfer_objects.inchirieriDTO import InchiriereDTO

def afisare_ui_recursiv(lista):
    if lista == []:
        return 0
    print(lista[0])
    return afisare_ui_recursiv(lista[1:])

def read_all_from_file_inchirieri_recursiv(lines, dict):
    if lines == []:
        return 0
    lines[0] = lines[0].strip()
    if lines[0] != "":
        parts = lines[0].split(" ")
        id_inchiriere = int(parts[0].strip())
        id_client_inchiriere = int(parts[1].strip())
        id_film_inchiriere = int(parts[2].strip())
        data_inchiriere = parts[3].strip()
        status_inchiriere = parts[4].strip()
        inchiriere_dto = InchiriereDTO(id_inchiriere,id_client_inchiriere,id_film_inchiriere,
                                       data_inchiriere,status_inchiriere)
        dict[id_inchiriere] = inchiriere_dto
    return read_all_from_file_inchirieri_recursiv(lines[1:], dict)

def cmp(a, b, key, reverse):
    if reverse is False:
        return key(a) < key(b)
    elif reverse is True:
        return key(a) > key(b)

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


def QuickSortRecursiv(lista, left, right, key, reverse):
    pos = partition(lista, left, right, key, reverse)

    if left < pos - 1:
        QuickSortRecursiv(lista, left, pos - 1, key, reverse)
    if pos + 1 < right:
        QuickSortRecursiv(lista, pos + 1, right, key, reverse)
    return lista

def test_recursivitate():
    lista = [1, 2, 3, 4, 5]
    afisare_ui_recursiv(lista)
    print("test afisare recursiva trecut cu succes!")

#test_recursivitate()