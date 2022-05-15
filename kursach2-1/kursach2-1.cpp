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
#include "Cinema.h"
#include "User.h"
using namespace MyNS;

template <class T>
class Menu {
protected:
	T type;
public:
	Menu(T type) : type(type) {}

	virtual void PrintMenu() = 0;
};

void UserManagementMenu();

template <class T>
class AdminMenu : public Menu<T>
{
public:
	AdminMenu(T type) : Menu<T>(type) {}
	void PrintMenu() override {
		{
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			int menu = 0;
			int cycle = 1;
			Cinema cinema;
			cinema.FileGetMovies();
			cinema.FileGetSessions();
			while (cycle) {
				system("pause");
				system("cls");
				cout << "Выберите необходимое действие:" << endl;
				cout << "1. Добавить фильм" << endl;
				cout << "2. Добавить сеанс" << endl;
				cout << "3. Вывести список фильмов" << endl;
				cout << "4. Вывести список сеансов" << endl;
				cout << "5. Вывести информацию о выбранном сеансе" << endl;
				cout << "6. Редактировать данные о выбранном фильме" << endl;
				cout << "7. Редактировать данные о выбранном сеансе" << endl;
				cout << "8. Фильтрация фильмов по возрастным ограничениям" << endl;
				cout << "9. Поиск сеансов по названию фильма" << endl;
				cout << "10. Удалить сеанс" << endl;
				cout << "11. Работа с пользователями" << endl;
				cout << "12. Выход" << endl;
				menu = CreateInt();
				switch (menu) {
				case 1: {
					cinema.AddMovie();
					break;
				}
				case 2: {
					cinema.AddSession();
					break;
				}
				case 3: {
					cinema.ShowMovies();
					break;
				}
				case 4: {
					cinema.ShowSessions();
					break;
				}
				case 5: {
					if (cinema.GetSessionsQuantity() > 0) {
						cinema.ShowSessions();
						int choise = cinema.ChooseSession();
						if (choise >= 0) {
							cinema.GetSession(choise)->GetInfo();
						}
					}
					break;
				}
				case 6: {
					cinema.ShowMovies();
					if (cinema.GetMoviesQuantity() > 0) {
						int choise = cinema.ChooseMovie();
						if (choise >= 0) {
							cinema.EditMovie(*cinema.GetMovie(choise));
						}
					}
					break;
				}
				case 7: {
					cinema.ShowSessions();
					if (cinema.GetSessionsQuantity() > 0) {
						int choise = cinema.ChooseSession();
						if (choise >= 0) {
							cinema.EditSession(*cinema.GetSession(choise));
						}
					}
					break;
				}
				case 8: {
					cinema.FilterAR();
					break;
				}
				case 9: {
					cinema.SearchSessionWithMovieName();
					break;
				}
				case 10: {
					cinema.DeleteSession();
					break;
				}
				case 11: {
					UserManagementMenu();
					break;
				}
				case 12: {
					cycle = 0;
					break;
				}
				default: {
					cout << "Некорректный ввод" << endl;
					break;
				}
				}
			}
			cinema.FileSetMovies();
			cinema.FileSetSessions();
		}
	};
};

template <class T>
class UserMenu : public Menu<T>
{
public:
	UserMenu(T type) : Menu<T>(type) {}
	void PrintMenu() override
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		int menu = 0;
		int cycle = 1;
		Cinema::CinemaInfo();
		Cinema cinema;
		cinema.FileGetMovies();
		cinema.FileGetSessions();
		while (cycle) {
			system("pause");
			system("cls");
			cout << "Выберите необходимое действие:" << endl;
			cout << "1. Вывести список фильмов" << endl;
			cout << "2. Вывести список сеансов" << endl;
			cout << "3. Вывести информацию о выбранном сеансе" << endl;
			cout << "4. Вывести информацию о выбранном фильме" << endl;
			cout << "5. Фильтрация фильмов по возрастным ограничениям" << endl;
			cout << "6. Поиск сеансов по названию фильма" << endl;
			cout << "7. Бронирование билета на сеанс" << endl;
			cout << "8. Выход" << endl;
			menu = CreateInt();
			switch (menu) {
			case 1: {
				cinema.ShowMovies();
				break;
			}
			case 2: {
				cinema.ShowSessions();
				break;
			}
			case 3: {
				cinema.ShowSessions();
				if (cinema.GetSessionsQuantity() > 0) {
					int choise = cinema.ChooseSession();
					if (choise >= 0) {
						cinema.GetSession(choise)->GetInfo();
					}
				}
				break;
			}
			case 4: {
				cinema.ShowMovies();
				if (cinema.GetMoviesQuantity() > 0) {
					int choise = cinema.ChooseMovie();
					if (choise >= 0) {
						cinema.GetMovie(choise)->GetInfo();
					}
				}
				break;
			}
			case 5: {
				cinema.FilterAR();
				break;
			}
			case 6: {
				cinema.SearchSessionWithMovieName();
				break;
			}
			case 7: {
				cinema.BuyTicket();
				break;
			}
			case 8: {
				cycle = 0;
				break;
			}
			default: {
				cout << "Некорректный ввод" << endl;
				break;
			}
			}
		}
		cinema.FileSetMovies();
		cinema.FileSetSessions();
	}
};


int main() {
	User ActiveUser;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int menu = 0;
	int cycle = 1;
	while (cycle) {
		system("pause");
		system("cls");
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Войти в качестве пользователя" << endl;
		cout << "2. Войти в качестве администратора" << endl;
		cout << "3. Зарегистрироваться в качестве пользователя" << endl;
		cout << "4. Выход" << endl;
		menu = CreateInt();
		switch (menu) {
		case 1: {
			int go = ActiveUser.authorization("users.txt");
			if (go) {
				cout << "Вы вошли в качестве пользователя" << endl;
				User u;
				UserMenu<User> a(u);
				a.PrintMenu();
			}
			else {
				cout << "Неправильно введены логин и/или пароль" << endl;
			}
			break;
		}
		case 2: {
			int go = ActiveUser.authorization("admin.txt");
			if (go) {
				cout << "Вы вошли в качестве администратора" << endl;
				User u;
				AdminMenu<User> a(u);
				a.PrintMenu();
			}
			else {
				cout << "Неправильно введены логин и/или пароль" << endl;
			}
			break;
		}
		case 3: {
			AddUser();
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

void UserManagementMenu() {
	int menu = 0;
	int cycle = 1;
	int UsersQuantity = FileGetUsers();
	while (cycle) {
		system("pause");
		system("cls");
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Просмотреть информацию о пользователях" << endl;
		cout << "2. Добавить пользователя" << endl;
		cout << "3. Редактировать пользователя" << endl;
		cout << "4. Удалить пользователя" << endl;
		cout << "5. Выход" << endl;
		menu = CreateInt();
		switch (menu) {
		case 1: {
				ShowUsers();
			break;
		}
		case 2: {
			UsersQuantity = AddUser();
			break;
		}
		case 3: {
			if (UsersQuantity)
				EditUser();
			else {
				cout << "Пользователи отсутствуют" << endl;
			}
			break;
		}
		case 4: {
			if (UsersQuantity)
				DeleteUser();
			else {
				cout << "Пользователи отсутствуют" << endl;
			}
			break;
		}
		case 5: {
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

