#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#include "Movie.h"
#include "funcs.h"
#include "MyTime.h"
#include "Seat.h"
#include "Session.h"
#include "Cinema.h"
using namespace MyNS;

//���������� ������� �����
template <class OBJECT, class PARAMETRARR>
void ShellSort(OBJECT* objects, PARAMETRARR* parametr, int size)
{
	int i, j, step;
	int tmp;
	OBJECT temp;
	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++)
		{
			tmp = parametr[i];
			temp = objects[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < parametr[j - step])
					objects[j] = objects[j - step];
				else
					break;
			}
			parametr[j] = tmp;
			objects[j] = temp;
		}
}

Cinema::Cinema() {
	name = "�������";
	SessionsQuantity = 1;
	sessions = new Session[SessionsQuantity];
	for (int i = 0; i < SessionsQuantity; i++) {
		Session s;
		sessions[i] = s;
	}
	moviesQuantity = 1;
	movies = new Movie[moviesQuantity];
	for (int i = 0; i < moviesQuantity; i++) {
		Movie m;
		movies[i] = m;
	}
}

Cinema::Cinema(int MQ) {
	name = "�������";
	moviesQuantity = MQ;
	movies = new Movie[moviesQuantity];
	for (int i = 0; i < moviesQuantity; i++) {
		string name, director;
		int AR;
		cout << "������� �������� ������: ";
		getchar();
		getline(cin, name);
		cout << "������� ��� ��������: ";
		getchar();
		getline(cin, director);
		cout << "������� ���������� �����������: ";
		AR = CreateInt();
		Movie mov(name, AR, director);
		movies[i] = mov;
	}
}

Cinema::Cinema(Cinema& cinema) {
	this->name = cinema.name;
	this->SessionsQuantity = cinema.SessionsQuantity;
	sessions = new Session[SessionsQuantity];
	for (int i = 0; i < SessionsQuantity; i++) {
		this->sessions[i] = cinema.sessions[i];
	}
	this->moviesQuantity = cinema.moviesQuantity;
	movies = new Movie[moviesQuantity];
	for (int i = 0; i < moviesQuantity; i++) {
		this->movies[i] = cinema.movies[i];
	}
}

void Cinema::operator=(Cinema& newcin) {
	this->name = newcin.name;
	this->SessionsQuantity = newcin.SessionsQuantity;
	sessions = new Session[SessionsQuantity];
	for (int i = 0; i < SessionsQuantity; i++) {
		this->sessions[i] = newcin.sessions[i];
	}
	this->moviesQuantity = newcin.moviesQuantity;
	movies = new Movie[moviesQuantity];
	for (int i = 0; i < moviesQuantity; i++) {
		this->movies[i] = newcin.movies[i];
	}
}

int Cinema::ChooseMovie() {
	int num;
	cout << "������� ���������� ����� ������:" << endl;
	num = CreateInt();
	if (num > 0 && num <= moviesQuantity) {
		return num - 1;
	}
	else {
		cout << "������������ ����" << endl;
		return -1;
	}
}

int Cinema::ChooseSession() {
	int num;
	cout << "������� ���������� ����� ������:" << endl;
	num = CreateInt();
	if (num > 0 && num <= SessionsQuantity) {
		return num - 1;
	}
	else {
		cout << "������������ ����" << endl;
		return -1;
	}
}

Movie* Cinema:: GetMovie(int choise) {
	return (&movies[choise]);
}

Session* Cinema::GetSession(int choise) {
	return (&sessions[choise]);
}

int Cinema::GetSessionsQuantity() {
	return SessionsQuantity;
}

int Cinema::GetMoviesQuantity() {
	return moviesQuantity;
}

