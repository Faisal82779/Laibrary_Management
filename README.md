# 📚 Library Management System

A **console-based Library Management System** in C that allows users to manage books efficiently, including **adding, deleting, borrowing, returning, searching, sorting, and displaying all books**.

---

## ✨ Features

- 🆕 **Add Book**: Add a new book with unique ID, title, and author.  
- ❌ **Delete Book**: Remove a book by its ID.  
- 📖 **Borrow Book**: Borrow a book if it's available.  
- 🔄 **Return Book**: Return a borrowed book.  
- 🔍 **Search Book by Title**: Find books by title (case-insensitive).  
- 📚 **Sort Books by Title**: Sort all books alphabetically by title.  
- 🗂 **Display All Books**: Show all books with their current status (Available/Borrowed).  
- 🚪 **Exit**: Exit the program and free all allocated memory.  

---

## 🖥 Technology

- **Language**: C  
- **Platform**: Console-based  
- **OS Compatibility**: Windows (with colored text) and Linux/Unix  

---

## 📝 Usage

- Run the program using the instructions above.

- Enter the menu option number to perform an action (1-8).

- Follow prompts for entering book details (ID, Title, Author) or book ID for operations.

- 4. Press Enter to continue after messages.

- Repeat actions as needed.

- Choose Exit to terminate the program and free memory.

---

## 👤 Author

- **Faisal Ahmad**   

---

## ⚡ How to Run

```bash
# Clone the repository and navigate to the project folder
git clone <repository_url> Library-Management-System
cd Library-Management-System

# Compile the program
gcc library.c -o library

# Run the program
./library   # Linux/Mac
library.exe # Windows

