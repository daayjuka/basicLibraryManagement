#include "Book.h"

/*
Book::~Book()
{
	std::cout << "Object is destroyed!" << std::endl;
}
*/
void Book::setYear(int Year)
{
	publishYear = Year;
}

void Book::setAuthor(std::string Author)
{
	author = Author;
}

void Book::setTitle(std::string Title)
{
	title = Title;
}

std::string Book::getTitle()
{
	return title;
}

std::string Book::getAuthor()
{
	return author;
}

int Book::getPublishYear()
{
	return publishYear;
}
