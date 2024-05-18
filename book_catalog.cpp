#include "book_catalog.h"

void writeBooksToFile(const std::string& filename, const std::vector<Book>& books) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file " << filename << " for writing" << std::endl;
        return;
    }
    for (const auto& book : books) {
        outFile << book.id << " " << book.author << " " << book.title << " " << book.pages << std::endl;
    }
    outFile.close();
}

void readBooksFromFile(const std::string& filename, std::vector<Book>& books) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file " << filename << " for reading" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book.id >> book.author >> book.title >> book.pages) {
        books.push_back(book);
    }
    inFile.close();
}

void addBook(std::vector<Book>& books) {
    Book newBook;
    std::cout << "Enter ID, author, title, and number of pages: ";
    std::cin >> newBook.id >> newBook.author >> newBook.title >> newBook.pages;
    books.push_back(newBook);
}

void viewBooks(const std::vector<Book>& books) {
    for (const auto& book : books) {
        std::cout << book.id << " " << book.author << " " << book.title << " " << book.pages << std::endl;
    }
}

void deleteBook(std::vector<Book>& books, const std::string& id) {
    books.erase(std::remove_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; }), books.end());
}

void searchBook(const std::vector<Book>& books, const std::string& title) {
    auto it = std::find_if(books.begin(), books.end(), [&title](const Book& book) { return book.title == title; });
    if (it != books.end()) {
        std::cout << it->id << " " << it->author << " " << it->title << " " << it->pages << std::endl;
    }
    else {
        std::cout << "Book not found." << std::endl;
    }
}

void editBook(std::vector<Book>& books, const std::string& id) {
    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        Book updatedBook;
        std::cout << "Enter new data: ";
        std::cin >> updatedBook.id >> updatedBook.author >> updatedBook.title >> updatedBook.pages;
        *it = updatedBook;
    }
    else {
        std::cout << "Book with ID " << id << " not found." << std::endl;
    }
}