/* "zahra Esnaashari ~ 98103239 ~ final project" */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

bool memberRegistration(string ID){
	string nationalNumber, firstName, lastName, phoneNumber;
	int borrowedBooks;
	bool found = false;
	
	fstream member;
	member.open("member.txt", ios::in);
	while(member >> nationalNumber >> firstName >> lastName >> phoneNumber >> borrowedBooks){
		if(ID == nationalNumber){
			cout << "\tThis member has already registered" << endl;
			cout << "\t=================================================" << endl;
			found = true;
		}
	}
	member.close();
	return found;
}

bool bookRegistration(string ID){
	string info, ISBN, bookName, authorName, initialCount, finalCount;
	bool found = false;
	
	fstream book;
	book.open("book.txt", ios::in);
	while(book >> ISBN >> bookName >> authorName >> initialCount >> finalCount){
		if(ID == ISBN){
			cout << "\tThis book has already registered" << endl;
			cout << "\t=================================================" << endl;
			found = true;
		}
	}
	book.close();
	return found;
}

void newMember(){
	cout << "\n\t=================================================" << endl;
	cout << "\tPlease enter an informatian." << endl;
	
	string nationalNumber, firstName, lastName, phoneNumber;
	int borrowedBooks = 0;
	
	cout << "\t\t national ID number: ";
	cin >> nationalNumber;
	if(memberRegistration(nationalNumber)) return;

	cout << "\t\t first name: ";
	FN: cin >> firstName;
	
	cout << "\t\t last name: ";
	LN: cin >> lastName;
	
	cout << "\t\t phone number: ";
	PN: cin >> phoneNumber;

	ofstream member("member.txt", ios::app);
	member << nationalNumber << " " << firstName << " " << lastName << " " << phoneNumber << " " << borrowedBooks << endl;

	cout << "\tMember successfully registered." << endl;
	cout << "\t=================================================" << endl;

}

void newBook(){
	cout << "\n\t=================================================" << endl;
	cout << "\tPlease enter an informatian." << endl;
	
	string ISBN, bookName, authorName;
	int initialCount, finalCount;
	
	cout << "\t\t ISBN: ";
	cin >> ISBN;
	if(bookRegistration(ISBN)) return;
	
	cout << "\t\t book name: ";
	BN: cin >> bookName;
	
	cout << "\t\t author name: ";
	AN: cin >> authorName;

	cout << "\t\t initial count: ";
	cin >> initialCount;
	
	cout << "\t\t final count: ";
	cin >> finalCount;

	ofstream member("book.txt", ios::app);
	member  << ISBN << " " << bookName << " " << authorName << " " << initialCount << " " << finalCount << endl;

	cout << "\tThe book was successfully registered." << endl;
	cout << "\t=================================================" << endl;
}

bool isMemberAvailable(string ID){
	string nationalNumber, firstName, lastName, phoneNumber;
	int borrowedBooks;
	bool found = false;
	
	fstream member;
	member.open("member.txt", ios::in);
	while (member >> nationalNumber >> firstName >> lastName >> phoneNumber >> borrowedBooks) {
		if (ID == nationalNumber) {
			if (borrowedBooks < 3) {
				member.close();
				found = true;
			}
		}
	}
	member.close();
	return found;
}

bool isBookAvailable(string ID){
	string ISBN, bookName, authorName;
	int initialCount, finalCount;
	bool found = false;
	
	fstream book;
	book.open("book.txt", ios::in);
	while (book >> ISBN >> bookName >> authorName >> initialCount >> finalCount) {
		if (ID == ISBN) {
			if (finalCount > 0) {
				book.close();
				found = true;
			}
		}
	}
	book.close();
	return found;
}

void changeBookCapacity(string ID, int count) {
	string ISBN, bookName, authorName;
	int initialCount, finalCount;
	
	fstream book;
	book.open("book.txt", ios::in);

	fstream tempBook;
	tempBook.open("tempBook.txt", ios::app);

	while (book >> ISBN >> bookName >> authorName >> initialCount >> finalCount) {
		if (ID == ISBN) {
			finalCount += count;
		}
		tempBook << ISBN << " " << bookName << " " << authorName << " " << initialCount << " " << finalCount << endl;
	}

	book.close();
	tempBook.close();
	remove("book.txt");
	rename("tempBook.txt", "book.txt");
}