void Cinema::ShowMovies() {
	if (moviesQuantity > 0) {
		int* arr;
		arr = new int[moviesQuantity];
		for (int i = 0; i < moviesQuantity; i++) {
			arr[i] = movies[i].GetAgeRestrictions();
		}
		ShellSort(movies, arr, moviesQuantity);
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "|����� �� �������|     ��������     |���������� �����������|     ��������    |" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < moviesQuantity; i++) {
			cout << "|" << setw(16) << i + 1 << "|" << setw(18) << movies[i].GetName() << "|" << setw(22) << movies[i].GetAgeRestrictions() << "|" << setw(17) << movies[i].GetDirector() << "|" << endl;
		}
		cout << "------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "������ �����������" << endl;
	}
}

void Cinema::ShowSessions() {
	if (SessionsQuantity > 0) {
		//��� ������� (����� �� ����, ����.���. ��� ����)
		int menu = 0, cycle = 1;
		while (cycle) {
			system("pause");
			system("cls");
			cout << "��� �� ������ ������� ������? �������� ����������� ��������:" << endl;
			cout << "1. ������������� �� ���� � �������" << endl;
			cout << "2. ������������� �� ���������� ������������" << endl;
			cout << "3. ������������� �� ����" << endl;
			menu = CreateInt();
			switch (menu) {
			case 1: {
				int* arr;
				arr = new int[SessionsQuantity];
				for (int i = 0; i < SessionsQuantity; i++) {
					arr[i] = sessions[i].GetTime()->GetMinutes() + sessions[i].GetTime()->GetHours() * 60 + sessions[i].GetTime()->GetDay() * 60 * 24 +
						sessions[i].GetTime()->GetMonth() * 60 * 24 * 30 + sessions[i].GetTime()->GetYear() * 60 * 24 * 30 * 365;
				}
				ShellSort(sessions, arr, SessionsQuantity);
				cycle = 0;
				break;
			}
			case 2: {
				int* arr;
				arr = new int[SessionsQuantity];
				for (int i = 0; i < SessionsQuantity; i++) {
					arr[i] = sessions[i].GetMovie()->GetAgeRestrictions();
				}
				ShellSort(sessions, arr, SessionsQuantity);
				cycle = 0;
				break;
			}
			case 3: {
				int* arr;
				arr = new int[SessionsQuantity];
				for (int i = 0; i < SessionsQuantity; i++) {
					arr[i] = sessions[i].GetPrice();
				}
				ShellSort(sessions, arr, SessionsQuantity);
				cycle = 0;
				break;
			}
			default: {
				cout << "������������ ����" << endl;
				break;
			}
			}
		}
		cout << "-----------------------------------------------------------------------------------------" << endl;
		cout << "|����� �� �������|     ��������     |���������� �����������|���� ������|  ���� � �����  |" << endl;
		cout << "-----------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < SessionsQuantity; i++) {
			cout << "|" << setw(16) << i + 1
				<< "|" << setw(18) << sessions[i].GetMovie()->GetName()
				<< "|" << setw(22) << sessions[i].GetMovie()->GetAgeRestrictions()
				<< "|" << setw(11) << sessions[i].GetPrice() << "|";
			sessions[i].GetTime()->ShowDate();
			cout << " ";
			sessions[i].GetTime()->ShowTime();
			cout << "|" << endl;
		}
		cout << "-----------------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "������ �����������" << endl;
	}
}

void Cinema::FileGetMovies() {
	int num = 0;
	ifstream in("movies.txt");
	if (in.is_open()) { //������ ���������� ��������
		string str;
		while (!in.eof()) {
			getline(in, str, '\n');
			num++;
		}
	}
	moviesQuantity = num - 1;
	movies = new Movie[moviesQuantity+2];
	in.close();
	ifstream iin("movies.txt");
	int i = 0;
	for (; i < moviesQuantity; i++) {
		movies[i].Read(iin);
		iin.get();
	}
	iin.close();
}


