#pragma once
#pragma warning (disable: 26823) // dereferencing null pointer
#pragma warning (disable: 26472) // don't use static_cast
#include "UI.h"
#include <iostream>

using std::cout;
using std::cin;
using std::getline;
using std::ws;

const int ConsoleUI::readBookId() {
	int id;
	cin >> id;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw InvalidInputException("Input invalid, introduceti un numar valid!\n");
		}
	return id;
}

string ConsoleUI::readBookISBN() {
	string ISBN; getline(cin >> ws, ISBN);
	for (auto& c : ISBN) c = static_cast<char>(toupper(c));
	return ISBN;
}

string ConsoleUI::readBookTitle() {
	string title; getline(cin >> ws, title);
	title.at(0) = static_cast<char>(toupper(title.at(0)));
	return title;
}

string ConsoleUI::readBookAuthor(){
	string author; getline(cin >> ws , author);
	author.at(0) = static_cast<char>(toupper(author.at(0)));
	return author;
}

string ConsoleUI::readBookGenre() {
	string genre; getline(cin >> ws, genre);
	genre.at(0) = static_cast<char>(toupper(genre.at(0)));
	return genre;
}

string ConsoleUI::readBookPublisher() {
	string publisher; getline(cin >> ws, publisher);
	publisher.at(0) = static_cast<char>(toupper(publisher.at(0)));
	return publisher;
}

const int ConsoleUI::readBookReleaseYear(){
	int release_year;
	cin >> release_year;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw InvalidInputException("Input invalid, introduceti un numar valid!\n");
		}

	return release_year;
}


void ConsoleUI::printBooklist(const vector<Book>& booklist) {
	for (const auto& book : booklist) {
		cout << book << "\n";
		/*cout << "| " << book.getISBN() << " | " << book.getTitle() << " | " << book.getAuthor() << " | " <<
			book.getGenre() << " | " << book.getPublisher() << " | " << book.getYear() << " |\n";*/
	}
}


void ConsoleUI::printMenu() {
	cout << "Comenzi disponibile:\n";
	cout << " -----     [help]       -----\n";
	cout << " ----------------------------\n";
	cout << " ----- [display_books]  -----\n";
	cout << " ----- [display_report] -----\n";
	cout << " ----- [add_book]       -----\n";
	cout << " ----- [find_book]      -----\n"; 
	cout << " ----- [delete_book]    -----\n";
	cout << " ----- [update_book]    -----\n"; 
	cout << " ----- [filter_books]   -----\n";
	cout << " ----- [sort_books]     -----\n";
	cout << " ----------------------------\n";
	cout << " -------    [undo]    -------\n";
	cout << " ----------------------------\n";
	cout << " ---  [add_to_wishlist]   ---\n";
	cout << " - [add_random_to_wishlist] -\n";
	cout << " ---  [display_wishlist]  ---\n";
	cout << " ---  [export_wishlist]   ---\n";
	cout << " ---  [clear_wishlist]    ---\n";
	cout << " ----------------------------\n";
	cout << " -----     [exit]       -----\n";
}


