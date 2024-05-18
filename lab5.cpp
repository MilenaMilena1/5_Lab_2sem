#include <iostream>
#include <sstream>
#include "book_catalog.h"
#include "matrix_operations.h"

int main() {
    std::vector<Book> books;
    std::string booksFilename = "books.txt";
    readBooksFromFile(booksFilename, books);

    std::vector<Matrix> matrices = {
        {{{1, 2, 3}, {4, 5, 6}}},
        {{{7, 8}, {9, 10}, {11, 12}}}
    };
    std::string matricesFilename = "matrices.txt";

    writeMatrixToFile(matricesFilename, matrices);
    std::vector<Matrix> readMatrices = readMatricesFromFile(matricesFilename);
    for (const auto& matrix : readMatrices) {
        std::cout << "\nMatrix:" << std::endl;
        for (const auto& row : matrix.data) {
            for (int value : row) {
                std::cout << value << ' ';
            }
            std::cout << std::endl;
        }
    }

    int choice;
    std::string input;
    do {
        std::cout << "\nMenu:\n"
            << "1. Add a book\n"
            << "2. View all books\n"
            << "3. Delete a book\n"
            << "4. Search for a book\n"
            << "5. Edit a book\n"
            << "6. Exit\n"
            << "Select: ";
        std::cin >> input;
        std::istringstream iss(input);
        if (!(iss >> choice)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            addBook(books);
            writeBooksToFile(booksFilename, books);
            break;
        case 2:
            viewBooks(books);
            break;
        case 3: {
            std::string id;
            std::cout << "Enter the book ID to delete: ";
            std::cin >> id;
            deleteBook(books, id);
            writeBooksToFile(booksFilename, books);
            break;
        }
        case 4: {
            std::string title;
            std::cout << "Enter the title of the book to search: ";
            std::cin >> title;
            searchBook(books, title);
            break;
        }
        case 5: {
            std::string id;
            std::cout << "Enter the book ID to edit: ";
            std::cin >> id;
            editBook(books, id);
            writeBooksToFile(booksFilename, books);
            break;
        }
        case 6:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
            break;
        }
    } while (choice != 6);

    return 0;
}
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
#include "matrix_operations.h"

void writeMatrixToFile(const std::string& filename, const std::vector<Matrix>& matrices) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return;
    }

    for (const auto& matrix : matrices) {
        for (const auto& row : matrix.data) {
            for (int value : row) {
                file << value << ' ';
            }
            file << '\n';
        }
        file << '\n';
    }

    file.close();
}

std::vector<Matrix> readMatricesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return {};
    }

    std::vector<Matrix> matrices;
    std::vector<std::vector<int>> matrixData;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            if (!matrixData.empty()) {
                matrices.push_back({ matrixData });
                matrixData.clear();
            }
        }
        else {
            std::istringstream iss(line);
            std::vector<int> row;
            int value;
            while (iss >> value) {
                row.push_back(value);
            }
            matrixData.push_back(row);
        }
    }

    if (!matrixData.empty()) {
        matrices.push_back({ matrixData });
    }

    file.close();
    return matrices;
}