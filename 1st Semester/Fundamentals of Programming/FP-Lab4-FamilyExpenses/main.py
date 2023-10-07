from testing_environment.tests import run_all_tests
from user_interface.ui import run_ui, printMenu, run_ui_test


def main():
    run_all_tests()
    printMenu()
    run_ui()

main()