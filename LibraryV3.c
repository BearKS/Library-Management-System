#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "LibraryCompro.bin"
// Macro related to the books info
#define MAX_STUDENT_NAME 50
#define MAX_STUDENT_ADDRESS 300
#define FILE_HEADER_SIZE  sizeof(sFileHeader)

void welcomeMessage();
void printMessageCenter(const char* message);
void headMessage(const char *message);
void login();
void updateAccount();
void init();
void menu();
void addBookInfoInDataBase();
void deleteBook();
void viewBooks();
void searchBooks();
void performBookSearch(int search_option, char* search_scope);
void addStudentInfoInDataBase();
void viewStudents();
void searchStudents();
void performStudentSearch(int search_option, char* search_scope);
void issueBook();
void view_overdue_books();
void returnBook();
int date_to_timestamp(int year, int month, int date);

FILE *books, *students, *issues;

time_t now;
char state[100] = "Available";
char state2[100] = "Borrowed";
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;

struct add_book {
	char id[100];
	char bookName[100];
	char authorName[100];
	char publisher[100];
	char subject[100];
	char date_added[100];
	char state[100];
};
struct add_book book;

struct add_student {
	char id[100];
	char name[100];
};
struct add_student student;

struct issueBook {
	char student_id[100];
	char book_id[100];
	char id[100];
	char date_loaned[100];
	int date_to_return;
};
struct issueBook issue;
//--------------------------------END OF LIBRARY&DEFINE---------------------------------//

//---------------------------------FUNCTION CHECK NAME----------------------------------//
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n'))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
//------------------------------END OF FUNCTION CHECK NAME--------------------------------//

//---------------------------------PRINT MESSAGE CENTER---------------------------------//
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    
    //calculate space to print
    len = (90 - strlen(message))/2;
    printf("");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
//-----------------------------END OF PRINT MESSAGE CENTER------------------------------//

//-----------------------------------HEADER MESSAGE-------------------------------------//
//Header Message
void headMessage(const char *message)
{
	system("cls");
    printf("\n\t\t\t------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t------------------------------------------\n\n");
    printf("\t\t                .--.                   .---.\n"); //1
    printf("\t\t            .---|__|           .-.     |~~~|\n"); //2
	printf("\t\t         .--|===|--|_          |_|     |~~~|--.\n"); //3
	printf("\t\t         |  |===|  |'\\     .---!~|  .--|   |--|\n"); //4
    printf("\t\t         |%%%%|   |  |.'\\    |===| |--|%%%%|   |  |\n"); //5
	printf("\t\t         |%%%%|   |  |\\.'\\   |   | |__|  |   |  |\n"); //6
	printf("\t\t         |  |   |  | \\  \\  |===| |==|  |   |  |\n"); //7
    printf("\t\t         |  |   |__|  \\.'\\ |   |_|__|  |~~~|__|\n"); //8
    printf("\t\t         |  |===|--|   \\.'\\|===|~|--|%%%%|~~~|--|\n"); //9
    printf("\t\t         ^--^---'--^    `-'`---^-^--^--^---'--'... \n"); //10
    printf("\t\t\t------------------------------------------\n"); //11
}
//-------------------------------END OF HEADER MESSAGE----------------------------------//