void ConsoleUI::helpCommandsUI() {
	cout << "Introduceti comanda pentru care doriti sa vizualizati detalii:\n";
	string cmd;
	cin >> cmd;
	if (cmd == "display_books") {
		cout << "[display_books] - Afiseaza toate cartile introduse in biblioteca\n";
	}
	else if (cmd == "add_book") {
		cout << "[add_book] - Adauga o noua carte in biblioteca, specificand urmatoarele atribute pentru care se respecta anumite reguli:\n";
		cout << "id - Numar de identificare unic pentru carte\n";
		cout << "titlu - Titlul cartii, format doar din litere mici si mari si alte anumite caractere speciale specifice\n";
		cout << "autor - Numele autorului cartii, format doar din litere mici si mari\n";
		cout << "gen - Genul cartii, un sir de caractere valid de lungime minim 2\n";
		cout << "editura -  Editura responsabila de publicarea cartii, un sir de caractere valid de lungime minim 2\n";
		cout << "an - Anul aparitiei cartii, un numar natural valid\n";
	}
	else if (cmd == "find_book") {
		cout << "[find_book] - Cauta o carte existenta in biblioteca, prin specificarea codului unic de inregistrare ISBN\n";
	}
	else if (cmd == "delete_book") {
		cout << "[delete_book] - Sterge o carte deja existenta in biblioteca, prin specificarea codului unic de inregistrare ISBN\n";
	}
	else if (cmd == "update_book") {
		cout << "[update_book] - Modifica genul si editura unei carti, cautata dupa codul unic de inregistrare ISBN\n";
	}
	else if (cmd == "filter_books") {
		cout << "[filter_books] - Afiseaza o lista de carti filtrata dupa unul din criteriile prezentate\n";
	}
	else if (cmd == "sort_books") {
		cout << "[sort_books] - Afiseaza o lista de carti sortate dupa criteriile prezentate\n";
	}
	else if (cmd == "add_to_wishlist") {
		cout << "[add_to_wishlist] - Adauga o carte in wishlist-ul curent, oferind o lista de carti disponibile in biblioteca cu titlul cautat," 
			"din care se va putea alege cartea dorita prin specificarea ISBN-ului corespunzator\n";
	}
	else if (cmd == "add_random_to_wishlist") {
		cout << "[add_random_to_wishlist] - Adauga la wishlist un numar dat de carti, alese aleator din oferta curenta a bibliotecii\n";
	}
	else if (cmd == "display_wishlist") {
		cout << "[display_wishlist] - Afiseaza cartile adaugate la wishlist-ul curent\n";
	}
	else if (cmd == "clear_wishlist") {
		cout << "[clear_wishlist] - Goleste wishlist-ul curent\n";
	}
	else if (cmd == "export_wishlist") {
		cout << "[export_wishlist] - Exporta wishlist-ul curent intr-un fisier cu numele introdus de la tastatura\n";
	}
	else if (cmd == "display_report") {
		cout << "[display_report] - Genereaza si afiseaza o statistica a cartilor de biblioteca contorizate in functie de genul acestora\n";
	}
	else if (cmd == "undo") {
		cout << "[undo] - Inverseaza efectul ultimei operatii efectuate asupra listei de carti, readucand-o la stadiul anterior\n";
	}
	else {
		cout << "Comanda introdusa este invalida!\n";
	}
}

void ConsoleUI::populateLibraryUI() {
	this->bookService.storeBook(23, "To Kill a Mockingbird", "Harper Lee", "Thriller", "Humanitas", 1960);
	this->bookService.storeBook(17, "War and Peace", "Lev Tolstoi", "War story", "Corint", 1869);
	this->bookService.storeBook(15, "War and Peace", "Lev Tolstoi", "War story", "Arthur", 1887);
	this->bookService.storeBook(14, "In Search of Lost Time", "Marcel Proust", "Fictiune filosofica", "Humanitas", 1890);
	this->bookService.storeBook(67, "The Trial", "Franz Kafka", "Fictiune filosofica", "Art", 1925);
	this->bookService.storeBook(6, "Les Miserables", "Victor Hugo", "Tragedie", "Humanitas", 1862);
	this->bookService.storeBook(19, "The Castle", "Franz Kafka", "Comedie", "Corint", 1926);
	this->bookService.storeBook(96, "Madame Bovary", "Gustave Flaubert", "Tragedie", "Humanitas", 1862);
	this->bookService.storeBook(12, "The Divine Comedy", "Dante Alighieri", "Drama", "Arthur", 1862);
	this->bookService.storeBook(2, "The Brothers Karamazov", "Fyodor Dostoyevsky", "Tragic", "Humanitas", 1862);

	cout << "-------- Librarie populata cu succes! --------\n";
}

void ConsoleUI::clearScreenUI() noexcept {
	system("cls");
}


void ConsoleUI::displayBooksUI() {
	const vector<Book>& booklist = this->bookService.getAllBooks();

	if (booklist.size() == 0) {
		cout << "Nu exista carti adaugate in biblioteca!\n";
	}
	else {
		this->printBooklist(booklist);
	}

}

