#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#include "Seat.h"

Seat::Seat() {
	available = true;
	row = 1;
	number = 1;
}

Seat::Seat(int row, int number) {
	available = true;
	this->row = row;
	this->number = number;
}

Seat::Seat(Seat& seat) {
	this->available = seat.available;
	this->row = seat.row;
	this->number = number;
}

void Seat:: operator=(Seat& newseat) {
	this->available = newseat.available;
	this->row = newseat.row;
	this->number = newseat.number;
}

void Seat::Print() {
	cout << "Ряд: " << row << endl;
	cout << "Место: " << number << endl;
}

void Seat::GetInfo() {
	Print();
	if (available) {
		cout << "свободно" << endl;
	}
	else {
		cout << "занято" << endl;
	}
}

bool Seat::isAvailable() { return available; }
int Seat::GetRow() { return row; }
int Seat::GetNumber() { return number; }
void Seat::Reserve() { available = false; }
void Seat::SetRow(int row) { this->row = row; }
void Seat::SetNumber(int num) { this->number = num; }

void Seat::Read(ifstream& in) {
	in >> row;
	in.get();
	in >> number;
	in.get();
	int ava;
	in >> ava;
	in.get();
	if (ava) {
		available = true;
	}
	else {
		available = false;
	}
}

void Seat::Write(ofstream& out) {
	int ava;
	if (available) {
		ava = 1;
	}
	else {
		ava = 0;
	}
	if (out.is_open())
	{
		out << row << "/" << number << "*" << ava << "-";
	}
	else {
		cout << "Error" << endl;
	}
}
