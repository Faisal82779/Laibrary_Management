#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
#endif

// ==================== Book Structure ====================
typedef struct Book {
    int id;
    char title[100];
    char author[100];
    int isBorrowed;
    struct Book *next;
} Book;

Book *head = NULL;

// ==================== Utility Functions ====================
void clearScreen() {
#ifdef _WIN32
    system("cls");
    system("color 0B"); // Blue text
#else
    system("clear");
#endif
}

void pressEnter() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Consume remaining input
}

int inputInt(const char *prompt) {
    int value;
    char line[50];
    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin)) {
            if (sscanf(line, "%d", &value) == 1) return value;
        }
        printf("Invalid input. Please enter a valid number.\n");
    }
}

void inputString(const char *prompt, char *str, size_t size) {
    printf("%s", prompt);
    if (fgets(str, size, stdin)) {
        str[strcspn(str, "\n")] = 0;
    }
}

void printHeader() {
    printf("=====================================================\n");
    printf("|          [ LIBRARY MANAGEMENT SYSTEM ]            |\n");
    printf("=====================================================\n\n");
}

void printBook(Book *book) {
    printf("| %3d | %-30s | %-20s | %-9s |\n",
           book->id, book->title, book->author, book->isBorrowed ? "Borrowed" : "Available");
}

Book* findBookByID(int id) {
    Book *temp = head;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

// ==================== Core Functions ====================
void addBook() {
    int id = inputInt("Enter Book ID: ");
    if (findBookByID(id)) {
        printf("A book with ID %d already exists!\n", id);
        pressEnter();
        return;
    }
    Book *newBook = malloc(sizeof(Book));
    newBook->id = id;
    inputString("Enter Book Title: ", newBook->title, sizeof(newBook->title));
    inputString("Enter Author Name: ", newBook->author, sizeof(newBook->author));
    newBook->isBorrowed = 0;
    newBook->next = head;
    head = newBook;
    printf("\nBook added successfully!\n");
    pressEnter();
}

void deleteBook() {
    int id = inputInt("Enter Book ID to delete: ");
    Book *temp = head, *prev = NULL;
    while (temp) {
        if (temp->id == id) {
            if (prev) prev->next = temp->next;
            else head = temp->next;
            free(temp);
            printf("\nBook deleted successfully!\n");
            pressEnter();
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Book not found!\n");
    pressEnter();
}

void borrowBook() {
    int id = inputInt("Enter Book ID to borrow: ");
    Book *book = findBookByID(id);
    if (!book) printf("Book not found!\n");
    else if (book->isBorrowed) printf("Book is already borrowed!\n");
    else { book->isBorrowed = 1; printf("Book borrowed successfully!\n"); }
    pressEnter();
}

void returnBook() {
    int id = inputInt("Enter Book ID to return: ");
    Book *book = findBookByID(id);
    if (!book) printf("Book not found!\n");
    else if (!book->isBorrowed) printf("Book is already available!\n");
    else { book->isBorrowed = 0; printf("Book returned successfully!\n"); }
    pressEnter();
}

void searchBook() {
    char title[100];
    inputString("Enter Book Title to search: ", title, sizeof(title));
    Book *temp = head;
    int found = 0;
    printf("\nSearch Results:\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("| ID  | Title                          | Author               | Status    |\n");
    printf("-----------------------------------------------------------------------------\n");
    while (temp) {
        if (strcasecmp(temp->title, title) == 0) {
            printBook(temp);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) printf("|                     No matching book found!             |\n");
    printf("-----------------------------------------------------------------------------\n");
    pressEnter();
}

void displayBooks() {
    if (!head) {
        printf("No books in library.\n");
        pressEnter();
        return;
    }
    printf("\nLibrary Books:\n");
    printf("---------------------------------------------------------------------------\n");
    printf("| ID  | Title                          | Author               | Status    |\n");
    printf("---------------------------------------------------------------------------\n");
    Book *temp = head;
    while (temp) {
        printBook(temp);
        temp = temp->next;
    }
    printf("---------------------------------------------------------------------------\n");
    pressEnter();
}

void sortBooksByTitle() {
    if (!head || !head->next) {
        printf("Not enough books to sort.\n");
        pressEnter();
        return;
    }

    int swapped;
    Book *ptr1;
    Book *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (strcasecmp(ptr1->title, ptr1->next->title) > 0) {
                // Swap book data
                int tempID = ptr1->id;
                char tempTitle[100], tempAuthor[100];
                strcpy(tempTitle, ptr1->title);
                strcpy(tempAuthor, ptr1->author);
                int tempBorrowed = ptr1->isBorrowed;

                ptr1->id = ptr1->next->id;
                strcpy(ptr1->title, ptr1->next->title);
                strcpy(ptr1->author, ptr1->next->author);
                ptr1->isBorrowed = ptr1->next->isBorrowed;

                ptr1->next->id = tempID;
                strcpy(ptr1->next->title, tempTitle);
                strcpy(ptr1->next->author, tempAuthor);
                ptr1->next->isBorrowed = tempBorrowed;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Books sorted by title successfully.\n");
    pressEnter();
}

void freeAllBooks() {
    Book *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// ==================== Main Menu ====================
int main() {
    int choice;
    while (1) {
        clearScreen();
        printHeader();
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Search Book by Title\n");
        printf("6. Sort Books by Title\n");
        printf("7. Display All Books\n");
        printf("8. Exit\n");
        printf("--------------------------------------------------\n");
        choice = inputInt("Enter your choice (1-8): ");

        switch (choice) {
            case 1: addBook(); break;
            case 2: deleteBook(); break;
            case 3: borrowBook(); break;
            case 4: returnBook(); break;
            case 5: searchBook(); break;
            case 6: sortBooksByTitle(); break;
            case 7: displayBooks(); break;
            case 8: freeAllBooks(); printf("\nThank you for using Library Management System!\n"); exit(0);
            default: printf("Invalid choice!\n"); pressEnter();
        }
    }
    return 0;
}

