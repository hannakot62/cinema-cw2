#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#include "funcs.h"
#include "User.h"
using namespace MyNS;

User::User() {
	login = "somebody";
	password = "1111";
}

User::User(string login, string password) {
	this->login = login;
	this->password = password;
}

string User::GetLogin() { return login; }
string User::GetPassword() { return password; }
void User::SetLogin(string login) { this->login = login; }
void User::SetPassword(string password) { this->password = password; }

void User::Write(ofstream& out) {
	if (out.is_open())
	{
		out << login << "-" << password <<"-" << endl;
	}
	else {
		cout << "Error" << endl;
	}
}

void User::Read(ifstream& in) {
	getline(in, login, '-');
	getline(in, password, '-');
	in.get();
}

void FileSetUsers(int UsersQuantity, User* users) {
	ofstream out;          // ����� ��� ������
	string file = "users.txt";
	out.open(file); // �������� ���� ��� ������
	for (int i = 0; i < UsersQuantity; i++) {
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] + 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] + 10;
		}
		users[i].Write(out);
	}
	out.close();
}

int FileGetUsers() {
	User* users;
	int num = 0;
	ifstream in("users.txt");
	if (in.is_open()) { //������ ���������� ��������
		string str;
		while (!in.eof()) {
			getline(in, str, '\n');
			num++;
		}
	}
	int UsersQuantity = num - 1;
	users = new User[UsersQuantity + 2];
	in.close();
	ifstream iin("users.txt");
	for (int i = 0; i < UsersQuantity; i++) {
		users[i].Read(iin);
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] - 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] - 10;
		}
	}
	iin.close();
	return UsersQuantity;
}

void ShowUsers() {
	///////////////////////////////////////////////////////////// ������ �� �����
	User* users;
	cout << endl;
	int num = 0;
	ifstream in("users.txt");
	if (in.is_open()) { //������ ���������� ��������
		string str;
		while (!in.eof()) {
			getline(in, str, '\n');
			num++;
		}
	}
	int UsersQuantity = num - 1;
	users = new User[UsersQuantity + 2];
	in.close();
	ifstream iin("users.txt");
	for (int i = 0; i < UsersQuantity; i++) {
		users[i].Read(iin);
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] - 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] - 10;
		}
	}
	iin.close();
	////////////////////////////////////////////////////////// ���������� ������
	if (UsersQuantity) {
		cout << "---------------------------------" << endl;
		cout << "|��/�|    �����    |   ������   |" << endl;
		cout << "---------------------------------" << endl;
		for (int i = 0; i < UsersQuantity; i++) {
			cout << "|" << setw(4) << i+1
				<< "|" << setw(13) << users[i].login
				<< "|" << setw(12) << users[i].password << "|" << endl;
		}
		cout << "---------------------------------" << endl << endl;
	}
	else {
		cout << "������������ �����������" << endl;
	}
}

int AddUser() {
	////////////////////////////////////////////////////// ������ �� �����
	User* users;
	cout << endl;
	int num = 0;
	ifstream in("users.txt");
	if (in.is_open()) { //������ ���������� ��������
		string str;
		while (!in.eof()) {
			getline(in, str, '\n');
			num++;
		}
	}
	int UsersQuantity = num - 1;
	users = new User[UsersQuantity + 2];
	in.close();
	ifstream iin("users.txt");
	for (int i = 0; i < UsersQuantity; i++) {
		users[i].Read(iin);
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] - 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] - 10;
		}
	}
	iin.close();
	//////////////////////////////////////////////////////////////// ����������
	User* users1;
	int UsersQuantity1 = UsersQuantity + 1;
	users1 = new User[UsersQuantity1];

	string login;
	string password;

	// �������f �� ������������� ������
	int cycle1 = 1;
	while (cycle1) {
		cout << "������� ����� ������������:" << endl;
		getchar();
		getline(cin, login);
		cin.ignore();
		int flag = 0;
		for (int i = 0; i < UsersQuantity; i++) {
			if (login == users[i].login) {
				cout << "������������ � ����� ������� ��� ����������." << endl;
				flag++;
			}
		}
		if (flag == 0) {
			cycle1 = 0;
		}
	}
	cout << "������� ������ ������������:" << endl;
	getline(cin, password);
	int i = 0;
	for (; i < UsersQuantity; i++) {
		users1[i] = users[i];
	}
	User n(login, password);
	users1[i] = n;

	UsersQuantity = UsersQuantity1;
	users = new User[UsersQuantity1];
	i = 0;
	for (; i < UsersQuantity; i++) {
		users[i] = users1[i];
	}
	/////////////////////////////////////////////////////////////// ������ � ����
	ofstream out;          // ����� ��� ������
	string file = "users.txt";
	out.open(file); // �������� ���� ��� ������

	for (int i = 0; i < UsersQuantity; i++) {
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] + 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] + 10;
		}
		users[i].Write(out);
	}
	out.close();
	//////////////////////////////////////////////////////////////
	return UsersQuantity;
}

