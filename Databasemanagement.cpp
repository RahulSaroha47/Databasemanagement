// Databasemanagement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<conio.h>
#include<stdlib.h>
using namespace std;

class Subjects {
protected:
	int BIO;
	int MA101;
	int OOPS;
	int Phy;
public:
	Subjects() {
		BIO = 0;
		MA101 = 0;
		OOPS = 0;
		Phy = 0;
	}
	void setmarks()
	{
		cout << "\nEnter marks scored by student in BIOLOGY : ";
		cin >> BIO;
		cout << "\nEnter marks scored by student in MA101 : ";
		cin >> MA101;
		cout << "\nEnter marks scored by student in Object-Oriented Programmming : ";
		cin >> OOPS;
		cout << "\nEnter marks scored by student in PHYSICS : ";
		cin >> Phy;
	}
	void showmarks()
	{
		if (BIO == 0 && MA101 == 0 && OOPS == 0 && Phy == 0)
		{
			cout << "\n\tNo marks updated yet\n";
		}
		else {

			cout << "\n\tMarks scored in BIOLOGY : " << BIO;
			cout << "\n\tMarks scored in MA101 :  " << MA101;
			cout << "\n\tMarks scored in Object-Oriented Programming : " << OOPS;
			cout << "\n\tMarks scored in PHYSICS : " << Phy;
		}
	}
};

class Attendance {
protected:
	int attBIO;
	int attMA101;
	int attOOPS;
	int attPhy;
public:
	Attendance() {
		attBIO = 0;
		attMA101 = 0;
		attOOPS = 0;
		attPhy = 0;
	}
	void setAttendance()
	{
		cout << "\nEnter attendance of student in BIOLOGY : ";
		cin >> attBIO;
		cout << "\nEnter attendance of student in MA101 : ";
		cin >> attMA101;
		cout << "\nEnter attendance of student in Object-Oriented Programming : ";
		cin >> attOOPS;
		cout << "\nEnter attendance of student in PHYSICS : ";
		cin >> attPhy;
	}
	void showAttendance()
	{
		if (attBIO == 0 && attMA101 == 0 && attOOPS == 0 && attPhy == 0)
		{
			cout << "\n\tNo attendance updated yet\n";
		}
		else
		{

			cout << "\n\tAttendance in BIOLOGY : " << attBIO;
			cout << "\n\tAttendance in MA101 : " << attMA101;
			cout << "\n\tAttendance in Object-Oriented Programming : " << attOOPS;
			cout << "\n\tAttendance in PHYSICS : " << attPhy;
		}
	}
};

class Student :public Subjects, public Attendance
{
	int admno;
	char name[50];
	char section[50];
	char course[50];

public:
	void setData()
	{
		cout << "\nEnter registration no.: ";
		cin >> admno;
		cout << "\nEnter name of student: ";
		cin.ignore();
		cin.getline(name, 50);
		cout << "\nEnter course enrolled: ";
		cin.getline(course, 50);
		cout << "\nEnter section of the student: ";
		cin.getline(section, 50);
	}

	void showData()
	{
		cout << "\n\tRegistration no. : " << admno;
		cout << "\n\tStudent Name : " << name;
		cout << "\n\tCourse Enrolled : " << course;
		cout << "\n\tSection in the course : " << section;
	}

	int retAdmno()
	{
		return admno;
	}
};


/*
* function to write in a binary file.
*/

void write_record()
{
	ofstream outFile;
	outFile.open("student.dat", ios::binary | ios::app);

	Student obj;
	obj.setData();

	outFile.write((char*)&obj, sizeof(obj));

	outFile.close();
}

/*
* function to display records of file
*/


void display()
{
	fstream File;
	File.open("student.dat", ios::in | ios::binary);

	Student obj;

	while (File.read((char*)&obj, sizeof(obj)))
	{
		obj.showData();
		obj.showmarks();
		obj.showAttendance();
	}

	File.close();
}

/*
* function to search and display from binary file
*/

void search(int n)
{
	int flag = 0;
	fstream inFile;
	inFile.open("student.dat", ios::in | ios::binary);

	Student obj;

	while (inFile.read((char*)&obj, sizeof(obj)))
	{
		if (obj.retAdmno() == n)
		{
			obj.showData();
			flag = 1;
		}
	}
	if (flag == 0)
		cout << "\n\tNo data found\n";

	inFile.close();
}

/*
* function to delete a record
*/

void delete_record(int n)
{
	int flag = 0;
	Student obj;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);

	ofstream outFile;
	outFile.open("temp.dat", ios::out | ios::binary);

	while (inFile.read((char*)&obj, sizeof(obj)))
	{
		if (obj.retAdmno() != n)
		{
			outFile.write((char*)&obj, sizeof(obj));
			flag = 1;
		}
	}
	if (flag == 0)
		cout << "\nInvalid registration number\n";

	inFile.close();
	outFile.close();

	remove("student.dat");
	rename("temp.dat", "student.dat");
}

/*
* function to modify a record
*/

void modify_record(int n)
{
	int flag = 0;
	fstream file;
	file.open("student.dat", ios::in | ios::out);

	Student obj;

	while (file.read((char*)&obj, sizeof(obj)))
	{
		if (obj.retAdmno() == n)
		{
			cout << "\n\t\t\tEnter the new details of student:\n";
			obj.setData();
			flag = 1;
			int pos = -1 * (int)sizeof(obj);
			file.seekp(pos, ios::cur);

			file.write((char*)&obj, sizeof(obj));
		}
	}
	if (flag == 0)
		cout << "Invalid registration number\n";
	file.close();
}

/*
* function to delete entire database
*/
void dbms_delete()
{
	ofstream outfile;
	outfile.open("student.dat", ios::out | ios::trunc);
	outfile.close();
}

