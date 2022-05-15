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
				return 0;//��� �� ����� �����
			}
		}
		return 1;//��� ����� �����
	}

	int CreateInt()
	{
		char str[70] = "a";//�������� ������ ������� (�� ����� �����)
		while (!CheckInt(str))
		{
			cin >> str;
			if (!CheckInt(str))
			{
				printf("������������ ����.\n");
			}
		}
		int n = atoi(str);//������� � ������������� ������
		return n;
	}

}
