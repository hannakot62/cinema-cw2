class Session {
private:
	int price;
	Movie movie;
	Time time;
	Seat seats[10][10];// ряд номер
public:
	Session();
	Session(Movie movie, Time time, int price);
	Session(Session& session);
	void operator=(Session& newses);
	void GetInfo();
	void ShowSeats();
	int GetPrice();
	void SetPrice(int price);
	Movie* GetMovie();
	Time* GetTime();
	Seat* GetSeat(int r, int num);
	void SetMovie(Movie movie);
	void SetTime(Time time);

	void Read(ifstream& in);
	void Write(ofstream& out);

	void EditTime();

	void BuyTicket();
};