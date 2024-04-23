#include "Library.h"

void Library::removeBook(std::string titleOrAuthor)
{
    auto it = allBooks.begin();
    while (it != allBooks.end()) {
        if (it->getAuthor() == titleOrAuthor || it->getTitle() == titleOrAuthor) {
            it = allBooks.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Library::displayAllBooks()
{
    if (allBooks.empty())
        std::cout << "\nLibrary is empty!" << std::endl;
    else{
        int count = 1;
        for (Book obj : allBooks) {
            std::cout << std::endl;
            std::cout << "--" << count << "." << "Book--" << std::endl;
            std::cout << "Title:  " << obj.getTitle() << std::endl;
            std::cout << "Author:  " << obj.getAuthor() << std::endl;
            std::cout << "Publish Year:  " << obj.getPublishYear() << std::endl << std::endl;
            count++;
        }
    }
}

