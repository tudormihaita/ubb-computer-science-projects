from teste.testare_filme import TesteFilme
from teste.testare_clienti import TesteClienti
from teste.testare_inchirieri import TesteInchirieri
from validare.validator_filme import ValidatorFilm
from validare.validator_clienti import ValidatorClient
from validare.validator_inchirieri import ValidatorInchiriere
from persistenta.repos_filme import RepoFilm
from persistenta.repos_clienti import RepoClient
from persistenta.repos_inchirieri import RepoInchiriere
from business.servicii_filme import ServiceFilm
from business.servicii_clienti import ServiceClient
from business.servicii_inchirieri import ServiceInchiriere
from prezentare.consola import UI
from persistenta.file_repo_clienti import FileRepoClienti
from persistenta.file_repo_filme import FileRepoFilme
from persistenta.file_repo_inchirieri import FileRepoInchirieri
#from persistenta.repos_clienti_fisiere import ClientRepositoryFile
from generari.generare_clienti import GeneratorClient
from generari.generare_filme import GeneratorFilm

if __name__ == '__main__':
    teste_filme = TesteFilme()
    teste_clienti = TesteClienti()
    teste_inchirieri = TesteInchirieri()
    teste_filme.ruleaza_toate_testele_filme()
    teste_clienti.ruleaza_toate_testele_clienti()
    teste_inchirieri.ruleaza_toate_testele_inchirieri()
    validator_film = ValidatorFilm()
    repo_film = RepoFilm()
    validator_client = ValidatorClient()
    repo_client = RepoClient()
   #repo_client = ClientRepositoryFile("fisier.txt")
    file_repo_client = FileRepoClienti("clienti.txt")
    file_repo_film = FileRepoFilme("filme.txt")
    file_repo_inchiriere = FileRepoInchirieri("inchirieri.txt")

    repo_inchiriere = RepoInchiriere()
    validator_inchiriere = ValidatorInchiriere()
    service_client = ServiceClient(file_repo_client,validator_client,file_repo_inchiriere)
    #service_client = ServiceClient(repo_client, validator_client, repo_inchiriere)
    service_film = ServiceFilm(file_repo_film, validator_film, file_repo_inchiriere)
    #service_film = ServiceFilm(repo_film, validator_film,repo_inchiriere)
    service_inchiriere = ServiceInchiriere(file_repo_inchiriere, validator_inchiriere, file_repo_client, file_repo_film,"rezultat_raport.txt")
    #service_inchiriere = ServiceInchiriere(repo_inchiriere,validator_inchiriere,repo_client,repo_film)

    generator_client = GeneratorClient(service_client)
    generator_film = GeneratorFilm(service_film)

    #consola = UI(service_film, service_client,service_inchiriere)
    consola = UI(service_film,service_client,service_inchiriere,generator_client,generator_film)
    consola.run()


    #test_string = genereaza_string_random_cifre(2)
    #print(test_string)
    #print(strtobool("True"))

