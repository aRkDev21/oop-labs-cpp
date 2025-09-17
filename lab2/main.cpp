#include <iostream>
#include <map>
#include <vector>
#include <string>

struct Book {
    int id;
    std::string title;
    std::vector<double> prices;

    void display() const {
        std::cout << id << " " << title << " ";
        for (const double &price : prices) std::cout << price << " ";
        std::cout << std::endl;
    }
};


// vector functions
void displayAllBooks(const std::vector<Book>&);
void findBookByPrice(const std::vector<Book>&, double);

// map functions
Book* findBookById(std::map<int, Book>&, int);
void displayAllBooks(const std::map<int, Book>&);
Book* searchBookByRange(std::map<int, Book>&, double, double);

// menu functions
void updateBookInfo(std::vector<Book>&, std::map<int, Book>&, int);
Book _createNewBook();
void _updateBook(Book&);
double calculateAvgPrice(const Book&);
void menu(std::vector<Book>&, std::map<int, Book>&);

int main() {
    std::vector<Book> books;
    std::map<int, Book> lib;

    books.push_back({1, "Kolobok", {11, 10.5, 12, 11.3}});
    books.push_back({2, "Popa", {1.1, 1.5, 1.2, 1.1}});
    books.push_back({3, "Pisya", {21, 20.5, 26, 21.3}});
    books.push_back({4, "Kaka", {101, 105, 120, 113}});

    for (auto &book : books) {
        lib[book.id] = book;
    }

    menu(books, lib);

    return 0;
}

void menu(std::vector<Book>& books, std::map<int, Book>& lib) {
    int choice;
    do {
        std::cout << std::endl << "--- Menu ---" << std::endl;
        std::cout << "1. Add new book" << std::endl;
        std::cout << "2. Display all books" << std::endl;
        std::cout << "3. Calculate average price of a book" << std::endl;
        std::cout << "4. Find book by price" << std::endl;
        std::cout << "5. Update book info by ID" << std::endl;
        std::cout << "6. Search book by price range" << std::endl;
        std::cout << "7. Find book by id" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose option: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            Book newBook = _createNewBook();
            books.push_back(newBook);
            lib[newBook.id] = newBook;
            break;
        }
        case 2:
            std::cout << "--- Vector of Books ---" << std::endl;
            displayAllBooks(books);
            std::cout << "--- Map of Books ---" << std::endl;
            displayAllBooks(lib);
            break;
        case 3: {
            int id;
            std::cout << "Enter book ID: ";
            std::cin >> id;
            Book* b = findBookById(lib, id);
            if (b) {
                std::cout << "Average price: " << calculateAvgPrice(*b) << std::endl;
            } else {
                std::cout << "Book with id " << id << " not found!" << std::endl;
            }
            break;
        }
        case 4: {
            double price;
            std::cout << "Enter price to search: ";
            std::cin >> price;
            findBookByPrice(books, price);
            break;
        }
        case 5: {
            int id;
            std::cout << "Enter book ID to update: ";
            std::cin >> id;
            updateBookInfo(books, lib, id);
            break;
        }
        case 6: {
            double minP, maxP;
            std::cout << "Enter min price: ";
            std::cin >> minP;
            std::cout << "Enter max price: ";
            std::cin >> maxP;
            Book* b = searchBookByRange(lib, minP, maxP);
            if (b) b->display();
            else std::cout << "No books in this price range" << std::endl;
            break;
        }
        case 7: {
            int id;
            std::cout << "Enter book ID: ";
            std::cin >> id;
            Book* b = findBookById(lib, id);
            if (b) {
                b->display();
            } else {
                std::cout << "Book with id " << id << " not found!" << std::endl;
            }
            break;
        }
        case 0:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
        }
    } while (choice != 0);
}

Book _createNewBook() {
    Book newBook;

    std::cout << "Enter id of new book: "; 
    std::cin >> newBook.id;

    std::cout << "Title: ";
    std::cin.ignore(32767, '\n');
    std::getline(std::cin, newBook.title);

    std::cout << "Prices (<=0 to stop): ";
    double temp;
    while (std::cin >> temp && temp > 0) {
        newBook.prices.push_back(temp);
    }

    if (!std::cin) std::cin.clear();
    std::cin.ignore(32767, '\n');

    return newBook;
}

void _updateBook(Book& oldBook) {
    std::cout << "\tUpdate menu" << std::endl;
    std::cout << "1. Change title" << std::endl;
    std::cout << "2. Add new price" << std::endl;

    int choice; 
    std::cout << "Choose option: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        std::cout << "New title: ";
        std::cin.ignore(32767, '\n');
        std::getline(std::cin, oldBook.title);
        break;
    case 2: {
        std::cout << "New price: ";
        double temp;
        std::cin >> temp;
        oldBook.prices.push_back(temp);
        break;
    }
    default:
        std::cout << "Invalid option!" << std::endl;
        break;
    }
}

void displayAllBooks(const std::vector<Book>& books) {
    if (books.empty()) {
        std::cout << "vector<Book> is empty" << std::endl;
        return;
    }
    for (const auto& book : books) book.display();
}

double calculateAvgPrice(const Book& book) {
    if (book.prices.empty()) {
        std::cout << "No prices available" << std::endl;
        return 0;
    }
    double sum = 0;
    for (const double& price : book.prices) sum += price;
    return sum / book.prices.size();
}

void findBookByPrice(const std::vector<Book>& books, double target_price) {
    bool found = false;
    for (const auto& book : books) {
        for (double price : book.prices) {
            if (price == target_price) {
                book.display();
                found = true;
                break;
            }
        }
    }
    if (!found) std::cout << "No book with price: " << target_price << std::endl;
}

Book* findBookById(std::map<int, Book>& lib, int id) {
    auto it = lib.find(id);
    if (it != lib.end()) return &it->second;
    return nullptr;
}

void updateBookInfo(std::vector<Book>& books, std::map<int, Book>& lib, int id) {
    Book* curBook = findBookById(lib, id);
    if (!curBook) {
        std::cout << "Book with id " << id << " not found!" << std::endl;
        return;
    }
    _updateBook(*curBook);

    for (auto& b : books) {
        if (b.id == id) {
            b = *curBook;
            break;
        }
    }
}

Book* searchBookByRange(std::map<int, Book>& lib, double minPrice, double maxPrice) { 
    for (auto& pair : lib) {
        for (auto price : pair.second.prices) {
            if (price >= minPrice && price <= maxPrice) {
                return &pair.second;
            }
        }
    }
    return nullptr;
}

void displayAllBooks(const std::map<int, Book>& lib) {
    if (lib.empty()) {
        std::cout << "map<Book> is empty" << std::endl;
        return;
    }
    for (const auto& pair : lib) {
        pair.second.display();
    }
}
