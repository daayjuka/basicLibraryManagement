#pragma once

#include "Book.h"
#include <vector>

class Library
{
public:

	Book obj;

	void addBook(Book obj) {
		allBooks.push_back(obj);
	}

	void removeBook(std::string titleOrAuthor);

	void displayAllBooks();


private:
	std::vector<Book> allBooks;
};



