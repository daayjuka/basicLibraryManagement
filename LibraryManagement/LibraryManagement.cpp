#include <iostream>
#include "Library.h"
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <limits>

void seperateString(std::string sentence, std::string* title, std::string* author, std::string* year);

void writeBooksToFile(std::vector<Book>& books, const std::string& filename);

std::vector<Book> readBooksFromFile(const std::string& filename);

void deleteBookFromFile(Book& target, const std::string& filename);

int main()
{
	std::vector<Book> dataBooks;
	Library kutuphane;

	dataBooks = readBooksFromFile("allBooks.txt");

	if(dataBooks.empty()){
	}
	else {
		for (auto& book : dataBooks) {
			kutuphane.addBook(book);
		}
	}


	std::cout << "Personal Library" << std::endl;
	std::cout << "  1 - Display All Books" << std::endl;
	std::cout << "  2 - Add Book" << std::endl;
	std::cout << "  3 - Remove Book" << std::endl << std::endl;
	std::cout << "  For quitting [exit]" << std::endl << std::endl;

	while(true){
		std::string choice;
		std::cout << "Choice: ";
		std::cin >> choice;

		if (choice == "1") {
			kutuphane.displayAllBooks();
		}
		else if (choice == "2")
		{
			//variables
			//int index1, index2;
			int year;
			std::string title, author;
			//book info
			std::cout << "Please give the book title: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			std::cout << "Please give the book author: ";
			std::getline(std::cin, author);
			while(true){
				std::cout << "Please give the book publish year: ";
				std::cin >> year;
				
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input! Year must be number. Please give valid input" << std::endl;
				}
				else {
					break;
				}

			}

			std::cout << std::endl;

			//std::string::difference_type countOfSpace = std::count(sentence.begin(), sentence.end(), ' ');
			//seperates string
			//seperateString(sentence, &title, &author, &year);
			//yearint = std::stoi(year);
			//create object
			Book tempBook;
			tempBook.setTitle(title);
			tempBook.setAuthor(author);
			tempBook.setYear(year);
			// add to library
			std::vector<Book> tempBookVec;
			tempBookVec.push_back(tempBook);
			writeBooksToFile(tempBookVec, "allBooks.txt");
			kutuphane.addBook(tempBook);
		
		
		}
		else if (choice == "3")
		{
			std::vector<Book> tempforDelete;
			std::string del;
			std::cout << "\t  Choose title or author to remove book!" << std::endl << std::endl;
			std::cout << "  => ";
			std::cin.ignore();
			std::getline(std::cin , del);

			tempforDelete = readBooksFromFile("allBooks.txt");

			auto it = tempforDelete.begin();
			while (it != tempforDelete.end()) {
				if (it->getTitle() == del || it->getAuthor() == del) {
					break;
				}
				else
				{
					it++;
				}
			}
			if (it == tempforDelete.end()) {
				std::cout << std::endl;
				std::cout << "There is not any author or title in this library" << std::endl << std::endl;
			}
			else{
			deleteBookFromFile(*it, "allBooks.txt");
			kutuphane.removeBook(del);
			}

		}
		else if (choice == "EXIT" || choice == "Exit" || choice == "exit")
		{
			std::cout << std::endl;
			std::cout << "You exit the program!" << std::endl;
			exit(0);
		}
		else {
			std::cout << std::endl;
			std::cout << "GIVE AN VALID INPUT" << std::endl << std::endl;
		}
	}
}


void seperateString(std::string sentence, std::string* title, std::string* author, std::string* year) {
	int index1, index2;
	index1 = sentence.find(" ");
	*title = sentence.substr(0, index1);
	sentence.replace(index1, 1, "£");
	index2 = sentence.find(" ");
	*author = sentence.substr(index1 + 1, (index2 - index1));
	sentence.replace(index2, 1, "£");
	*year = sentence.substr(index2 + 1, (sentence.length() - index2));
}

void writeBooksToFile(std::vector<Book>& books, const std::string& filename) {
	std::ofstream outFile(filename, std::ios_base::app);
	if (outFile.is_open()) {
		for (auto& book : books) {
			outFile << book.getTitle() << "_" << book.getAuthor() << "_" << book.getPublishYear() << std::endl;
		}
		outFile.close();
	}
	else {
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
}

std::vector<Book> readBooksFromFile(const std::string& filename) {
	std::vector<Book> books;
	std::ifstream inFile(filename);
	if (inFile.is_open()) {
		std::string line;
		while (std::getline(inFile,line)) {
			std::istringstream iss(line);
			std::string title_str, author_str, year_str;
			if (std::getline(iss, title_str, '_') && std::getline(iss, author_str, '_') && std::getline(iss, year_str, '_')) {
				int year = std::stoi(year_str);
				books.emplace_back(title_str, author_str, year);
			}
		}
		inFile.close();
	}
	else {
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
	return books;
}

void deleteBookFromFile(Book& target, const std::string& filename) {
	std::vector<Book> books = readBooksFromFile(filename);

	std::ofstream outFile(filename + ".tmp");
	if (outFile.is_open()) {

		for (auto& book : books) {
			if (!(book.getTitle() == target.getTitle() && book.getAuthor() == target.getAuthor() && book.getPublishYear() == target.getPublishYear())) {
				outFile << book.getTitle() << "_" << book.getAuthor() << "_" << book.getPublishYear() << std::endl;
			}
		}
		outFile.close();

		remove("allBooks.txt");

		if (std::rename((filename + ".tmp").c_str(), filename.c_str()) != 0) {
			std::cerr << "Error replacing file: " << filename << std::endl;
		}
	}
	else {
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
}