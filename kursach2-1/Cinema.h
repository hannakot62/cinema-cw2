class Cinema {
private:
	string name;
	Session* sessions;
	int SessionsQuantity;
	Movie* movies;
	int moviesQuantity;
public:
	const static int SeatsQuantity = 100;

	Cinema();
	Cinema(int MQ);
	Cinema(Cinema& cinema);
	void operator=(Cinema& newcin);
	int ChooseMovie();
	int ChooseSession();
	Movie* GetMovie(int choise);
	Session* GetSession(int choise);
	int GetSessionsQuantity();
	int GetMoviesQuantity();

	void ShowMovies();
	void ShowSessions();

	void FileGetMovies();
	void FileGetSessions();
	void FileSetMovies();
	void FileSetSessions();

	void AddMovie();
	void AddSession();
	void AddSessionAction(Movie mov);

	void EditMovie(Movie& mov);
	void EditSession(Session& ses);

	void FilterAR();
	void SearchSessionWithMovieName();

	void BuyTicket();

	void DeleteSession();

	static void CinemaInfo();
};

template <class OBJECT, class PARAMETRARR>
void ShellSort(OBJECT* objects, PARAMETRARR* parametr, int size);