//----------------------------------WELCOME MESSAGE-------------------------------------//
//First Page Welcome
void welcomeMessage()
{
	system("mode CON: COLS=90 LINES=25");
    headMessage("Welcome");
    printf("\n\t\t      **-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    printf("\n\t\t                       - CREDIT -              ");
    printf("\n\t\t                         BearKS                ");
    printf("\n\t\t      **-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t           .....Enter any key to continue.....");
    getch();
}
//------------------------------END OF WELCOME MESSAGE----------------------------------//

//---------------------------------------MENU-------------------------------------------//
//Main Menu
void menu()
{
	system("mode CON: COLS=90 LINES=35");
    int choice = 0;
	do
    {
        headMessage("MAIN MENU");
        printf("\t........................................................................\n\n");
		printf("\t>> BOOKS <<             >> STUDENTS <<            >> ISSUE BOOK <<\n\n");
		printf("\t<1> Add New Book        <5> Add New Student       <8> Issue Book\n");
		printf("\t<2> View Books          <6> View Students         <9> View Overdue Books\n");
		printf("\t<3> Search Books        <7> Search Students       <10> Return Book\n");
		printf("\t<4> Delete Books                                                 \n");
		printf("\t........................................................................\n\n");
		printf("\t>> OTHER <<\n\n");
		printf("\t<11> Update Account\n\t<0> Exit\n");
		printf("\t........................................................................\n\n");
		printf("\n\t>>> Choose Your Option(0-10): ");
		scanf("%d",&choice);
		switch(choice) {
		case 1:
			addBookInfoInDataBase();
			break;
		case 2:
			(books = fopen("Books.txt", "r")) == NULL ? menu("No Book Records Exist") : viewBooks();
			break;
	
		case 3:
			(books = fopen("Books.txt", "r")) == NULL ? menu("No Book Records Exist") : searchBooks();
			break;
		case 4:
			deleteBook();
			break;
		case 5:
			addStudentInfoInDataBase();
			break;
		case 6:
			(students = fopen("Students.txt", "r")) == NULL ? menu("No Student Records Exist") : viewStudents();
			break;
		case 7:
			(students = fopen("Students.txt", "r")) == NULL ? menu("No Student Records Exist") : searchStudents();
			break;
		case 8:
			(students = fopen("Students.txt", "r")) == NULL ? menu("No Student Records Exist") :
			(books = fopen("Books.txt", "r")) == NULL ? menu("No Book Records Exist") : issueBook();
			break;
		case 9:
			(issues = fopen("Issues.txt", "r")) == NULL ? menu("No Issue Records Exist") : view_overdue_books();
			break;
		case 10:
			(issues = fopen("Issues.txt", "r")) == NULL ? menu("No Issue Records Exist") : returnBook();
			break;
		case 11:
            updateAccount();
            break;
		case 0:
			printf("\n\n\n\n\t- Bye Bye -\n\n\tSee you next time!\n\n\n\n\n");
			exit(1);
			break;
		default:
            printf("\n\n\n...INVALID INPUT! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=10);                                        //Loop Ended
}
//-----------------------------------END OF MENU----------------------------------------//

//----------------------------------ADD NEW BOOKS---------------------------------------//
//Add new books
void addBookInfoInDataBase()
{
	int status = 0;
	system("mode CON: COLS=90 LINES=40");
	headMessage("ADD NEW BOOKS");
	time(&now);
	printf("\n\tEnter your details below:\n");
	printf("\t........................................................................\n");
	printf("\n\t>> Book ID NO: ");
	fflush(stdin);
	scanf("%[^\n]", book.id);
	do{
        printf("\n\t>> Book Name: ");
        fflush(stdin);
        scanf("%[^\n]", book.bookName);
        status = isNameValid(book.bookName);
        if (!status){
            printf("\n\tInvalid character. Please try again.");
        }
    }while(!status);
    
    do{
        printf("\n\t>> Author: ");
		fflush(stdin);
		scanf("%[^\n]", book.authorName);
        status = isNameValid(book.authorName);
        if (!status){
            printf("\n\tInvalid character. Please try again.");
        }
    }while(!status);
    	
	do{
        printf("\n\t>> Publisher: ");
		fflush(stdin);
		scanf("%[^\n]", book.publisher);
        status = isNameValid(book.publisher);
        if (!status){
            printf("\n\tInvalid character. Please try again.");
        }
    }while(!status);

	do{
        printf("\n\t>> Subject: ");
	fflush(stdin);
	scanf("%[^\n]", book.subject);
        status = isNameValid(book.subject);
        if (!status){
            printf("\n\tInvalid character. Please try again.");
        }
    }while(!status);
	strcpy( book.state , state);
	headMessage("CONFIRM NEW BOOK");
	printf("\n\tComfirm to add new book:\n");
	printf("\t........................................................................\n\n");
	printf("\tBook ID NO: %s\n", &book.id);
	printf("\tBook Name: %s\n", &book.bookName);
	printf("\tAuthor: %s\n", &book.authorName);
	printf("\tPublisher: %s\n", &book.publisher);
	printf("\tSubject: %s\n", &book.subject);
	printf("\tDate Added: %s\n", strcpy(book.date_added, ctime(&now)));
	printf("\tState: %s\n", &book.state);
	printf("\t........................................................................\n");
	printf("\t               Are you sure you wish to Add this Record?                \n\n");
	printf("\t                       <Y> Yes            <N> No                        \n\n\n ");
 	addBookInfoInDataBase_confirmation_retry:
		switch (tolower(getch())) {
		case 'y':
			fprintf(books = fopen("Books.txt", "a+"), "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
				&book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);
			fclose(books);
			//menu("Record Added Successfully!");
			break;
		case 'n':
			//menu("");
			break;
		default:
			goto addBookInfoInDataBase_confirmation_retry;
		}
}
//-------------------------------END OF ADD NEW BOOKS-----------------------------------//


void deleteBook()
{
	headMessage("DELETE BOOK");

	FILE *books2,*fp;
	fp = fopen("Books.txt", "r");
	int found2 = 0;

	char book_id2[100], issue_id2[100];

//	fflush(stdin);
//	printf("\n\t>> Enter Student ID: ");
//	scanf("%[^\n]", student_id);
	fflush(stdin);

	printf("\n\t>> Book ID: ");
	scanf("%[^\n]", book_id2);
	strcpy(issue_id2, book_id2);
	fseek(books, 0, SEEK_END);
	rewind(books);

	while (!feof(fp)) {
		//printf("%s",issue_id2);
		fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
		       &book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);

		if (strcmp(book.id, issue_id2) == 0) {
			found2 = 1;
		}
	}
	
	if (found2 == 1) {
		printf("\n\t                            >> Book Found <<                          \n");
		printf("\t........................................................................\n\n");
		printf("\t                 Are you sure you wish to Delete this Book?             \n");
		printf("\t                        <Y> Yes            <N> No                       \n\n");
		printf("                               Choose an Option: ");
 		deleteBook_confirm_options_retry:
			switch (tolower(getch())) {
			case 'y':
				fseek(fp, 0, SEEK_END);
				rewind(fp);
				books2 = fopen("Books2.txt", "a+");
	
				while (!feof(fp)) {
					fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
			       		&book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);
	
					if (strcmp(book.id, issue_id2) != 0) {
						fprintf(books2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n", &book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);
					}
				}
				fclose(fp);
				remove("Books.txt");
				long savedOffset = ftell(books2);
				fseek(books2, 0, SEEK_END);
				if (ftell(books2) == 0) {
					fclose(books2);
					remove("Books2.txt");
				}
				fclose(books2);
				fclose(fp);
				rename("Books2.txt", "Books.txt");
				menu("Book Delete Successfully");
				break;
	
			case 'n':
				fclose(fp);
				break;
	
			default:
				goto deleteBook_confirm_options_retry;
		}
	}else  {
		printf("\n\t                       >> No Record Found <<                          \n");
		printf("\t........................................................................\n\n");
		printf("\t           <1> Delete Another Book         <0> Main Menu\n\n");
		printf("                               Choose an Option: ");

 deleteBook_not_found_options_retry:
		switch (getch()) {
		case '1':
			deleteBook();
			break;

		case '0':
			fclose(books);
			break;

		default:
			goto deleteBook_not_found_options_retry;
		}
	}
}


//------------------------------------VIEW BOOKS----------------------------------------//
//View books
void viewBooks()
{
	// Edit number of lines for long result
	system("mode CON: COLS=90 LINES=500");
	headMessage("VIEW BOOKS");
	int counter = 0;
	printf("\n\tView Books:\n");
	printf("\t........................................................................\n\n");
	while (!feof(books)) {
		fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
		       &book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);
		counter++;
//		char book.id;
//		if(book.id!=)
		printf("\tBook ID NO: %s\n", &book.id);
		printf("\tBook Name: %s\n", &book.bookName);
		printf("\tAuthor: %s\n", &book.authorName);
		printf("\tPublisher: %s\n", &book.publisher);
		printf("\tSubject: %s\n", &book.subject);
		printf("\tDate Added: %s\n", strcpy(book.date_added, ctime(&now)));
		printf("\tBook State: %s\n", &book.state);
		printf("\t........................................................................\n\n");
	}
	printf("\n                                  %d %s Available\n\n", counter, counter < 2 ? "Record" : "Records");
	printf("                        Press any Key to Return to the Main Menu");
	getch();
	fclose(books);
}
//---------------------------------END OF VIEW BOOKS------------------------------------//

//-----------------------------------SEARCH BOOKS---------------------------------------//
//Search Books (Menu)
void searchBooks()
{
	system("mode CON: COLS=90 LINES=40");
	int choice = 0;
	
	headMessage("SEARCH BOOKS");
	printf("\t................................");
	printf("\n\n\t<1> Book IDs\n\n\t<2> Book Names\n\n\t<3> Authors\n\n\t<4> Publishers\n\n\t<5> Subjects\n\n\t<0> Cancel\n");
	printf("\t................................\n\n");
	printf("\n\t>>> Choose Your Option(0-5): ");
	scanf("%d",&choice);
	searchBooks_options_retry:
	switch(choice) {
	case 1:
		performBookSearch(1, "Book IDs");
		break;
		
	case 2:
		performBookSearch(2, "Book Names");
		break;

	case 3:
		performBookSearch(3, "Authors");
		break;

	case 4:
		performBookSearch(4, "Publishers");
		break;

	case 5:
		performBookSearch(5, "Subjects");
		break;

	case 0:
		fclose(books);
		break;

	default:
		goto searchBooks_options_retry;
	}										//Switch Ended
}
//-------------------------------END OF SEARCH BOOKS------------------------------------//

//------------------------------PERFORM SEARCH BOOKS------------------------------------//
//Search Books
void performBookSearch(int search_option, char* search_scope)
{
	
	system("mode CON: COLS=90 LINES=300");
	int choice = 0;
	
	headMessage("SEARCH BOOKS");
	printf("\t%s :\n", search_scope);
	char search[20], *bookName_search, *author_search, *publisher_search, *subject_search,
	     *id_search, temp_bookName[100], temp_author[100], temp_publisher[100], temp_subject[100], temp_id[100];
	int counter = 0;
	fflush(stdin);
	printf("\t>> Enter %s: ", search_scope);
	scanf("%[^\n]", search);
	printf("\t........................................................................\n\n");
	// Convert the user entry to lower case to allow for case insensitive search
	strlwr(search);
	// Move the file pointer back to the start of the file
	// A previous search may have moved the pointer somewhere inside the file so we need to reset it
	fseek(books, 0, SEEK_END);
	rewind(books);

	while (!feof(books)) {
				fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
		       &book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);
		// Copy the attribute to a temporary variable, convert it to lower case and compare it with the search term the user entered
		bookName_search = strstr(strlwr(strcpy(temp_bookName, book.bookName)), search);
		author_search = strstr(strlwr(strcpy(temp_author, book.authorName)), search);
		publisher_search = strstr(strlwr(strcpy(temp_publisher, book.publisher)), search);
		subject_search = strstr(strlwr(strcpy(temp_subject, book.subject)), search);
		id_search = strstr(strlwr(strcpy(temp_id, book.id)), search);

		if ((search_option == 1 && id_search != NULL) ||
			(search_option == 2 && bookName_search != NULL) ||
		    (search_option == 3 && author_search != NULL) ||
		    (search_option == 4 && publisher_search != NULL) ||
		    (search_option == 5 && subject_search != NULL)) {
			counter++;

			printf("\tBook ID NO: %s\n", &book.id);
			printf("\tBook Name: %s\n", &book.bookName);
			printf("\tAuthor: %s\n", &book.authorName);
			printf("\tPublisher: %s\n", &book.publisher);
			printf("\tSubject: %s\n", &book.subject);
			printf("\tDate Added: %s\n", strcpy(book.date_added, ctime(&now)));
			printf("\t........................................................................\n\n");
		}
	}
	printf("\t%d %s Found for \"%s\"\n\n\n", counter, counter < 2 ? "Result" : "Results", search);
	printf("\t<1> Search again with <%s>     <2> New Search     <0> Cancel\n\n", search_scope);
	printf("\t>>> Choose Your Option(0-2): ");
	scanf("%d",&choice);
	
 	performBookSearch_options_retry:
	switch (choice) {
	case 1:
		performBookSearch(search_option, search_scope);
		break;
	case 2:
		searchBooks();
		break;
	case 0:
		fclose(books);
		break;
	default:
		goto performBookSearch_options_retry;
	}
}
//---------------------------END OF PERFORM SEARCH BOOKS--------------------------------//

//-----------------------------------ADD STUDENTS---------------------------------------//
void addStudentInfoInDataBase()
{
	system("mode CON: COLS=90 LINES=300");
	
	int status = 0;
	headMessage("ADD NEW STUDENTS");
	time(&now);
	printf("\n\tEnter your details below:\n");
	printf("\t........................................................................\n\n");
	

	printf("\n\t>> Student ID NO: ");
	fflush(stdin);
	scanf("%[^\n]", student.id);


	do{
        printf("\n\t>> Name: ");
		fflush(stdin);
		scanf("%[^\n]", student.name);
        status = isNameValid(student.name);
        if (!status){
            printf("\n\tInvalid character. Please try again.");
        }
    }while(!status);
	
	headMessage("NEW STUDENT");
	printf("\n\tComfirm to add new student:\n");
	printf("\t........................................................................\n\n");
	printf("\tStudent ID NO: %s\n", &student.id);
	printf("\tName: %s\n", &student.name);
	printf("\t........................................................................\n");
	printf("\t               Are you sure you wish to Add this Record?                \n\n");
	printf("\t                       <Y> Yes            <N> No                        \n\n\n ");
 	addStudentInfoInDataBase_options_retry:
		switch (tolower(getch())) {
		case 'y':
			fprintf(students = fopen("Students.txt", "a+"), "%s\n%s\n", &student.id, &student.name);
			fclose(students);
			break;
	
		case 'n':
			break;
	
		default:
			goto addStudentInfoInDataBase_options_retry;
		}
}
//--------------------------------END OF ADD STUDENTS-----------------------------------//

//----------------------------------SEARCH STUDENTS-------------------------------------//
void searchStudents()
{
	system("mode CON: COLS=90 LINES=40");
	int choice = 0;
	
	headMessage("SEARCH BOOKS");
	printf("\t................................");
	printf("\n\n\t<1> Student ID\n\n\t<2> Name\n\n\t<0> Cancel\n");
	printf("\t................................\n\n");
	printf("\n\t>>> Choose Your Option(0-2): ");
	scanf("%d",&choice);
	searchStudents_options_retry:
	switch(choice) {
	case 1:
		performStudentSearch(1, "Student ID");
		break;
		
	case 2:
		performStudentSearch(2, "Name");
		break;

	case 0:
		fclose(students);
		break;

	default:
		goto searchStudents_options_retry;
	}										//Switch Ended
}
//-------------------------------END OF SEARCH STUDENTS---------------------------------//

//------------------------------------VIEW STUDENTS-------------------------------------//
void viewStudents()
{
	system("mode CON: COLS=90 LINES=300");

	headMessage("VIEW STUDENTS");

	int counter = 0;
	
	printf("\n\tView Students:\n");
	printf("\t........................................................................\n\n");
	while (!feof(students)) {
		fscanf(students, "%[^\n]\n%[^\n]\n",&student.id, &student.name);
		counter++;
		printf("\tStudent ID NO: %s\n", &student.id);
		printf("\tName: %s\n", &student.name);
		printf("\t........................................................................\n\n");
	}
	printf("\n                                  %d %s Available\n\n", counter, counter < 2 ? "Record" : "Records");
	printf("                        Press any Key to Return to the Main Menu");
	getch();
	fclose(students);
}
//--------------------------------END OF VIEW STUDENTS----------------------------------//

//------------------------------PERFORM SEARCH STUDENTS---------------------------------//
void performStudentSearch(int search_option, char* search_scope)
{
	system("mode CON: COLS=90 LINES=50");
	
	int choice =0;
	headMessage("SEARCH STUDENTS");
	printf("\t%s :\n", search_scope);
		char search[20], *name_search, *id_search, temp_name[100], temp_id[100];
	int counter = 0;
	
	fflush(stdin);
	printf("\t>> Enter %s: ", search_scope);
	scanf("%[^\n]", search);
	printf("\t........................................................................\n\n");
	// Convert the user entry to lower case to allow for case insensitive search
	strlwr(search);
	// Move the file pointer back to the start of the file
	// A previous search may have moved the pointer somewhere inside the file so we need to reset it
	fseek(students, 0, SEEK_END);
	rewind(students);

	while (!feof(students)) {
		fscanf(students, "%[^\n]\n%[^\n]\n", &student.id, &student.name);

		name_search = strstr(strlwr(strcpy(temp_name, student.name)), search);

		id_search = strstr(strlwr(strcpy(temp_id, student.id)), search);
		
		if ((search_option == 1 && id_search != NULL) ||
			(search_option == 2 && name_search != NULL)) {
			counter++;

			printf("\tStudent ID NO: %s\n", &student.id);
			printf("\tName: %s\n", &student.name);
			printf("\t........................................................................\n\n");
		}
	}
	printf("\t%d %s Found for \"%s\"\n\n\n", counter, counter < 2 ? "Result" : "Results", search);
	printf("\t<1> Search again with <%s>     <2> New Search     <0> Cancel\n\n", search_scope);
	printf("\t>>> Choose Your Option(0-2): ");
	scanf("%d",&choice);
	
 	performStudentSearch_options_retry:
	switch (choice) {
	case 1:
		performStudentSearch(search_option, search_scope);
		break;
	case 2:
		searchStudents();
		break;
	case 0:
		fclose(students);
		break;
	default:
		goto performStudentSearch_options_retry;
	}
}
//---------------------------END OF PERFORM SEARCH STUDENTS-----------------------------//

//-----------------------------------ISSUE BOOKS----------------------------------------//
void issueBook()
{
	int iResult = 0;
	system("mode CON: COLS=90 LINES=60");
	int choice =0;
	headMessage("ISSUE BOOK");

	time(&now);

	int found_book = 0, found_student = 0, year = 0, month = 0, date = 0;
	char student_id[100], book_id[100];
	fflush(stdin);
	
	printf("\t>> Enter Student ID: ");
	scanf("%[^\n]", student_id);
	printf("\t........................................................................\n\n");

	fseek(students, 0, SEEK_END);
	rewind(students);

	while (!feof(students)) {
		fscanf(students, "%[^\n]\n%[^\n]\n", &student.id, &student.name);

		if (strcmp(student_id, student.id) == 0) {
			printf("\tStudent ID NO: %s\n", &student.id);
			printf("\tName: %s\n", &student.name);
			printf("\t........................................................................\n\n");
			found_student = 1;
			strcpy(issue.student_id, student.id);
		}
	}
	if (found_student != 1) {
		printf("\tNo student with ID: %s Found\n\n\n\n", student_id);
		printf("\t<1> New Issue              <0> Main Menu\n\n");
		printf("\t>>> Choose Your Option(0-1): ");
		scanf("%d",&choice);
	
 		issueBook_student_options_retry:
			switch (choice) {
			case 1:
				issueBook();
	
				break;
	
			case 0:
				fclose(students);
				break;
	
			default:
				goto issueBook_student_options_retry;
			}
	}
	
	fflush(stdin);
	printf("\t>> Enter Book ID: ");
	scanf("%[^\n]", book_id);
	printf("\t........................................................................\n\n");
	
	fseek(books, 0, SEEK_END);
	rewind(books);

	while (!feof(books)) {
		fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
		       &book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);

		if (strcmp(book_id, book.id) == 0) {
			printf("\tBook ID NO: %s\n", &book.id);
			printf("\tBook Name: %s\n", &book.bookName);
			printf("\tAuthor: %s\n", &book.authorName);
			printf("\tPublisher: %s\n", &book.publisher);
			printf("\tSubject: %s\n", &book.subject);
			printf("\tDate Added: %s\n", strcpy(book.date_added, ctime(&now)));
			printf("\t........................................................................\n\n");
			found_book = 1;
			strcpy(issue.book_id, book.id);
		}
	}
	if (!found_book) {
		printf("\tNo Book with ID: %s Found\n\n\n\n", book_id);
		printf("\t<1> New Issue              <0> Main Menu\n\n");
		printf("\t>>> Choose Your Option(0-1): ");
		scanf("%d",&choice);
		
 	issueBook_book_options_retry:
		switch (choice) {
		case 1:
			issueBook();
			break;

		case 0:
			fclose(students);
			fclose(books);
			break;

		default:
			goto issueBook_book_options_retry;
		}
	}
	
	printf("\tDate to Return\n\n");
	printf("\tYear(YYYY): ");
	scanf("%d", &year);
	printf("\tMonth(MM): ");
	scanf("%d", &month);
	printf("\tDate(DD): ");
	scanf("%d", &date);
	issue.date_to_return = date_to_timestamp(year, month, date);
	printf("\t........................................................................\n\n");
	printf("\t               Are you sure you wish to Add this Record?                \n\n");
	printf("\t                       <Y> Yes            <N> No                        \n\n\n ");
	printf("                               Choose an Option: ");

 	issueBook_confirm_issue_options_retry:
	switch (tolower(getch())) {
		case 'y':
			fprintf(issues = fopen("Issues.txt", "a+"), "%s\n%s\n%s%s\n%s%d\n",
				&issue.student_id, &issue.book_id, &issue.student_id, &issue.book_id, strcpy(issue.date_loaned, ctime(&now)), issue.date_to_return);

//			strcpy(book.state ,state2);				
//			fprintf(books = fopen("Books.txt", "a+"),"%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
//				&book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);
			fclose(books);
			fclose(issues);
			break;
	
		case 'n':
			break;
	
		default:
			goto issueBook_confirm_issue_options_retry;
		}
}
//-------------------------------END OF ISSUE BOOKS-------------------------------------//

