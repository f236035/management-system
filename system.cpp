#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool isIssued;

public:
    Book(int bookId, string bookTitle, string bookAuthor) 
        : id(bookId), title(bookTitle), author(bookAuthor), isIssued(false) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsIssued() const { return isIssued; }

    void issueBook() {
        if (!isIssued) {
            isIssued = true;
            cout << "Book \"" << title << "\" has been issued." << endl;
        } else {
            cout << "Book \"" << title << "\" is already issued." << endl;
        }
    }

    void returnBook() {
        if (isIssued) {
            isIssued = false;
            cout << "Book \"" << title << "\" has been returned." << endl;
        } else {
            cout << "Book \"" << title << "\" was not issued." << endl;
        }
    }

    void display() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author;
        cout << (isIssued ? " [Issued]" : " [Available]") << endl;
    }
};

class Member {
private:
    int memberId;
    string name;
    int issuedBooksCount;

public:
    Member(int id, string memberName) : memberId(id), name(memberName), issuedBooksCount(0) {}

    int getMemberId() const { return memberId; }
    string getName() const { return name; }

    void issueBook() {
        issuedBooksCount++;
    }

    void returnBook() {
        if (issuedBooksCount > 0) {
            issuedBooksCount--;
        }
    }

    void display() const {
        cout << "Member ID: " << memberId << ", Name: " << name << ", Issued Books: " << issuedBooksCount << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book \"" << book.getTitle() << "\" added to the library." << endl;
    }

    void addMember(const Member& member) {
        members.push_back(member);
        cout << "Member \"" << member.getName() << "\" added to the library." << endl;
    }

    void issueBook(int bookId, int memberId) {
        for (auto& book : books) {
            if (book.getId() == bookId) {
                if (book.getIsIssued()) {
                    cout << "Book is already issued." << endl;
                    return;
                }

                for (auto& member : members) {
                    if (member.getMemberId() == memberId) {
                        book.issueBook();
                        member.issueBook();
                        return;
                    }
                }
                cout << "Member not found." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void returnBook(int bookId, int memberId) {
        for (auto& book : books) {
            if (book.getId() == bookId) {
                for (auto& member : members) {
                    if (member.getMemberId() == memberId) {
                        book.returnBook();
                        member.returnBook();
                        return;
                    }
                }
                cout << "Member not found." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void displayBooks() const {
        cout << "Books in the Library:" << endl;
        for (const auto& book : books) {
            book.display();
        }
    }

    void displayMembers() const {
        cout << "Members of the Library:" << endl;
        for (const auto& member : members) {
            member.display();
        }
    }
};

int main() {
    Library library;

    // Add Books
    library.addBook(Book(1, "C++ Programming", "Bjarne Stroustrup"));
    library.addBook(Book(2, "Effective Java", "Joshua Bloch"));
    library.addBook(Book(3, "Design Patterns", "Erich Gamma"));

    // Add Members
    library.addMember(Member(101, "John Doe"));
    library.addMember(Member(102, "Alice Smith"));

    // Display Books and Members
    library.displayBooks();
    library.displayMembers();

    // Issue a book to a member
    library.issueBook(1, 101);

    // Try to issue the same book again
    library.issueBook(1, 102);

    // Return the book
    library.returnBook(1, 101);

    // Display final state
    library.displayBooks();
    library.displayMembers();

    return 0;
}

