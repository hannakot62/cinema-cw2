class Seat {
private:
	bool available;
	int row;
	int number;
public:
	Seat();
	Seat(int row, int number);
	Seat(Seat& seat);
	void operator=(Seat& newseat);
	void Print();
	void GetInfo();
	bool isAvailable();
	int GetRow();
	int GetNumber();
	void Reserve();
	void SetRow(int row);
	void SetNumber(int num);

	void Read(ifstream& in);
	void Write(ofstream& out);

};