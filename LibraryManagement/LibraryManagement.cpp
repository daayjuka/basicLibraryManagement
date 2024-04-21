#include <iostream>
#include "Library.h"


int main()
{
	bool app = true;

	Book book1;
	book1.setAuthor("Author1");
	book1.setTitle("Title1");
	book1.setYear(1915);
	Book book2("Title2", "Author2", 1918);
	Library kutuphane;


	std::cout << "Personal Library" << std::endl;
	std::cout << "  1 - Display All Books" << std::endl;
	std::cout << "  2 - Add Book" << std::endl;
	std::cout << "  3 - Remove Book" << std::endl << std::endl;


	while(true){

		int choice;
		std::cout << "Choice: ";
		std::cin >> choice;

		if (choice == 1) {
			kutuphane.displayAllBooks();
		}
		else if (choice == 2)
		{
			//variables
			int index1, index2, yearint;
			std::string sentence, title, author, year;
			//book info
			std::cout << "Please give the book informations(Title/Author/Year-Seperated with space): ";
			std::cin.ignore();
			std::getline(std::cin, sentence);
			if(sentence.empty()){
				std::cout << "give an input";
			}else{
			//seperate the string
			index1 = sentence.find(" ");
			title = sentence.substr(0, index1);
			sentence.replace(index1, 1, "!");
			index2 = sentence.find(" ");
			author = sentence.substr(index1+1, (index2 - index1));
			sentence.replace(index2, 1, "£");
			year = sentence.substr(index2+1, (sentence.length() - index2));
			yearint = std::stoi(year);
			//create object
			Book tempBook;
			tempBook.setTitle(title);
			tempBook.setAuthor(author);
			tempBook.setYear(yearint);
			// add to library
			kutuphane.addBook(tempBook);
			}
		}
		else if (choice == 3)
		{
			std::string del;
			std::cout << "\t  Choose title or author to remove book!" << std::endl << std::endl;
			std::cin >> del;
			kutuphane.removeBook(del);
		}
	}
}
