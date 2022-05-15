class Movie {
private:
	string name;
	int AgeRestrictions;
	string director;
public:
	Movie();
	Movie(string name, int AR, string director);
	Movie(Movie& movie);
	void operator=(Movie& newmovie);
	void GetInfo();
	string GetName();
	int GetAgeRestrictions();
	string GetDirector();
	void SetName(string name);
	void SetAgeRestrictions(int AR);
	void SetDirector(string director);

	void Read(ifstream& in);
	void Write(ofstream& out);

};