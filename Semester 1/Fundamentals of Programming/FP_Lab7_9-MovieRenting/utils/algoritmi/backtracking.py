
############################
"""
Mereu vom porni de la primul element din lista intr-o solutie candidat. O solutie candidat va contine indici 0 sau 1, care indica semnul
cu care se va adauga valoarea acestuia la expresia curenta(negativ sau pozitiv). Pentru fiecare operator, se testeaza daca expresia
va ramane pozitiva in continuare, si daca aceasta conditie testata prin metoda consistent() este indeplinita, se merge mai departe.
Se testeaza daca avem deja o solutie prin metoda solution(),verificand daca solutia candidat are aceeasi dimensiune ca lista data si
afisandu-se solutia in caz afirmativ cu metoda solutionFound(), altfel se trece mai departe la urmatorul nivel al solutiei candidat,
testandu-se din nou ambele valori ale urmatorului element pentru a se obtine toate solutiile posibile de distribuire a operatorilor
'+' si '-' intre elementele intregi ale listei astfel incat valoarea finala a expresiei sa fie pozitiva.
"""
############################

def solutionFound(list, candidate, dim):
    #solution = [lista]
    print(list[0], end=' ')
    for i in range(1, dim):
        if list[i] >= 0:
            if candidate[i] == 0:
                print(" - ", end=' ')
            else:
                print(" + ", end=' ')
        else:
            if candidate[i] == 0:
                print(" + ", end=' ')
            else:
                print(" - ", end=' ')
        print(list[i], end=' ')
    print("\n")


def solution(candidate, dim):
    return len(candidate) == dim


def consistent(list, candidate, index, dim):
    totalSum = sum
    expression = list[0]
    for i in range(1, dim):
        if list[i] >= 0:
            if candidate[i] == 0:
                expression -= list[i]
            elif candidate[i] == 1:
                expression += list[i]
            else:
                return False
        else:
            if candidate[i] == 0:
                expression += list[i]
            elif candidate[i] == 1:
                expression -= list[i]
            else:
                return False
    restSum = 0
    for i in range(index, len(list)):
        restSum += list[index]
    return expression + abs(restSum) >= 0


def backIter(list, dim):
    expression = list[0]
    index = 1
    candidate = [1]
    chosen = False
    if dim < 1:
        return
    elif dim == 1:
        if list[0] >= 0:
            solutionFound(list, candidate, dim)
        return

    candidate.append(-1)
    while len(candidate) > 1:
        chosen = False
        while not chosen and candidate[index] < 2:
            candidate[index] = candidate[index] + 1
            chosen = consistent(list, candidate, index+1, len(candidate))
        if chosen:
            if solution(candidate, dim):
                solutionFound(list, candidate, dim)
                if candidate[index] == 1:
                    candidate = candidate[:-1]
                    index -= 1
            else:
                candidate.append(-1)
                index += 1
        else:
            candidate = candidate[:-1]
            index -= 1


def backRec(list, candidate, dim):
    if dim < 1:
        return
    elif dim == 1:
        if list[0] >= 0:
            solutionFound(list, candidate, dim)
        return
    candidate.append(-1)
    #for index in range(1, dim):
    while candidate[-1] < 2 and len(candidate) <= dim:
        candidate[-1] = candidate[-1] + 1
        #print(len(candidate))
        if consistent(list, candidate, len(candidate), len(candidate)):
            if solution(candidate, dim):
                solutionFound(list, candidate, dim)
            backRec(list, candidate, dim)
    candidate.pop()


def ui_backtracking():
    print("Acesta este meniul pentru testare al algoritmilor de Backtracking.")
    print("Problema data este introducerea operatorilor '+' si '-' intre elementele unei liste date de numere intregi astfel incat "
          "valoarea expresiei rezultate sa fie intotdeauna pozitiva.")
    print("Optiuni disponibile: ")
    print("[recursiv] - afisarea tuturor solutiilor problemei date generate prin intermediul algoritmului de Backtracking Recursiv")
    print("[iterativ] - afisarea tuturor solutiilor problemei date generate prin intermediul algoritmului de Backtracking Iterativ")
    print("[exit] - iesirea din meniu")

    print("Introduceti optiunea dorita:")

    while True:
        optiune = input(">>>")
        optiune = optiune.strip()

        if optiune == "":
            continue
        elif optiune == "exit":
            return
        elif optiune == "recursiv":
            lista_string = input("Introduceti elementele listei: ")
            lista = lista_string.split(" ")
            for i in range(len(lista)):
                lista[i] = int(lista[i])
            candidat = [1]
            print("Solutiile problemei pentru setul de date introdus sunt:")
            backRec(lista, candidat, len(lista))
        elif optiune == "iterativ":
            lista_string = input("Introduceti elementele listei: ")
            lista = lista_string.split(" ")
            for i in range(len(lista)):
                lista[i] = int(lista[i])
            print("Solutiile problemei pentru setul de date introdus sunt:")
            backIter(lista, len(lista))
        else:
            print("comanda invalida!")


# run the console:
ui_backtracking()


