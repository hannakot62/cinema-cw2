#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#include "funcs.h"
#include "MyTime.h"
#include "Movie.h"
#include "Seat.h"
#include "Session.h"
using namespace MyNS;


Session::Session() {
	price = 5;
	Movie m("Челюсти", 18, "Стивен Спилберг");
	movie = m;
	Time t(21, 30);
	time = t;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Seat s(i + 1, j + 1);
			seats[i][j] = s;
		}
	}
}

Session::Session(Movie movie, Time time, int price) {
	this->price = price;
	this->movie = movie;
	this->time = time;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Seat s(i + 1, j + 1);
			seats[i][j] = s;
		}
	}
}

Session::Session(Session& session) {
	this->price = session.price;
	this->movie = session.movie;
	this->time = session.time;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			seats[i][j] = session.seats[i][j];
		}
	}
}

void Session::operator=(Session& newses) {
	this->price = newses.price;
	this->movie = newses.movie;
	this->time = newses.time;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->seats[i][j] = newses.seats[i][j];
		}
	}
}

void Session::GetInfo() {
	cout << endl;
	movie.GetInfo();
	cout << "Дата: ";
	time.ShowDate();
	cout << endl;
	cout << "Время: ";
	time.ShowTime();
	cout << endl;
	cout << "Цена билета на сеанс: " << price << endl;
	ShowSeats();
}

void Session::ShowSeats() {
	cout << "----------------------------------------------------" << endl;
	cout << "                 Экран                 " << endl;
	cout << "               *********               " << endl << endl;
	for (int i = 0; i < 10; i++) {
		int j = 0;
		for (; j < 10; j++) {
			cout << seats[i][j].GetNumber();
			if (seats[i][j].isAvailable()) {
				cout << "   ";
			}
			else {
				cout << "*  ";
			}
		}
		cout << " -  ряд " << seats[i][j-1].GetRow() << endl;
	}
	cout << "----------------------------------------------------" << endl;
	cout << "* - место забронировано" << endl << endl;
}

int Session::GetPrice() { return price; }
void Session::SetPrice(int price) { this->price = price; }
Movie* Session::GetMovie() { return &movie; }
Time* Session::GetTime() { return &time; }
Seat* Session::GetSeat(int r, int num) { return &seats[r - 1][num - 1]; }
void Session::SetMovie(Movie movie) { this->movie = movie; }
void Session::SetTime(Time time) { this->time = time; }

void Session::Read(ifstream& in) {
	movie.Read(in);
	time.Read(in);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j<10; j++) {
			seats[i][j].Read(in);
		}
	}
	in >> price;
	in.get();
}

void Session::Write(ofstream& out) {
	if (out.is_open())
	{
		movie.Write(out);
		time.Write(out);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				seats[i][j].Write(out);
			}
		}
		out << price << endl;
	}
	else {
		cout << "Error" << endl;
	}
}

void Session::EditTime() {
	Date d(*CreateDate());
	Time t (*CreateTime(d));
	time = t;
}

void Session::BuyTicket() {
	cout << "Введите ряд: ";
	int row = 11;
	while (row > 10 || row < 1) {
		row = CreateInt();
		if (row > 10 || row < 1) {
			cout << "Номер ряда введен некорректно" << endl;
		}
	}
	int num = 11;
	cout << "Введите место: ";
	while (num > 10 || num < 1) {
		num = CreateInt();
		if (num > 10 || num < 1) {
			cout << "Номер места введен некорректно" << endl;
		}
	}
	if (seats[row - 1][num - 1].isAvailable()) {
		seats[row - 1][num - 1].Reserve();
	}
	else {
		cout << "Это место уже зарезервировано" << endl;
	}
}