void ConsoleUI::addBookUI() {
	string title, author, genre, publisher;
	int idNumber = -1, releaseYear = -1;
	cout << " --------  Adaugati o carte noua  --------\n";
	cout << "Numar identificare unic -> "; idNumber = this->readBookId();
	cout << "Titlu -> "; title = this->readBookTitle();
	cout << "Autor -> "; author = this->readBookAuthor();
	cout << "Gen -> "; genre = this->readBookGenre();
	cout << "Editura -> "; publisher = this->readBookPublisher();
	cout << "Anul aparitiei -> "; releaseYear = this->readBookReleaseYear();

	this->bookService.storeBook(idNumber, title, author, genre, publisher, releaseYear);
	cout << " -------- Carte adaugata cu succes! --------\n";
}

void ConsoleUI::findBookUI() {
	if (this->bookService.getSize() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua cautarea!\n";
		return;
	}

	cout << " --------     Cautati o carte     --------\n";
	cout << "ISBN-ul cartii cautate -> "; string ISBN = this->readBookISBN();

	Book foundBook = this->bookService.findBook(ISBN);
	cout << " -------- Carte gasita cu succes: --------\n";

	cout << "| "<< foundBook.getISBN()<< " | " << foundBook.getTitle() << " | " << foundBook.getAuthor() << " | " <<
		foundBook.getGenre() << " | " << foundBook.getPublisher() << " | " <<  foundBook.getYear() << " |\n";

	cout << "\n";

}

void ConsoleUI::deleteBookUI(){
	if (this->bookService.getSize() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua stergerea!\n";
		return;
	}

	/*cout << "Cartile disponibile pentru stergere sunt urmatoarele: \n";
	this->displayBooksUI();*/

	cout << " --------     Stergeti o carte     --------\n";
	cout << "ISBN-ul cartii cautate -> "; string ISBN = this->readBookISBN();

	Book deletedBook = this->bookService.removeBook(ISBN);
	cout << " -------- Carte stearsa cu succes: --------\n";

	cout << "| " << deletedBook.getISBN() << " | " << deletedBook.getTitle() << " | " << deletedBook.getAuthor() << " | " <<
		deletedBook.getGenre() << " | " << deletedBook.getPublisher() << " | " << deletedBook.getYear() << " |\n";

	cout << "\n";
}

void ConsoleUI::updateBookUI(){
	if (this->bookService.getSize() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua modificarea!\n";
		return;
	}

	/*cout << "Cartile disponibile pentru modificare sunt urmatoarele: \n";
	this->displayBooksUI();*/

	cout << " --------     Modificati o carte     --------\n";
	cout << "ISBN-ul cartii cautate -> "; string ISBN = this->readBookISBN();

	cout << "Genul nou -> "; string new_genre = this->readBookGenre();
	cout << "Editura noua -> "; string new_publisher = this->readBookPublisher();
	Book oldBook = this->bookService.updateBook(ISBN, new_genre, new_publisher);

	cout << " -------- Carte modificata cu succes: --------\n";

	cout << "| " << oldBook.getISBN() << " | " << oldBook.getTitle() << " | " << oldBook.getAuthor() << " | " <<
		oldBook.getGenre() << " | " << oldBook.getPublisher() << " | " << oldBook.getYear() << " |\n";

	cout << "\n";
}

void ConsoleUI::filterBooksUI() {
	if (this->bookService.getSize() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua filtrarea!\n";
		return;
	}
	int filterType = -1;
	cout << " -------- Introduceti tipul de filtrare dorit: -------- \n";
	cout << "1 - Filtrare carti aparute intre anii dati\n";
	cout << "2 - Filtrare carti gen dat\n";

	cout << "Tip filtrare -> "; cin >> filterType;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Optiune introdusa invalida, nu se poate efectua filtrarea!\n";
		return;
	}

	if (filterType == 1) {
		cout << "Intervalul de aparitie pentru care se vor filtra cartile -> ";

		const int minReleaseYear = this->readBookReleaseYear();
		const int maxReleaseYear = this->readBookReleaseYear();

		vector<Book> filteredBooks = this->bookService.filterByReleaseYear(minReleaseYear, maxReleaseYear);

		if (filteredBooks.size() == 0) {
			cout << " -------- Au fost filtrate toate cartile! --------\n";
			return;
		}
		else {
			cout << " -------- Cartile filtrate dupa anul aparitiei sunt: -------- \n";
			this->printBooklist(filteredBooks);
		}
	}
	else if (filterType == 2) {
		cout << "Genul de carte filtrat -> ";
		string genreFilter = this->readBookGenre();

		vector<Book> filteredBooks = this->bookService.filterByGenre(genreFilter);

		if (filteredBooks.size() == 0) {
			cout << " -------- Au fost filtrate toate cartile! --------\n";
			return;
		}
		else {
			cout << " -------- Cartile filtrate dupa gen sunt: -------- \n";
			this->printBooklist(filteredBooks);
		}
	}
	else {
		cout << "Tip filtrare invalid, nu s-a putut efectua filtrarea!\n";
	}
}