//-------------------------------VIEW OVERDUE BOOKS-------------------------------------//
void view_overdue_books()
{
	system("mode CON: COLS=90 LINES=300");
	headMessage("VIEW OVERDUE BOOKS");

	int counter = 0, current_time = time(NULL);

	books = fopen("Books.txt", "r");

	students = fopen("Students.txt", "r");
	printf("\tDetails Below: \n");
	printf("\t........................................................................\n\n");
	while (!feof(issues)) {
		fscanf(issues, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%ld\n", &issue.student_id, &issue.book_id, &issue.id, &issue.date_loaned, &issue.date_to_return);

		if (issue.date_to_return < current_time) {
			fseek(students, 0, SEEK_END);
			rewind(students);

			while (!feof(students)) {
				fscanf(students, "%[^\n]\n%[^\n]\n", &student.id, &student.name);

				if (strcmp(issue.student_id, student.id) == 0) {
					printf("\t>> Student");
					printf("\n\n\t\tStudent ID: %s\n\t\tName: %s\n\n", &student.id, &student.name);
				}
			}
			fseek(books, 0, SEEK_END);
			rewind(books);

			while (!feof(books)) {
					fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
		       			&book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);

				if (strcmp(issue.book_id, book.id) == 0) {
					printf("\t>> Book");
					printf("\n\n\t\t>> Book ID: %s\n\t\t>> Book Name: %s\n\t\t>> Author: %s\n\t\t>> Publisher: %s\n\t\t>> Subject: %s",
					    &book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject);
				}
			}
			time_t date_to_return_timestamp = issue.date_to_return;
			printf("\n\n\tDate Issueed: %s", &issue.date_loaned);
			printf("\n\n\tDate to Return: %s\n\n", ctime(&date_to_return_timestamp));
			printf("\t........................................................................\n\n");
			counter++;
		}
	}
	printf("\n\t%d %s Available", counter, counter == 1 ? "Record" : "Records");
	printf("\n\n\t...Press any Key to Return to the Main Menu...");

	fclose(books);
	fclose(students);
	fclose(issues);

	getch();
}
//----------------------------END OF VIEW OVERDUE BOOKS---------------------------------//

