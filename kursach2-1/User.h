class User {
private:
	string login;
	string password;
public:
	User();
	User(string login, string password);
	string GetLogin();
	string GetPassword();
	void SetLogin(string login);
	void SetPassword(string password);

	void Write(ofstream& out);
	void Read(ifstream& in);

	friend void FileSetUsers(int UsersQuantity, User* users);
	friend int FileGetUsers();
	friend void ShowUsers();
	friend int AddUser();
	friend int ChooseUser(int UsersQuantity);
	friend void EditUser();
	friend int DeleteUser();

	int authorization(string fileName);

};

void FileSetUsers(int UsersQuantity, User* users);
int FileGetUsers();
void ShowUsers();
int AddUser();
int ChooseUser(int UsersQuantity);
void EditUser();
int DeleteUser();