void ConsoleUI::sortBooksUI() {
	if (this->bookService.getSize() == 0) {
		cout << "Nu exista carti introduse in biblioteca, nu se poate efectua sortarea!\n";
		return;
	}


	int sortType = -1;
	cout << " -------- Introduceti tipul de sortare dorit: --------\n";
	cout << "1 - Sortare dupa titlu\n";
	cout << "2 - Sortare dupa autor\n";
	cout << "3 - Sortare dupa an aparitie si gen\n";

	cout << "Tip sortare ->"; cin >> sortType;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Optiune introdusa invalida, nu se poate efectua filtrarea!\n";
		return;
	}

	if (sortType == 1) {
		char criteria = 'c';
		bool reversed = false;

		cout << " -------- Introduceti criteriul de sortare: --------\n";
		cout << "c - sortare crescatoare\n";
		cout << "d - sortare descrescatoare\n";

		cout << "Criteriu sortare -> "; cin >> criteria;

		if (criteria != 'c' && criteria != 'd') {
			cout << "Criteriu de sortare invalid, nu se poate efectua sortarea!\n";
			return;
		}

		if (criteria == 'c')
			reversed = false;
		else if (criteria == 'd')
			reversed = true;

		vector<Book> sortedBooks = this->bookService.sortByTitle(reversed);

		cout << " -------- Cartile sortate in functie de titlu sunt: --------\n";
		this->printBooklist(sortedBooks);
	}
	else if (sortType == 2) {
		char criteria = 'c';
		bool reversed = false;

		cout << " -------- Introduceti criteriul de sortare: --------\n";
		cout << "c - sortare crescatoare\n";
		cout << "d - sortare descrescatoare\n";

		cout << "Criteriu sortare -> "; cin >> criteria;

		if (criteria != 'c' && criteria != 'd') {
			cout << "Criteriu de sortare invalid, nu se poate efectua sortarea!\n";
			return;
		}

		if (criteria == 'c')
			reversed = false;
		else if (criteria == 'd')
			reversed = true;

		vector<Book> sortedBooks = this->bookService.sortByAuthor(reversed);

		cout << " -------- Cartile sortate in functie de autor sunt: --------\n";
		this->printBooklist(sortedBooks);
	}
	else if (sortType == 3) {
		char criteria = 'c';
		bool reversed = false;

		cout << " -------- Introduceti criteriul de sortare: --------\n";
		cout << "c - sortare crescatoare\n";
		cout << "d - sortare descrescatoare\n";

		cout << "Criteriu sortare -> "; cin >> criteria;

		if (criteria != 'c' && criteria != 'd') {
			cout << "Criteriu de sortare invalid, nu se poate efectua sortarea!\n";
			return;
		}

		if (criteria == 'c')
			reversed = false;
		else if (criteria == 'd')
			reversed = true;

		vector<Book> sortedBooks = this->bookService.sortByReleaseYearAndGenre(reversed);

		cout << " -------- Cartile sortate in functie de an aparitie si gen sunt: --------\n";
		this->printBooklist(sortedBooks);

	}
	else {
		cout << "Tip sortare invalid, nu s-a putut efectua sortarea!\n";;
	}
}

