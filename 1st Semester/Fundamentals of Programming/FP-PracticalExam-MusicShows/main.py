from testare.teste_spectacole import TestareSpectacole
from repositories.repo_spectacole import RepoSpectacole
from validator.validare_spectacole import ValidareSpectacole
from controller.service_spectacole import ServiceSpectacole
from ui.consola import UI

if __name__ == '__main__':
    teste_spectacole = TestareSpectacole()
    repo_spectacole = RepoSpectacole("spectacole.txt")
    validator_spectacole = ValidareSpectacole()
    service_spectacole = ServiceSpectacole(repo_spectacole, validator_spectacole)
    consola = UI(service_spectacole)
    teste_spectacole.ruleaza_toate_testele()
    consola.help()
    consola.run()