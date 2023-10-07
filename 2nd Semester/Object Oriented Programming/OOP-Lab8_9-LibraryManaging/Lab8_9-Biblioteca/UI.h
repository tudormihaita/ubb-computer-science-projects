#pragma once
#include "Service.h"
#include "Exceptions.h"
#include <unordered_map>
#include <functional>
#include <limits>

using std::unordered_map;

//typedef void (ConsoleUI::*UIMethod)();

class ConsoleUI {
private:
	Library& bookService;
	
	unordered_map<string, void(ConsoleUI::*)()> commands = {
		{"help", &ConsoleUI::helpCommandsUI},
		{"display_books", &ConsoleUI::displayBooksUI},
		{"add_book",&ConsoleUI::addBookUI},
		{"find_book", &ConsoleUI::findBookUI},
		{"delete_book", &ConsoleUI::deleteBookUI},
		{"update_book", &ConsoleUI::updateBookUI},
		{"filter_books", &ConsoleUI::filterBooksUI},
		{"sort_books", &ConsoleUI::sortBooksUI},
		{"add_to_wishlist", &ConsoleUI::addToWishlistUI},
		{"clear_wishlist", &ConsoleUI::clearWishlistUI},
		{"add_random_to_wishlist", &ConsoleUI::addRandomToWishlistUI},
		{"display_wishlist", &ConsoleUI::displayWishlistUI},
		{"export_wishlist", &ConsoleUI::exportWishlistUI},
		{"display_report", &ConsoleUI::displayBookReportUI},
		{"populate_library", &ConsoleUI::populateLibraryUI},
		{"undo", &ConsoleUI::undoUI},
		{"clear", &ConsoleUI::clearScreenUI}
	};

	const int readBookId();

	string readBookISBN();

	string readBookTitle();

	string readBookAuthor();

	string readBookPublisher();

	string readBookGenre();

	const int readBookReleaseYear();

	void populateLibraryUI();

	void clearScreenUI() noexcept;

public:

	ConsoleUI(Library& service) : bookService { service } {};

	ConsoleUI(const ConsoleUI& other) = delete;

	void printBooklist(const vector<Book>& booklist);

	void printMenu();
	  
	void helpCommandsUI();

	void displayBooksUI();

	void addBookUI();

	void findBookUI();

	void deleteBookUI();

	void updateBookUI();

	void filterBooksUI();

	void sortBooksUI();
	
	void addToWishlistUI();

	void clearWishlistUI();

	void addRandomToWishlistUI();

	void exportWishlistUI();

	void undoUI();

	void displayBookReportUI();

	void displayWishlistUI();

	void run();
};
