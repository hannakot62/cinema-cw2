#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#include "MyTime.h"
#include "Movie.h"
#include "Seat.h"
#include"Session.h"
#include "Cinema.h"

#include "funcs.h"

namespace MyNS {
	int CheckInt(char c[])
	{
		for (int i = 0; i < strlen(c); i++)
		{
			if (c[i] > '9' || c[i] < '0')
			{
				return 0;//это не целое число
			}
		}
		return 1;//это целое число
	}

	int CreateInt()
	{
		char str[70] = "a";//заведомо ложное условие (не целое число)
		while (!CheckInt(str))
		{
			cin >> str;
			if (!CheckInt(str))
			{
				printf("Ќекорректный ввод.\n");
			}
		}
		int n = atoi(str);//перевод в целочисленный формат
		return n;
	}

}
