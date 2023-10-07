from domain.clienti import Client
from persistenta.repos_clienti import RepoClient

class ClientRepositoryFile(RepoClient):


    def __init__(self, fileName):
        RepoClient.__init__(self)
        self.__fileName = fileName

        self.__loadFromFile2()

    def __createClientFromLine(self, line):


        fields = line.strip().split(" ")
        client = Client(int(fields[0]), fields[1], fields[2])
        return client

    def __loadFromFile(self):

        fh = open(self.__fileName)
        # read in the entire file
        content = fh.read()
        fh.close()
        lines = content.split('\n')
        for line in lines:
            if line.strip() == "":
                continue  # we have an empty line, just skip
            client = self.__createClientFromLine(line)

            self._clienti[client.get_id_client()] = client

    def __loadFromFile2(self):

        fh = open(self.__fileName)
        for line in fh:
            if line.strip() == "":
                continue
            client = self.__createClientFromLine(line)

            RepoClient.adauga_client(self, client)
        fh.close()

    def store(self, client):

        RepoClient.adauga_client(self, client)
        self.__appendToFile(client)

    def __appendToFile(self, client):

        fh = open(self.__fileName, "a")
        line = client.get_id_client() + " " + client.get_nume_client() + " " + client.get_cnp_client()
        fh.write("\n")
        fh.write(line)
        fh.close()


def testRepo():
    fileName = "test.txt"

    #clearFileContent(fileName)
    f = open(fileName, "w")
    f.close()
    repo = ClientRepositoryFile(fileName)
    assert (len(repo) == 0)
    repo.store(Client("23", "Andrei", "1020304118923"))
    assert (len(repo) == 1)


def testRead():
    fileName = "test.txt"
    # make sure wi start with an empty file
    #clearFileContent(fileName)
    f = open(fileName, "w")
    f.close()

    repo = ClientRepositoryFile(fileName)
    repo.store(Client("19", "George", "1030508229913"))
    repo.store(Client("9", "Vlad", "1031208038923"))

    #repo2 = ClientRepositoryFile(fileName)
    assert ( len(repo) == 2)


testRepo()
testRead()