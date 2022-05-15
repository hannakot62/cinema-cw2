#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#include "Movie.h"

Movie::Movie() {
	name = "Титаник";
	AgeRestrictions = 16;
	director = "Джеймс Кэмерон";
}

Movie::Movie(string name, int AR, string director) {
	this->name = name;
	this->AgeRestrictions = AR;
	this->director = director;
}

Movie::Movie(Movie& movie) {
	this->name = movie.name;
	this->AgeRestrictions = movie.AgeRestrictions;
	this->director = movie.director;
}

void Movie:: operator=(Movie& newmovie) {
	this->name = newmovie.GetName();
	this->AgeRestrictions = newmovie.GetAgeRestrictions();
	this->director = newmovie.GetDirector();
}

void Movie::GetInfo() {
	cout << "Название фильма: " << name << endl;
	cout << "Режиссёр фильма: " << director << endl;
	cout << "Возрастные ограничения для просмотра: " << AgeRestrictions << endl;
}

string Movie::GetName() { return name; }
int Movie::GetAgeRestrictions() { return AgeRestrictions; }
string Movie::GetDirector() { return director; }
void Movie::SetName(string name) { this->name = name; }
void Movie::SetAgeRestrictions(int AR) { this->AgeRestrictions = AR; }
void Movie::SetDirector(string director) { this->director = director; }

void Movie::Read(ifstream& in) {
	getline(in, name, '-');
	in >> AgeRestrictions;
	in.get();
	getline(in, director, '-');
}

void Movie::Write(ofstream& out) {
	if (out.is_open())
	{
		out << name << "-" << AgeRestrictions << "-" << director << "-";
	}
	else {
		cout << "Error" << endl;
	}
}