void ConsoleUI::addToWishlistUI() {
	string searchedTitle;
	cout << " -------- Adaugare carte in wishlist --------\n";
	cout << "Titlu carte cautata -> "; searchedTitle = this->readBookTitle();

	const vector<Book>& matchedBooks = this->bookService.matchWishlistBooks(searchedTitle);
	if (matchedBooks.size() == 0) {
		cout << "Nu au fost gasite carti cu titlul dat!\n";
		return;
	}
	else {
		cout << " -------- Carti disponibile cu titlul dat: --------\n";
		this->printBooklist(matchedBooks);
	}

	string searchedISBN;
	cout << "ISBN carte dorita -> "; searchedISBN = this->readBookISBN();

	this->bookService.addToWishlist(searchedISBN);
	cout << " -------- Carte adaugata in wishlist cu succes! --------\n";

	cout << " --- Numar de carti in wishlist-ul curent -> " << this->bookService.getWishlistSize()<< " ---\n";

}

void ConsoleUI::clearWishlistUI() {
	this->bookService.emptyWishlist();
	cout << " -------- Wishlist golit cu succes! --------\n";
}

void ConsoleUI::addRandomToWishlistUI() {
	int howMany = -1;
	cout << " -------- Generare wishlist random --------\n";

	cout << "Numar carti de adaugat -> "; howMany = this->readBookId();

	if (howMany <= 0) {
		cout << "Numar carti invalid, introduceti un numar valid!\n";
		return;
	}
	else {
		this->bookService.addRandomToWishlist(howMany);
		cout << " -------- Wishlist cu " << howMany << " carti generat cu succes! --------\n";
	}

	cout << " --- Numar de carti in wishlist-ul curent -> " << this->bookService.getWishlistSize() << " ---\n";
}

void ConsoleUI::exportWishlistUI() {
	string fileName;
	cout << " -------- Export wishlist in fisier dat --------\n";
	cout << "Introduceti numele fisierului de export: "; cin >> fileName;
	this->bookService.exportWishlist(fileName);
	cout << " -------- Export efectuat cu succes! --------\n";

	cout << " --- Numar de carti in wishlist-ul curent -> " << this->bookService.getWishlistSize() << " ---\n";
}

void ConsoleUI::undoUI() {
	this->bookService.undo();

	cout << " -------- Undo efectuat cu succes! --------\n";
}


void ConsoleUI::displayBookReportUI() {
	const unordered_map<string, BookReportDTO> bookReport = this->bookService.getBookReport();

	cout << " -------- Afisare statistica carti dupa gen --------\n";

	if (bookReport.empty()) {
		cout << "Nu exista carti adaugate in biblioteca!\n";
		return;
	}

	for (const std::pair<string, BookReportDTO>& stat : bookReport) {
		cout << "Tipul: " << stat.first << " -> " << stat.second.getCount() << "\n";
	}

	cout << " ---------------------------------------------------\n";
}

void ConsoleUI::displayWishlistUI() {
	const vector<Book>& wishlist = this->bookService.getWishlistBooks();



	if (wishlist.size() == 0) {
		cout << "Nu exista carti adaugate in wishlist!\n";
		return;
	}
	else {
		this->printBooklist(wishlist);
	}
}

void ConsoleUI::run() {
	this->printMenu();
	bool running = true;
	string cmd;
	while (running) {
		cout << "Introduceti comanda: ";
		cin >> cmd;
		auto exists = this->commands.find(cmd);
		if (cmd == "exit") {
			cout << "Shutting down...\n";
			running = false;
			return;
		}
		if (exists != this->commands.end()) {
			try {
				(this->*commands.at(cmd))();
			}
			catch(ValidationException& ve) {
				cout << " -------- Eroare de validare --------\n";
				cout << ve.get_error_messages();
				cout << " ------------------------------------\n";
			}
			catch (RepoException& re) {
				cout << " -------- Eroare de repository --------\n";
				cout << re.get_error_message();
				cout << " --------------------------------------\n";
			}
			catch (UndoException& ue) {
				cout << " ----------- Eroare de undo -----------\n";
				cout << ue.get_error_message();
				cout << " --------------------------------------\n";
			}
			catch (InvalidInputException& ie) {
				cout << " -------- Eroare de input --------\n";
				cout << string(ie);
				cout << " ---------------------------------\n";
			}
		}
		else {
			cout << "Comanda invalida!\n";
		}
	}
}