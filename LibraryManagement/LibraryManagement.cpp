#include <iostream>
#include "Library.h"
#include <algorithm>
#include <fstream>
#include <cstdio>

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
			int index1, index2, yearint;
			std::string sentence, title, author, year;
			//book info
			std::cout << "Please give the book informations(Title/Author/Year-Seperated with space): ";
			std::cin.ignore();
			std::getline(std::cin, sentence);

			std::cout << std::endl;

			std::string::difference_type countOfSpace = std::count(sentence.begin(), sentence.end(), ' ');

			if(sentence.empty()){
				std::cout << "Please give valid an input";
			}
			else{
				if(countOfSpace == 2){
					std::vector<Book> tempBookVec;
					//seperates string
					seperateString(sentence, &title, &author, &year);
					yearint = std::stoi(year);
					//create object
					Book tempBook;
					tempBook.setTitle(title);
					tempBook.setAuthor(author);
					tempBook.setYear(yearint);
					// add to library
					tempBookVec.push_back(tempBook);
					writeBooksToFile(tempBookVec, "allBooks.txt");
					kutuphane.addBook(tempBook);
				}
				else {
					std::cout << std::endl;
					std::cerr << "PLEASE GIVE VALID BOOK INFOS" << std::endl << std::endl;
				}
			}
		}
		else if (choice == "3")
		{
			std::vector<Book> tempforDelete;
			std::string del;
			std::cout << "\t  Choose title or author to remove book!" << std::endl << std::endl;
			std::cout << "\t= ";
			std::cin >> del;

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
			deleteBookFromFile(*it, "allBooks.txt");
			kutuphane.removeBook(del);
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
			outFile << book.getTitle() << " " << book.getAuthor() << " " << book.getPublishYear() << std::endl;
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
		std::string title, author;
		int year;
		while (inFile >> title >> author >> year) {
			books.emplace_back(title, author, year);
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
				outFile << book.getTitle() << " " << book.getAuthor() << " " << book.getPublishYear() << std::endl;
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