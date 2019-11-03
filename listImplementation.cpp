#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

class Node {
public:
	Node* next;
	string firstName;
	string lastName;
	int year;
	string country;
	Node();
};

Node::Node() {
	this->firstName = "";
	this->lastName = "";
	this->year = 0;
	this->country = "";
}

class List {
public:
	Node* head;
	int length;
	void display();
	void add(string firstName, string lastName, int year, string country);
	List() {
		this->head = NULL;
		length = 0;
	}
	List filterByCountry(string oneCountry);
	List countByCountry();
	void delete_position(int pos);
};

void List::delete_position(int pos)
{
	Node* current = new Node;
	Node* previous = new Node;
	current = head;
	for (int i = 1; i < pos; i++)
	{
		previous = current;
		current = current->next;
	}
	previous->next = current->next;
}


void List::add(string fName, string lName, int nYear, string fCountry) {

	Node* newOne = new Node;

	newOne->firstName = fName;
	newOne->lastName = lName;
	newOne->year = nYear;
	newOne->country = fCountry;

	if (head == 0) {
		head = newOne;
	}
	else {
		Node* pom = head;
		while (pom->next != NULL) {
			pom = pom->next;
		}
		pom->next = newOne;
		newOne->next = NULL;
	}
	length++;
}

void List::display() {
	Node* pom = new Node();
	pom = head;
	while (pom != NULL)
	{
		cout << "Imie: " << pom->firstName << "\t Nazwisko: " << pom->lastName << "\t Rok otrzymania nagrody: " << pom->year << "\t Kraj pohodzenia: " << pom->country << endl;
		pom = pom->next;
	}
}

List List::filterByCountry(string oneCountry) {
	List newList;
	Node* pom = head;
	while(pom!=NULL) {
		if (pom->country == oneCountry) {
			newList.add(pom->firstName, pom->lastName, pom->year, pom->country);
		}
		pom = pom->next;
	}
	return newList;
}

List List::countByCountry() {
	List newList;
	Node* pom = head;
	Node* pom2 = head;
	int licznik = 0;
	while (pom != NULL) {
		// pierwsza petla, bierzemy element do ktorego bedziemy porownywac
		string temp = pom2->country;
		for (int i =0; i<length; i++) {
			//porownujemy element z pierwszej petli ze wszystkimi el, listy

			if (temp == pom->country) {
				licznik++;
				delete_position(i);
			}
			pom = pom->next;
		}
		
		newList.add(pom2->country, "", licznik, "");
		cout << pom2->country << " ma " << licznik << " nagrod" << endl;
		if (pom2->next != NULL) {
				pom2 = pom2->next;
				pom = head;
				licznik = 0;
		}
		else {
			break;
		}
	}
	return newList;
	
}

int main()
{
	List list;
	fstream file;
	string fName, lName, fCountry;
	int nYear;
	file.open("data2.txt", ios::in);

	if (file.good() == true) {
		//file opened successfully
		
		char str[200];
		while (!file.eof())
		{
			file.getline(str, 200);
			char* schowek;
			char* next_token1 = NULL;
			schowek = strtok_s(str, ",", &next_token1); //spliting char array when comma is found
			while (schowek != NULL) {
				fName = schowek;
				schowek = strtok_s(NULL, ",", &next_token1);
				lName = schowek;
				schowek = strtok_s(NULL, ",", &next_token1);
				nYear = atoi(schowek);
				schowek = strtok_s(NULL, ",", &next_token1);
				fCountry = schowek;
				schowek = strtok_s(NULL, ",", &next_token1);
				list.add(fName, lName, nYear, fCountry);
			}
			
		}
		file.close();

	}
	list.countByCountry().display();
	//list.filterByCountry("Norwegia").display();
	//list.display();
	//system("pause");
	return 0;
}
