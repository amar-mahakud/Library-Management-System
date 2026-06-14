# Library Management System (C++)

A console-based Library Management System built in C++ that manages books
and members using object-oriented programming and binary file handling for
persistent storage.

## Features

- **Add Book** – Register a new book with a unique Book ID, title, and author.
  Every new book is automatically marked as Available.
- **Add Member** – Register a new library member with a unique Member ID and name.
- **Display All Books** – Lists every book stored in `books.dat`, showing Book ID,
  title, author, availability status, and (if issued) which Member ID holds it.
- **Display All Members** – Lists every member stored in `members.dat`, showing
  Member ID and name.
- **Issue Book** – Marks a book as issued to a specific member. Prevents
  double-issuing — if the book is already issued, it reports which member
  currently holds it.
- **Return Book** – Marks an issued book as available again. Prevents returning
  a book that was never issued.
- **Search by Title** – Searches all books for a partial or full title match
  and displays all matching results.
- **Search by Author** – Searches all books for a partial or full author name
  match and displays all matching results.
- **Exit** – Closes the program.

## How It Works

- Two classes model the data:
  - `Book` — fields: `bookID` (int), `title` (char[50]), `author` (char[50]),
    `isIssued` (int: 0=available, 1=issued), `issuedToID` (int: member ID or 0).
  - `Member` — fields: `memberID` (int), `name` (char[50]).
- Fixed-size `char` arrays are used (instead of `std::string`) so entire objects
  can be written/read as raw bytes in binary mode.
- Two separate binary files store records:
  - `books.dat` — all book records.
  - `members.dat` — all member records.
  Both files are created automatically on first use.
- **Issue/Return** locates the matching book record by scanning the file, then
  uses `seekp` to move the write pointer back to the start of that record and
  overwrites it in place with the updated `isIssued` and `issuedToID` values.
- **Search** uses `strstr()` for partial substring matching — e.g., searching
  "Kalam" will match "Wings of Fire by A.P.J Abdul Kalam". All matching records
  are displayed (not just the first match).
- The program runs in a `do...while` loop showing a numbered menu (1–9) until
  the user selects Exit.

## Requirements

- A C++ compiler (e.g., g++)
- C++11 or later

## Build & Run

```bash
g++ -o lms LibraryManagementSystem.cpp
./lms
```

On Windows:

```bash
g++ -o lms.exe LibraryManagementSystem.cpp
lms.exe
```

## Notes / Limitations

- Book IDs and Member IDs are not checked for duplicates — adding two books
  with the same ID will create two separate records and cause unexpected
  behavior during issue/return (only the first match is processed).
- There is no delete or update feature for books or members.
- `books.dat` and `members.dat` are binary files and are not human-readable.
  Deleting them will erase all stored data.
- Title and author fields are limited to 49 characters each; member name is
  limited to 49 characters (fixed array sizes with null terminator).
- Search is case-sensitive — searching "wings" will not match "Wings of Fire".
- No input validation is performed (e.g., non-numeric input for IDs).
