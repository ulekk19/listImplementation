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
	void filterByCountry(int oneCountry);
};

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

void List::filterByCountry(int oneCountry) {
	List newList;
	Node* pom = head;
	for (int i = 0; i < length; i++) {
		if (pom->year == oneCountry) {
			cout << "Dodano element" << endl;
			newList.add(pom->firstName, pom->lastName, pom->year, pom->country);
		}
		else {
			cout << "Cos poszlo nie tak" << endl;
		}
	}
	//return newList;
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
	list.filterByCountry(1904);
	//cout << "Dlugosc listy: " << list.length << endl;
	//list.display();
	//system("pause");
	return 0;
}
