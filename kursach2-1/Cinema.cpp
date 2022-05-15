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

//сортировка методом Шелла
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
	name = "Октябрь";
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
	name = "Октябрь";
	moviesQuantity = MQ;
	movies = new Movie[moviesQuantity];
	for (int i = 0; i < moviesQuantity; i++) {
		string name, director;
		int AR;
		cout << "Введите название фильма: ";
		getchar();
		getline(cin, name);
		cout << "Введите имя режиссёра: ";
		getchar();
		getline(cin, director);
		cout << "Введите возрастные ограничения: ";
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
	cout << "Введите порядковый номер фильма:" << endl;
	num = CreateInt();
	if (num > 0 && num <= moviesQuantity) {
		return num - 1;
	}
	else {
		cout << "Некорректный ввод" << endl;
		return -1;
	}
}

int Cinema::ChooseSession() {
	int num;
	cout << "Введите порядковый номер сеанса:" << endl;
	num = CreateInt();
	if (num > 0 && num <= SessionsQuantity) {
		return num - 1;
	}
	else {
		cout << "Некорректный ввод" << endl;
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
		cout << "|Номер по порядку|     Название     |Возрастные ограничения|     Режиссер    |" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < moviesQuantity; i++) {
			cout << "|" << setw(16) << i + 1 << "|" << setw(18) << movies[i].GetName() << "|" << setw(22) << movies[i].GetAgeRestrictions() << "|" << setw(17) << movies[i].GetDirector() << "|" << endl;
		}
		cout << "------------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "Фильмы отсутствуют" << endl;
	}
}

void Cinema::ShowSessions() {
	if (SessionsQuantity > 0) {
		//как вывести (сортю по дате, возр.огр. или цене)
		int menu = 0, cycle = 1;
		while (cycle) {
			system("pause");
			system("cls");
			cout << "Как Вы хотите вывести сеансы? Выберите необходимое действие:" << endl;
			cout << "1. Отсортировать по дате и времени" << endl;
			cout << "2. Отсортировать по возрастным ограничениям" << endl;
			cout << "3. Отсортировать по цене" << endl;
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
				cout << "Некорректный ввод" << endl;
				break;
			}
			}
		}
		cout << "-----------------------------------------------------------------------------------------" << endl;
		cout << "|Номер по порядку|     Название     |Возрастные ограничения|Цена билета|  Дата и время  |" << endl;
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
		cout << "Сеансы отсутствуют" << endl;
	}
}

void Cinema::FileGetMovies() {
	int num = 0;
	ifstream in("movies.txt");
	if (in.is_open()) { //узнаем количество объектов
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
	if (in.is_open()) { //узнаем количество объектов
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
	ofstream out;          // поток для записи
	string file = "movies.txt";
	out.open(file); // окрываем файл для записи
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
	ofstream out;          // поток для записи
	string file = "sessions.txt";
	out.open(file); // окрываем файл для записи
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

	cout << "Введите название фильма:" << endl;
	getchar();
	getline(cin, name);
	cin.ignore();
	cout << "Введите режиссёра фильма:" << endl;
	getline(cin, director);
	cout << "Введите возрастные ограничения:" << endl;
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
	cout << "Введите цену билета:" << endl;
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
	cout << "Выберите необходимое действие:" << endl;
	cout << "1. Добавить сеанс для существующего фильма" << endl;
	cout << "2. Добавить сеанс для нового фильма" << endl;
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
		cout << "Некорректный ввод" << endl;
		break;
	}
	}
}

void Cinema::EditMovie(Movie& mov) {
	int cycle = 1;
	int menu = 0;
	while (cycle) {
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Редактировать название фильма" << endl;
		cout << "2. Редактировать режиссера фильма" << endl;
		cout << "3. Редактировать возратные ограничения фильма" << endl;
		cout << "4. Выход" << endl;
		menu = CreateInt();
		switch (menu) {
		case 1: {
			string name;
			cout << "Введите новое название: ";
			getchar();
			getline(cin, name);
			mov.SetName(name);
			break;
		}
		case 2: {
			string director;
			cout << "Введите новое имя режиссера: ";
			getchar();
			getline(cin, director);
			mov.SetDirector(director);
			break;
		}
		case 3: {
			int ar;
			cout << "Введите новые возрастные ограничения: ";
			ar = CreateInt();
			mov.SetAgeRestrictions(ar);
			break;
		}
		case 4: {
			cycle = 0;
			break;
		}
		default: {
			cout << "Некорректный ввод" << endl;
			break;
		}
		}
	}
}


void Cinema::EditSession(Session& ses) {
	int cycle = 1;
	int menu = 0;
	while (cycle) {
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Редактировать данные о фильме" << endl;
		cout << "2. Редактировать время сеанса" << endl;
		cout << "3. Редактировать цену билета на сеанс" << endl;
		cout << "4. Выход" << endl;
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
			cout << "Введите новую цену билета на сеанс: ";
			pr = CreateInt();
			ses.SetPrice(pr);
			break;
		}
		case 4: {
			cycle = 0;
			break;
		}
		default: {
			cout << "Некорректный ввод" << endl;
			break;
		}
		}
	}
}

void Cinema::FilterAR() {
	int a = -1;
	int b = -1;
	cout << "Введите границы фильтрации:" << endl<< "От ";
	a = CreateInt();
	cout << "До ";
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
		cout << "Такие фильмы не найдены" << endl;
		system("pause");
	}
}

void Cinema::SearchSessionWithMovieName() { 
	string movN;
	cout << "Введите название фильма" << endl;
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
		cout << "Сеансов с данным фильмом не найдено" << endl;
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
	cout << "Введите номер сеанса для удаления:" << endl;
	int num;
	num = CreateInt();
	if (num<1 || num>SessionsQuantity) {
		cout << "Такого сеанса нет" << endl;
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
	cout << "Кинотеатр - общественное здание или его часть с оборудованием" <<
		endl << "для публичной демонстрации кинофильмов на большом экране." << endl << endl;
	cout << "Количество мест в кинозале: "<<SeatsQuantity<<endl<<endl;
}
