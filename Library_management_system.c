#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct admin {
    char username[50];
    char password[50];
} a;

struct user {
    char username[50];
    char password[50];
} u;

struct books {
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b;

struct student {
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
} s;

FILE *fp;

void adminregis();
void adminlogin();
void userregis();
void userlogin();
void addBook();
void booksList();
void del();
void issueBook();
void issueList();

int main() {
    int choice;
    printf("Enter your role\n");
    printf("1. Admin Registration\n");
    printf("2. Admin Login\n");
    printf("3. User Registration\n");
    printf("4. User login\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        adminregis();
        break;
    case 2:
        adminlogin();
        break;
    case 3:
        userregis();
        break;
    case 4:
        userlogin();
        break;
    default:
        printf("Invalid choice\n");
        break;
    }

    return 0;
}

void adminregis() {
    fp = fopen("adminlogin.txt", "ab");
    printf("\nEnter Username: ");
    fflush(stdin);
    gets(a.username);
    printf("\nEnter Password: ");
    fflush(stdin);
    gets(a.password);
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("registration complete\n");
    printf("login using your credentials\n");
    adminlogin();
}

void adminlogin() {
    char user[50];
    char pass[50];
    int found = 0;

    fp = fopen("adminlogin.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("\nEnter Username: ");
    fflush(stdin);
    gets(user);
    printf("\nEnter Password: ");
    fflush(stdin);
    gets(pass);

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (strcmp(a.username, user) == 0 && strcmp(a.password, pass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found==1) {
        printf("Login Successful\n");

        int choice;
        while (1) {
            printf("\n<== Library Management System ==>\n");
            printf("1. Add Book\n");
            printf("2. View Books List\n");
            printf("3. Remove Book\n");
            printf("4. Issue Book\n");
            printf("5. View Issued Book List\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 0:
                exit(0);
            case 1:
                addBook();
                break;
            case 2:
                booksList();
                break;
            case 3:
                del();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                issueList();
                break;
            default:
                printf("Invalid Choice\n");
            }
        }
    } else {
        printf("Invalid Username or Password\n");
    }
}

void userregis() {
    fp = fopen("userlogin.txt", "ab");
    printf("\nEnter Username: ");
    fflush(stdin);
    gets(u.username);
    printf("\nEnter Password: ");
    fflush(stdin);
    gets(u.password);
    fwrite(&u, sizeof(u), 1, fp);
    fclose(fp);
    printf("User Registration Complete\n");
    printf("Login Using your Credentials\n");
    userlogin();
}

void userlogin() {
    char user[50];
    char pass[50];
    int found = 0;

    fp = fopen("userlogin.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("\nEnter Username: ");
    fflush(stdin);
    gets(user);
    printf("\nEnter Password: ");
    fflush(stdin);
    gets(pass);

    while (fread(&u, sizeof(u), 1, fp) == 1) {
        if (strcmp(u.username, user) == 0 && strcmp(u.password, pass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found) {
        printf("Login Successful\n");
        int choice;
        while (1) {
            printf("\n<== User Menu ==>\n");
            printf("1. View Book List\n");
            printf("2. View Issued Books\n");
            printf("0. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 0:
                return; 
            case 1:
                booksList();
                break;
            case 2:
                viewIssuedBooks(user); 
                break;
            default:
                printf("Invalid Choice\n");
            }
        }
    } else {
        printf("Invalid Username or Password\n");
    }
}

void addBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("Book Added Successfully\n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

void booksList() {
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void del() {
    int id, f = 0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (id == b.id) {
            f = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if (f == 1) {
        printf("\nDeleted Successfully\n");
    } else {
        printf("\nRecord Not Found\n");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void issueList() {
    system("cls");
    printf("<== Issued Book List ==>\n\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "Book id", "Student Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issued_books.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}

void viewIssuedBooks(char *username) {
    system("cls");
    printf("<== Books Issued to %s ==>\n\n", username);
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("issued_books.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (strcmp(s.sName, username) == 0) {
            printf("%-10d %-30s %-20s %s\n", s.id, s.bookName, "", s.date);
        }
    }

    fclose(fp);
}

void issueBook() {
    int bookId;
    char userName[50];

    printf("Enter Book ID to issue: ");
    scanf("%d", &bookId);

    printf("Enter User Name to whom the book is issued: ");
    fflush(stdin);
    gets(userName);

    fp = fopen("issued_books.txt", "ab");
    if (fp == NULL) {
        printf("Error opening file for issuing book\n");
        return;
    }

    FILE *booksFile = fopen("books.txt", "rb");
    if (booksFile == NULL) {
        printf("Error opening file for reading books\n");
        fclose(fp);
        return;
    }

    struct books book;
    int found = 0;
    while (fread(&book, sizeof(book), 1, booksFile) == 1) {
        if (book.id == bookId) {
            found = 1;
            break;
        }
    }
    fclose(booksFile);

    if (!found) {
        printf("Book with ID %d not found\n", bookId);
        fclose(fp);
        return;
    }

    struct student issuedBook;
    issuedBook.id = book.id;
    strcpy(issuedBook.bookName, book.bookName);
    strcpy(issuedBook.date, book.date);
    strcpy(issuedBook.sName, userName);

    fwrite(&issuedBook, sizeof(issuedBook), 1, fp);
    fclose(fp);

    printf("Book with ID %d issued to user %s successfully\n", bookId, userName);
}
