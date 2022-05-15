class Date {
protected:
	int year;
	int month;
	int day;
public:
	Date();
	Date(int d, int m, int y);
	Date(Date& date);
	void operator=(Date& newDate);
	void ShowDate();
	int GetYear();
	int GetMonth();
	int GetDay();
	void SetYear(int y);
	void SetMonth(int m);
	void SetDay(int d);
};

class Time : public Date {
private:
	int hours;
	int minutes;
public:
	Time();
	Time(int h, int m);
	Time(int d, int m, int y, int h, int min);
	Time(Time& time);
	void operator=(Time& newtime);
	void ShowTime();
	int GetHours();
	int GetMinutes();
	void SetHours(int h);
	void SetMinutes(int m);

	void Read(ifstream& in);
	void Write(ofstream& out);
};

Date* CreateDate();
Time* CreateTime(Date& date);