void changeMemberCapacity(string ID, int count) {
	string nationalNumber, firstName, lastName, phoneNumber;
	int borrowedBooks;
	
	fstream member;
	member.open("member.txt", ios::in);

	fstream tempMember;
	tempMember.open("tempMember.txt", ios::app);

	while (member >> nationalNumber >> firstName >> lastName >> phoneNumber >> borrowedBooks) {
		if (ID == nationalNumber) {
			borrowedBooks += count;
		}
		tempMember << " " << nationalNumber << " "<< firstName << " " << lastName << " " << phoneNumber << " " << borrowedBooks << endl;
	}

	member.close();
	tempMember.close();
	remove("member.txt");
	rename("tempMember.txt", "member.txt");
}

void borrowBook() {
	string ISBN, nationalNumber;
	cout << "\n\t=================================================" << endl;
	
	cout << "\tEnter an ISBN of book: ";
	cin >> ISBN;
	if(!isBookAvailable(ISBN)) {
		cout << "\tBook capacity is over or The book dose not exist!" << endl;
		cout << "\t=================================================" << endl;
		return;
	}
	
	cout << "\tEnter an nationalNumber of member: ";
	cin >> nationalNumber;
	if (!isMemberAvailable(nationalNumber)) {
		cout << "\tMember capacity is over or Member is not registered!" << endl;
		cout << "\t=================================================" << endl;
		return;
	}
	
	changeBookCapacity(ISBN, -1);
	changeMemberCapacity(nationalNumber, +1);
	fstream memBook;
	memBook.open("mem_book.txt", ios::app);
	memBook << nationalNumber << " " << ISBN << endl;
	memBook.close();
	cout << "\tThe book was successfully borrowed" << endl;
	cout << "\t=================================================" << endl;
}

bool memberCheck(string ID){
	string nationalNumber, firstName, lastName, phoneNumber;
	int borrowedBooks;
	bool found = false;
	
	fstream member;
	member.open("member.txt", ios::in);
	while (member >> nationalNumber >> firstName >> lastName >> phoneNumber >> borrowedBooks) {
		if (ID == nationalNumber) {
			if (borrowedBooks > 0) {
				member.close();
				found = true;
			}
		}
	}
	member.close();
	return found;
}

bool bookCheck(string ID){
	string ISBN, bookName, authorName;
	int initialCount, finalCount;
	bool found = false;
	
	fstream book;
	book.open("book.txt", ios::in);
	while (book >> ISBN >> bookName >> authorName >> initialCount >> finalCount) {
		if (ID == ISBN) { 
			if (finalCount < finalCount) {
				book.close();
				found = true;
			}
		} found = true;
	}
	book.close();
	return found;
}

void returnBook(){
	string ISBN, nationalNumber;
	cout << "\n\t=================================================" << endl;
	
	cout << "\tEnter an ISBN of book: ";
	cin >> ISBN;
	if(!bookCheck(ISBN)) {
		cout << "\tBook capacity is full or The book dose not exist!" << endl;
		cout << "\t=================================================" << endl;
		return;
	}
	
	cout << "\tEnter an nationalNumber of member: ";
	cin >> nationalNumber;
	if(!memberCheck(nationalNumber)){
		cout << "\tMember capacity is zero or Member is not registered!" << endl;
		cout << "\t=================================================" << endl;
		return;
	}
	
	fstream memBook;
	memBook.open("mem_book.txt", ios::in);

	fstream tempMemBook;
	tempMemBook.open("tempMemBook.txt", ios::app);

	string bookID, memberID;
	bool isReturn = false;
	while (memBook >> memberID >> bookID){
		if (nationalNumber == memberID && ISBN == bookID && !isReturn) {
			isReturn = true;
			changeBookCapacity(ISBN, +1);
			changeMemberCapacity(nationalNumber, -1);
		}
		else {
			tempMemBook << memberID << " " << bookID << endl;
		}
	}
	
	memBook.close();
	tempMemBook.close();
	remove("mem_book.txt");
	rename("tempMemBook.txt", "mem_book.txt");
	cout << "\tThe book was successfully returned" << endl;
	cout << "\t=================================================" << endl;
}

int main(){
	while(true){
		cout << "\t" << "MENU \n\n";
		cout << "\t" << "01.NEW MEMBER" << endl;
		cout << "\t" << "02.NEW BOOK" << endl;
		cout << "\t" << "03.BORROW BOOK" << endl;
		cout << "\t" << "04.Return BOOK" << endl;
		cout << "\t" << "05.EXIT \n" << endl;
		cout << "\t" << "Select your option (1-5) ";
		
		int item;
		getItem: cin >> item;
		
		switch(item){
			case 1: newMember(); break;
			case 2: newBook(); break;
			case 3: borrowBook(); break;
			case 4: returnBook(); break;
			case 5: cout << "\n\t=================================================\n" << "\tThe operation is over" << endl; return 0;
			default: cout << "\tInvalid option, try again.\n\n"; break;
		}
	}
}

