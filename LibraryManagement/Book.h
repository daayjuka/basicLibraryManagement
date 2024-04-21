#pragma once

#include <iostream>
#include <string>

class Book
{
public:
	//CONSTURACTERS
	Book()
		:title(""), author(""), publishYear(-1) {}
	Book(std::string title, std::string author,int publishYear)
		:title(title), author(author), publishYear(publishYear) {}


	//SET-GET FUNCTIONS
	void setYear(int Year);
	void setAuthor(std::string Author);
	void setTitle(std::string Title);

	std::string getTitle();
	std::string getAuthor();
	int getPublishYear();

	//DESTRUCTER
	//~Book();

private:
	std::string title;
	std::string author;
	int publishYear;
};