void Cinema::FileGetSessions() {
	int num = 0;
	ifstream in("sessions.txt");
	if (in.is_open()) { //������ ���������� ��������
		string str;
		while (!in.eof()) {
			getline(in, str, '\n');
			num++;
		}
	}
	SessionsQuantity = num - 1;
	sessions = new Session[SessionsQuantity + 2];
	in.close();
	ifstream iin("sessions.txt");
	for (int i = 0; i < SessionsQuantity; i++) {
		sessions[i].Read(iin);
	}
	iin.close();
}

void Cinema::FileSetMovies() {
	ofstream out;          // ����� ��� ������
	string file = "movies.txt";
	out.open(file); // �������� ���� ��� ������
	for (int i = 0; i < moviesQuantity; i++) {
		if (out.is_open())
		{
			movies[i].Write(out);
			out << endl;
		}
		else {
			cout << "Error" << endl;
		}
	}
	out.close();
}

void Cinema::FileSetSessions() {
	ofstream out;          // ����� ��� ������
	string file = "sessions.txt";
	out.open(file); // �������� ���� ��� ������
	for (int i = 0; i < SessionsQuantity; i++) {
		if (out.is_open())
		{
			sessions[i].Write(out);
		}
		else {
			cout << "Error" << endl;
		}
	}
	out.close();
}

void Cinema::AddMovie() {
	Movie* movies1;
	int movieQuantity1 = moviesQuantity + 1;
	movies1 = new Movie[movieQuantity1];

	string name;
	string director;
	int AgeRestrictions;

	cout << "������� �������� ������:" << endl;
	getchar();
	getline(cin, name);
	cin.ignore();
	cout << "������� �������� ������:" << endl;
	getline(cin, director);
	cout << "������� ���������� �����������:" << endl;
	AgeRestrictions = CreateInt();
	int i = 0;
	for (; i < moviesQuantity; i++) {
		movies1[i] = movies[i];
	}
	Movie n(name, AgeRestrictions, director);
	movies1[i] = n;

	moviesQuantity = movieQuantity1;
	movies = new Movie[movieQuantity1];
	i = 0;
	for (; i < moviesQuantity; i++) {
		movies[i] = movies1[i];
	}
}

void Cinema::AddSessionAction(Movie mov) {
	Session* sessions1;
	int sessionsQuantity1 = SessionsQuantity + 1;
	sessions1 = new Session[sessionsQuantity1];

	int price;
	cout << "������� ���� ������:" << endl;
	price = CreateInt();
	Date date(*CreateDate());
	Time sestime (*CreateTime(date));
	int i = 0;
	for (; i < SessionsQuantity; i++) {
		sessions1[i] = sessions[i];
	}
	Session n(mov, sestime, price);
	sessions1[i] = n;

	SessionsQuantity = sessionsQuantity1;
	sessions = new Session[sessionsQuantity1];
	i = 0;
	for (; i < SessionsQuantity; i++) {
		sessions[i] = sessions1[i];
	}
}

void Cinema::AddSession() {
	int choise;
	cout << "�������� ����������� ��������:" << endl;
	cout << "1. �������� ����� ��� ������������� ������" << endl;
	cout << "2. �������� ����� ��� ������ ������" << endl;
	choise = CreateInt();
	switch (choise) {
	case 1: {
		ShowMovies();
		if (moviesQuantity > 0) {
			int choise = ChooseMovie();
			if (choise >= 0) {
				AddSessionAction(*GetMovie(choise));
			}
		}
		break;
	}
	case 2: {
		AddMovie();
		AddSessionAction(movies[moviesQuantity-1]);
		break;
	}
	default: {
		cout << "������������ ����" << endl;
		break;
	}
	}
}