int ChooseUser(int UsersQuantity) {
	int num;
	cout << "������� ���������� ����� ������������:" << endl;
	num = CreateInt();
	if (num > 0 && num <= UsersQuantity) {
		return num - 1;
	}
	else {
		cout << "������������ ����" << endl;
		return -1;
	}
}

void EditUser() {
	////////////////////////////////////////////////////// ������ �� �����
	User* users;
	cout << endl;
	int num = 0;
	ifstream in("users.txt");
	if (in.is_open()) { //������ ���������� ��������
		string str;
		while (!in.eof()) {
			getline(in, str, '\n');
			num++;
		}
	}
	int UsersQuantity = num - 1;
	users = new User[UsersQuantity + 2];
	in.close();
	ifstream iin("users.txt");
	for (int i = 0; i < UsersQuantity; i++) {
		users[i].Read(iin);
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] - 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] - 10;
		}
	}
	iin.close();
	int cycle = 1;
	int menu = 0;
	ShowUsers();////////////////////////////////////////////
	int choise = ChooseUser(UsersQuantity);
	if (choise>-1) {
		while (cycle) {
			cout << "�������� ����������� ��������:" << endl;
			cout << "1. ������������� ����� ������������" << endl;
			cout << "2. ������������� ������ ������������" << endl;
			cout << "3. �����" << endl;
			menu = CreateInt();
			switch (menu) {
			case 1: {
				string login;
				cout << "������� ����� �����: ";
				cin >> login;
				users[choise].SetLogin(login);
				break;
			}
			case 2: {
				string password;
				cout << "������� ����� ������: ";
				cin >> password;
				users[choise].SetPassword(password);
				break;
			}
			case 3: {
				cycle = 0;
				break;
			}
			default: {
				cout << "������������ ����" << endl;
				break;
			}
			}
		}
	}
	/////////////////////////////////////////////////////////////// ������ � ����
	ofstream out;          // ����� ��� ������
	string file = "users.txt";
	out.open(file); // �������� ���� ��� ������

	for (int i = 0; i < UsersQuantity; i++) {
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] + 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] + 10;
		}
		users[i].Write(out);
	}
	out.close();
}

int DeleteUser() {
	////////////////////////////////////////////////////// ������ �� �����
	User* users;
	cout << endl;
	int num = 0;
	ifstream in("users.txt");
	if (in.is_open()) { //������ ���������� ��������
		string str;
		while (!in.eof()) {
			getline(in, str, '\n');
			num++;
		}
	}
	int UsersQuantity = num - 1;
	users = new User[UsersQuantity + 2];
	in.close();
	ifstream iin("users.txt");
	for (int i = 0; i < UsersQuantity; i++) {
		users[i].Read(iin);
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] - 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] - 10;
		}
	}
	iin.close();
	ShowUsers();
	User* users1 = new User[UsersQuantity+2];
	if (UsersQuantity) {
		int choise = ChooseUser(UsersQuantity);
		if (choise>-1) {
			int i = 0, k = 0;
			for (; i < UsersQuantity; i++) {
				if (i != choise) {
					users1[k] = users[i];
					k++;
				}
			}
			UsersQuantity = UsersQuantity - 1;
			users = new User[UsersQuantity + 2];
			i = 0;
			for (; i < UsersQuantity; i++) {
				users[i] = users1[i];
			}
		}
	}
	/////////////////////////////////////////////////////////////// ������ � ����
	ofstream out;          // ����� ��� ������
	string file = "users.txt";
	out.open(file); // �������� ���� ��� ������

	for (int i = 0; i < UsersQuantity; i++) {
		for (int k = 0; k < users[i].login.length(); k++) {
			users[i].login[k] = users[i].login[k] + 10;
		}
		for (int k = 0; k < users[i].password.length(); k++) {
			users[i].password[k] = users[i].password[k] + 10;
		}
		users[i].Write(out);
	}
	out.close();
	return UsersQuantity;
}

int User::authorization(string fileName) {
	string log, pass;
		cout << "������� �����: ";
		cin >> log;
		cout << "������� ������: ";
		cin >> pass;
		for (int k = 0; k < log.length(); k++) {
			log[k] = log[k] + 10;
		}
		for (int k = 0; k < pass.length(); k++) {
			pass[k] = pass[k] + 10;
		}
		ifstream in(fileName);
		if (in.is_open())
		{
			while (getline(in, login, '-') && getline(in, password, '-'))
			{
				if (login == log && pass == password) {
					return 1; //���� ����������
				}
				in.get();
			}
		}
		in.close();
	return 0;
}