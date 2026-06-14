#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

// ---------------- Book Class ----------------
class Book {
public:
    int bookID;
    char title[50];
    char author[50];
    int isIssued;       // 0 = available, 1 = issued
    int issuedToID;     // member ID who has the book (0 if none)

    void getData() {
        cout << "Enter Book ID: ";
        cin >> bookID;
        cin.ignore();
        cout << "Enter Title: ";
        cin.getline(title, 50);
        cout << "Enter Author: ";
        cin.getline(author, 50);
        isIssued = 0;
        issuedToID = 0;
    }

    void showData() {
        cout << "Book ID   : " << bookID << "\n";
        cout << "Title     : " << title << "\n";
        cout << "Author    : " << author << "\n";
        cout << "Status    : " << (isIssued ? "Issued" : "Available") << "\n";
        if (isIssued)
            cout << "Issued To : Member ID " << issuedToID << "\n";
        cout << "------------------------\n";
    }

    int getBookID() { return bookID; }
};

// ---------------- Member Class ----------------
class Member {
public:
    int memberID;
    char name[50];

    void getData() {
        cout << "Enter Member ID: ";
        cin >> memberID;
        cin.ignore();
        cout << "Enter Member Name: ";
        cin.getline(name, 50);
    }

    void showData() {
        cout << "Member ID : " << memberID << "\n";
        cout << "Name      : " << name << "\n";
        cout << "------------------------\n";
    }

    int getMemberID() { return memberID; }
};

// ---------------- Add Book ----------------
void addBook() {
    Book b;
    b.getData();

    fstream file;
    file.open("books.dat", ios::binary | ios::out | ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file.write((char*)&b, sizeof(Book));
    file.close();

    cout << "Book added successfully!\n";
}

// ---------------- Add Member ----------------
void addMember() {
    Member m;
    m.getData();

    fstream file;
    file.open("members.dat", ios::binary | ios::out | ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file.write((char*)&m, sizeof(Member));
    file.close();

    cout << "Member added successfully!\n";
}

// ---------------- Display All Books ----------------
void displayAllBooks() {
    Book b;
    fstream file;
    file.open("books.dat", ios::binary | ios::in);

    if (!file) {
        cout << "Error opening file or no books found!\n";
        return;
    }

    cout << "\n----- All Books -----\n";
    bool found = false;

    while (file.read((char*)&b, sizeof(Book))) {
        b.showData();
        found = true;
    }

    if (!found)
        cout << "No books found.\n";

    file.close();
}

// ---------------- Display All Members ----------------
void displayAllMembers() {
    Member m;
    fstream file;
    file.open("members.dat", ios::binary | ios::in);

    if (!file) {
        cout << "Error opening file or no members found!\n";
        return;
    }

    cout << "\n----- All Members -----\n";
    bool found = false;

    while (file.read((char*)&m, sizeof(Member))) {
        m.showData();
        found = true;
    }

    if (!found)
        cout << "No members found.\n";

    file.close();
}

// ---------------- Issue Book ----------------
void issueBook() {
    int bookID, memberID;
    cout << "Enter Book ID to issue: ";
    cin >> bookID;
    cout << "Enter Member ID: ";
    cin >> memberID;

    Book b;
    fstream file;
    file.open("books.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    bool found = false;

    while (file.read((char*)&b, sizeof(Book))) {
        if (b.getBookID() == bookID) {
            found = true;

            if (b.isIssued) {
                cout << "Book is already issued to Member ID "
                     << b.issuedToID << "\n";
                break;
            }

            b.isIssued = 1;
            b.issuedToID = memberID;

            int pos = -1 * (int)sizeof(Book);
            file.seekp(pos, ios::cur);
            file.write((char*)&b, sizeof(Book));

            cout << "Book issued successfully to Member ID "
                 << memberID << "\n";
            break;
        }
    }

    if (!found)
        cout << "Book with ID " << bookID << " not found.\n";

    file.close();
}

// ---------------- Return Book ----------------
void returnBook() {
    int bookID;
    cout << "Enter Book ID to return: ";
    cin >> bookID;

    Book b;
    fstream file;
    file.open("books.dat", ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    bool found = false;

    while (file.read((char*)&b, sizeof(Book))) {
        if (b.getBookID() == bookID) {
            found = true;

            if (!b.isIssued) {
                cout << "This book was not issued.\n";
                break;
            }

            cout << "Book returned from Member ID "
                 << b.issuedToID << "\n";

            b.isIssued = 0;
            b.issuedToID = 0;

            int pos = -1 * (int)sizeof(Book);
            file.seekp(pos, ios::cur);
            file.write((char*)&b, sizeof(Book));

            cout << "Book returned successfully!\n";
            break;
        }
    }

    if (!found)
        cout << "Book with ID " << bookID << " not found.\n";

    file.close();
}

// ---------------- Search by Title ----------------
void searchByTitle() {
    char searchTitle[50];
    cout << "Enter title to search: ";
    cin.ignore();
    cin.getline(searchTitle, 50);

    Book b;
    fstream file;
    file.open("books.dat", ios::binary | ios::in);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    bool found = false;
    cout << "\n----- Search Results -----\n";

    while (file.read((char*)&b, sizeof(Book))) {
        if (strstr(b.title, searchTitle) != NULL) {
            b.showData();
            found = true;
        }
    }

    if (!found)
        cout << "No books found with that title.\n";

    file.close();
}

// ---------------- Search by Author ----------------
void searchByAuthor() {
    char searchAuthor[50];
    cout << "Enter author name to search: ";
    cin.ignore();
    cin.getline(searchAuthor, 50);

    Book b;
    fstream file;
    file.open("books.dat", ios::binary | ios::in);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    bool found = false;
    cout << "\n----- Search Results -----\n";

    while (file.read((char*)&b, sizeof(Book))) {
        if (strstr(b.author, searchAuthor) != NULL) {
            b.showData();
            found = true;
        }
    }

    if (!found)
        cout << "No books found with that author.\n";

    file.close();
}

// ---------------- Main Menu ----------------
int main() {
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1.  Add Book\n";
        cout << "2.  Add Member\n";
        cout << "3.  Display All Books\n";
        cout << "4.  Display All Members\n";
        cout << "5.  Issue Book\n";
        cout << "6.  Return Book\n";
        cout << "7.  Search by Title\n";
        cout << "8.  Search by Author\n";
        cout << "9.  Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                addMember();
                break;
            case 3:
                displayAllBooks();
                break;
            case 4:
                displayAllMembers();
                break;
            case 5:
                issueBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                searchByTitle();
                break;
            case 8:
                searchByAuthor();
                break;
            case 9:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