//-----------------------------------RETURN BOOKS----------------------------------------//
void returnBook()
{
	headMessage("RETURN BOOK");

	FILE *issues2;

	int found = 0;

	char student_id[100], book_id[100], issue_id[100];

	fflush(stdin);
	printf("\n\t>> Enter Student ID: ");
	scanf("%[^\n]", student_id);
	fflush(stdin);

	printf("\n\t>> Book ID: ");
	scanf("%[^\n]", book_id);
	strcpy(issue_id, student_id);
	// Concatenate the student ID and book ID to determine the issue ID
	strcat(issue_id, book_id);
	fseek(issues, 0, SEEK_END);
	rewind(issues);

//	fseek(books, 0, SEEK_END);
//	rewind(books);
//	
//	while (!feof(books)) {
//		fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
//		       &book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);
//	}

	while (!feof(issues)) {
		fscanf(issues, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", &issue.student_id, &issue.book_id, &issue.id, &issue.date_loaned, &issue.date_to_return);

		if (strcmp(issue.id, issue_id) == 0) {
			found = 1;
		}
	}
	
	if (found == 1) {
		printf("\n\t                            >> Issue Found <<                          \n");
		printf("\t........................................................................\n\n");
		printf("\t                 Are you sure you wish to Return this Book?             \n");
		printf("\t                        <Y> Yes            <N> No                       \n\n");
		printf("                               Choose an Option: ");
 	returnBook_confirm_return_options_retry:
		switch (tolower(getch())) {
		case 'y':
			fseek(issues, 0, SEEK_END);
			rewind(issues);
			issues2 = fopen("Issues2.txt", "a+");

			while (!feof(issues)) {
				fscanf(issues, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", &issue.student_id, &issue.book_id, &issue.id, &issue.date_loaned, &issue.date_to_return);

				if (strcmp(issue.id, issue_id) != 0) {
					fprintf(issues2, "%s\n%s\n%s\n%s\n%s\n", &issue.student_id, &issue.book_id, &issue.id, &issue.date_loaned, &issue.date_to_return);
				}
			}
			fclose(issues);
			remove("Issues.txt");
			long savedOffset = ftell(issues2);
			fseek(issues2, 0, SEEK_END);
			if (ftell(issues2) == 0) {
				fclose(issues2);
				remove("Issues2.txt");
			}
//			strcpy( book.state , state);
//			fprintf(books = fopen("Books.txt", "a+"), "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
//				&book.id, &book.bookName, &book.authorName, &book.publisher, &book.subject, &book.date_added, &book.state);
			fclose(issues2);
			fclose(books);
			rename("Issues2.txt", "Issues.txt");
			menu("Book Returned Successfully");
			break;

		case 'n':
			fclose(issues);
			break;

		default:
			goto returnBook_confirm_return_options_retry;
		}
	}else  {
		printf("\n\t                       >> No Record Found <<                          \n");
		printf("\t........................................................................\n\n");
		printf("\t           <1> Return Another Book         <0> Main Menu\n\n");
		printf("                               Choose an Option: ");

 returnBook_not_found_options_retry:
		switch (getch()) {
		case '1':
			returnBook();
			break;

		case '0':
			fclose(issues);
			break;

		default:
			goto returnBook_not_found_options_retry;
		}
	}
}
//-------------------------------END OF RETURN BOOKS-------------------------------------//

//-----------------------------------DATE TO TIMESTAMP-----------------------------------//
int date_to_timestamp(int year, int month, int date)
{
	struct tm return_date;

	return_date.tm_year = year - 1900;
	return_date.tm_mon = month - 1;
	return_date.tm_mday = date;
	return_date.tm_hour = 0;
	return_date.tm_min = 0;
	return_date.tm_sec = 0;
	return_date.tm_isdst = 0;
	return mktime(&return_date);
}
//-------------------------------END OF DATE TO TIMESTAMP--------------------------------//

//-------------------------------------UPDATE ACCOUNT------------------------------------//
//Update Username&Password
void updateAccount(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("UPDATE ACCOUNT");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\nFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t>>> New Username: ");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\t>>> New Password: ");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\n\t\t\tYour Password has been changed successfully!\n");
    printf("\n\t\t\t     .....Enter any key to continue.....");
    fflush(stdin);
    getchar();
    login();
}
//---------------------------------END OF UPDATE ACCOUNT---------------------------------//

//-----------------------------------------LOGIN-----------------------------------------//
//login password
void login()
{
	system("mode CON: COLS=90 LINES=25");
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("LOGIN");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\t>>> Username: ");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t>>> Password: ");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\n\t...Login Failed Enter Again Username & Password...\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
//--------------------------------------END OF LOGIN-------------------------------------//

//------------------------------------IS FILE EXIXSTS------------------------------------//
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
//----------------------------------END OF ISFILEEXIXSTS--------------------------------//

//-----------------------------------------INIT-----------------------------------------//
//Default Setting First Time
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="admin\n";
    const char defaultPassword[] ="adminpass\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status){
        //Create the .bin file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL){
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
		}
    }
}
//-------------------------------------END OF INIT--------------------------------------//

//-----------------------------------------MAIN-----------------------------------------//
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}
//-------------------------------------END OF MAIN--------------------------------------//