void Cinema::EditMovie(Movie& mov) {
	int cycle = 1;
	int menu = 0;
	while (cycle) {
		cout << "�������� ����������� ��������:" << endl;
		cout << "1. ������������� �������� ������" << endl;
		cout << "2. ������������� ��������� ������" << endl;
		cout << "3. ������������� ��������� ����������� ������" << endl;
		cout << "4. �����" << endl;
		menu = CreateInt();
		switch (menu) {
		case 1: {
			string name;
			cout << "������� ����� ��������: ";
			getchar();
			getline(cin, name);
			mov.SetName(name);
			break;
		}
		case 2: {
			string director;
			cout << "������� ����� ��� ���������: ";
			getchar();
			getline(cin, director);
			mov.SetDirector(director);
			break;
		}
		case 3: {
			int ar;
			cout << "������� ����� ���������� �����������: ";
			ar = CreateInt();
			mov.SetAgeRestrictions(ar);
			break;
		}
		case 4: {
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


void Cinema::EditSession(Session& ses) {
	int cycle = 1;
	int menu = 0;
	while (cycle) {
		cout << "�������� ����������� ��������:" << endl;
		cout << "1. ������������� ������ � ������" << endl;
		cout << "2. ������������� ����� ������" << endl;
		cout << "3. ������������� ���� ������ �� �����" << endl;
		cout << "4. �����" << endl;
		menu = CreateInt();
		switch (menu) {
		case 1: {
			EditMovie(*ses.GetMovie());
			break;
		}
		case 2: {
			ses.EditTime();
			break;
		}
		case 3: {
			int pr;
			cout << "������� ����� ���� ������ �� �����: ";
			pr = CreateInt();
			ses.SetPrice(pr);
			break;
		}
		case 4: {
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

void Cinema::FilterAR() {
	int a = -1;
	int b = -1;
	cout << "������� ������� ����������:" << endl<< "�� ";
	a = CreateInt();
	cout << "�� ";
	b = CreateInt();
	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	int counter = 0;
	for (int i = 0; i < moviesQuantity; i++)
	{
		if (movies[i].GetAgeRestrictions() >= a && movies[i].GetAgeRestrictions() <= b)
		{
			cout << endl;
			cout << counter + 1 << ". ";
			movies[i].GetInfo();
			cout << endl;
			counter++;
		}
	}
	if (counter == 0)
	{
		cout << "����� ������ �� �������" << endl;
		system("pause");
	}
}

void Cinema::SearchSessionWithMovieName() { 
	string movN;
	cout << "������� �������� ������" << endl;
	getchar();
	getline(cin, movN);
	int counter = 0;
	for (int i = 0; i < SessionsQuantity; i++)
	{
		if ((sessions[i].GetMovie()->GetName())==movN)
		{
			sessions[i].GetInfo();
			counter++;
		}
	}
	if (counter == 0)
	{
		cout << "������� � ������ ������� �� �������" << endl;
		system("pause");
	}
}

void Cinema::BuyTicket() {
	ShowSessions();
	if (GetSessionsQuantity() > 0) {
		int choise = ChooseSession();
		if (choise >= 0) {
			GetSession(choise)->GetInfo();
			GetSession(choise)->BuyTicket();
		}
	}
}

void Cinema::DeleteSession() {
	ShowSessions();
	Session* sessions1 = new Session[SessionsQuantity];
	cout << "������� ����� ������ ��� ��������:" << endl;
	int num;
	num = CreateInt();
	if (num<1 || num>SessionsQuantity) {
		cout << "������ ������ ���" << endl;
	}
	else {
		int del = num - 1;
		int i = 0, k = 0;
		for (; i < SessionsQuantity; i++) {
			if (i != del) {
				sessions1[k] = sessions[i];
				k++;
			}
		}
		SessionsQuantity = SessionsQuantity - 1;
		sessions = new Session[SessionsQuantity+2];
		i = 0;
		for (; i < SessionsQuantity; i++) {
			sessions[i] = sessions1[i];
		}
	}
}

void Cinema::CinemaInfo() {
	cout << endl;
	cout << "��������� - ������������ ������ ��� ��� ����� � �������������" <<
		endl << "��� ��������� ������������ ����������� �� ������� ������." << endl << endl;
	cout << "���������� ���� � ��������: "<<SeatsQuantity<<endl<<endl;
}
