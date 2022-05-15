#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#include "funcs.h"
#include "MyTime.h"
using namespace MyNS;

Date::Date() {
	year = 2021;
	month = 12;
	day = 1;
}

Date::Date(int d, int m, int y) {
	year = y;
	month = m;
	day = d;
}

Date::Date(Date& date) {
	this->year = date.year;
	this->month = date.month;
	this->day = date.day;
}

void Date::operator=(Date& newDate) {
	this->year = newDate.year;
	this->month = newDate.month;
	this->day = newDate.day;
}

void Date::ShowDate() {
	cout <<(day>9? "":"0")<< day << "." << (month > 9 ? "" : "0")<< month << "." << year;
}

int Date::GetYear() { return year; }
int Date::GetMonth() { return month; }
int Date::GetDay() { return day; }
void Date::SetYear(int y) { this->year = y; }
void Date::SetMonth(int m) { this->month = m; }
void Date::SetDay(int d) { this->day = d; }

////////////////////////////////////////////////////////////////////////////////

Time::Time() {
	hours = 12;
	minutes = 0;
}

Time::Time(int h, int m) {
	hours = h;
	minutes = m;
}

Time::Time(int d, int m, int y, int h, int min) {
	year = y;
	month = m;
	day = d;
	hours = h;
	minutes = min;
}

Time::Time(Time& time) : Date(time) {
	this->hours = time.hours;
	this->minutes = time.minutes;
}

void Time:: operator=(Time& newtime) {
	Date::operator=(newtime);
	this->hours = newtime.hours;
	this->minutes = newtime.minutes;
}

void Time::ShowTime() {
	cout << (hours > 9 ? "" : "0") << hours << ":" << (minutes > 9 ? "" : "0") << minutes;
}

int Time::GetHours() { return hours; }
int Time::GetMinutes() { return minutes; }
void Time::SetHours(int h) { this->hours = h; }
void Time::SetMinutes(int m) { this->minutes = m; }

void Time::Read(ifstream& in) {
	in >> day;
	in.get();
	in >> month;
	in.get();
	in >> year;
	in.get();
	in >> hours;
	in.get();
	in >> minutes;
	in.get();
}

void Time::Write(ofstream& out) {
	if (out.is_open())
	{
		out << day << "." << month << "." << year << "-" << hours << ":" << minutes << "-";
	}
	else {
		cout << "Error" << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
Date* CreateDate() {
	int d, m, y;
	bool correct = false;
	while (!correct) {
		cout << "Введите день : ";
		d = CreateInt();
		cout << "Введите месяц : ";
		m = CreateInt();
		cout << "Введите год : ";
		y = CreateInt();
		if (d > 31 || d < 1 || m < 1 || m>12 || y < 2021 || y>2023 || (d > 28 && m == 2)) {
			cout << "Некорректный ввод" << endl;
		}
		else {
			correct = true;
		}
	}
	Date date(d, m, y);
	return &date;
}

Time* CreateTime(Date& date) {
	int h, m;
	bool correct = false;
	while (!correct) {
		cout << "Введите часы : ";
		h = CreateInt();
		cout << "Введите минуты : ";
		m = CreateInt();
		if (h < 0 || h>23 || m < 0 || m>59) {
			cout << "Некорректный ввод" << endl;
		}
		else {
			correct = true;
		}
	}
	Time time(date.GetDay(), date.GetMonth(), date.GetYear(), h, m);
	return &time;
}