/*
* function to set marks of students
*/
void setmarks_subjects()
{
	int flag = 0;
	int number;
	cout << "\nEnter student registration number\n";
	cin >> number;
	fstream file;
	file.open("student.dat", ios::in | ios::binary | ios::out);
	Student obj;
	while (file.read((char*)&obj, sizeof(obj)))
	{
		if (obj.retAdmno() == number)
		{
			flag = 1;
			obj.setmarks();
			int pos = -1 *(int)sizeof(obj);
			file.seekp(pos, ios::cur);

			file.write((char*)&obj, sizeof(obj));
		}
	}
	if (flag == 0)
		cout << "\nInvalid registration number\n";
}

/*
* function to show marks of students
*/
void showmarks_subjects(int n)
{
	int flag = 0;
	fstream file;
	file.open("student.dat", ios::in | ios::out | ios::binary);
	Student obj;
	while (file.read((char*)&obj, sizeof(obj)))
	{
		if (obj.retAdmno() == n)
		{
			flag = 1;
			obj.showmarks();
		}
	}
	if (flag == 0)
		cout << "\nInvalid registration number\n";
}

/*
* function to set attendance of students
*/
void set_attendance()
{
	int flag = 0;
	int number;
	cout << "\nEnter student registration number\n";
	cin >> number;
	fstream file;
	file.open("student.dat", ios::in | ios::binary | ios::out);
	Student obj;
	while (file.read((char*)&obj, sizeof(obj)))
	{
		if (obj.retAdmno() == number)
		{
			flag = 1;
			obj.setAttendance();
			int pos = -1 * (int)sizeof(obj);
			file.seekp(pos, ios::cur);

			file.write((char*)&obj, sizeof(obj));
		}
	}
	if (flag == 0)
		cout << "\nInvalid registration number\n";
}
/*
* function to show attendance
*/
void show_attendance(int n)
{
	int flag = 0;
	fstream file;
	file.open("student.dat", ios::in | ios::out | ios::binary);
	Student obj;
	while (file.read((char*)&obj, sizeof(obj)))
	{
		if (obj.retAdmno() == n)
		{
			flag = 1;
			obj.showAttendance();
		}
	}
	if (flag == 0)
		cout << "\nInvalid registration number\n";
}
int main()
{
	char adminpass[50];
	int choice, option;
	char ch;
	do {
		system("cls");
		cout << "**************Student Database Management System****************\n";
		cout << "************Coded by RAHUL SAROHA***************\n";
		cout << "1.Admin Login\n";
		cout << "2.Student Login\n";
		cout << "3.Faculty Login\n";
		cout << "4.Exit\n\n";
		cout << "Select your option:";

		cin >> choice;

		switch (choice)
		{
		case 1: {
			system("cls");
			cout << "****************Admin Login*******************\n";
			cout << "Enter admin password- ";
			cin >> adminpass;
			if (strcmp(adminpass, "rahul") == 0)
			{
				system("cls");
				cout << "\n****************Admin Options*********************\n";
				cout << "\n1.Add a record";
				cout << "\n2.View a specific record";
				cout << "\n3.Delete a record";
				cout << "\n4.Delete complete database";
				cout << "\n5.Modify a record";
				cout << "\n6.Exit";
				cout << "\nSelect your option:";
				cin >> option;
				switch (option) {
					system("cls");
				case 1: {
					do {
						system("cls");
						write_record();
						cout << "\nAdd another record(y/n)? ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					break;
				}
				case 2: {
					do {
						system("cls");
						int number;
						cout << "\nEnter registration number:";
						cin >> number;
						search(number);
						showmarks_subjects(number);
						show_attendance(number);
						cout << "\nView another record(y/n)? ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					break;
				}
				case 3: {
					do
					{
						system("cls");
						int number;
						cout << "\nEnter registration number of the person you want to delete record of:";
						cin >> number;
						cout << "\nCaution!!! you are about to delete a record. Proceed? ";
						cin >> ch;
						if (ch == 'y' || ch == 'Y')
							delete_record(number);
						cout << "\nDelete another record(y/n)? ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					break;
				}
				case 4: {
					cout << "\nCaution!!! you are about to completely wipeoff the database. Proceed? ";
					cin >> ch;
					if (ch == 'y' || ch == 'Y')
						dbms_delete();
					break;
				}
				case 5: {
					do
					{
						system("cls");
						int number;
						cout << "Enter registration number of the person you want to modify-";
						cin >> number;
						modify_record(number);
						cout << "\nModify another record(y/n)? ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					break;
				}
				case 6: {
					break;
				}

				}
			}
			else
			{
				cout << "Invalid Password";
			}
			break;
		}
		case 2: {
			do
			{
				system("cls");
				cout << "\n*******************Student Login*******************";
				cout << "\nEnter student registration number : ";
				int number;
				cin >> number;
				search(number);
				showmarks_subjects(number);
				show_attendance(number);
			} while (!_getch());
			break;
		}
		case 3: {
			do
			{
				system("cls");
				cout << "\n******************Faculty Login*****************";
				cout << "\n1.Update Marks";
				cout << "\n2.Update Attendance";
				cout << "\n3.Exit";
				cout << "\n\nSelect option : ";
				cin >> ch;
				switch (ch) {
				case '1': {
					do
					{
						system("cls");
						setmarks_subjects();
						cout << "\nDo you want to update marks of another student(y/n)? ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					break;
				}
				case '2': {
					do
					{
						system("cls");
						set_attendance();
						cout << "\nDo you want to update attendance of another student(y/n)? ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					break;
				}
				case '3': {
					break;
				}
				}
			} while (ch != '3');
			break;
		}
		case 4:
		{
			return 0;
		}
		}
	} while (ch != 4);
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
