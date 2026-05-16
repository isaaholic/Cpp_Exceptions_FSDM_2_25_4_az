#include <iostream>

using namespace std;

// Database elave olunsun
void deleteUserById(const int& id);//eger bele bir id istifadechi yoxdursa exception atilsin
void hashUserDataById(const int& id);//gonderilen id deki istifadechinin butun melumatlari hash olunsun(string olanlar)digerleri qalsin


class Exception {}; // text, line, source, time. //cari vaxti alinmasini internetden arashdirin
class DatabaseException : public Exception {};
class InvalidArgumentException : public Exception {};


class User {
	int id;
	string username;
	string password;
	string name;
	string surname;

public:
	void show() const;
};

class Database {
	User** users;
	int user_count = 0;
public:
	void addUser(const User& user);
	User& getUserByUsername(string username);
	void updateUser(User& olduser, const User& newuser);
};



class Registration {
	Database _database;
public:
	Registration(const Database& database) {
		_database = database;
	}


	//eger bu username istifadechi yoxdursa error atsin
	//eger username varsa amma password yanlishdirsa error atsin
	void signIn(string username, string password);


	//Eger istifadechi varsa hemen username de throw DatabaseException
	//Eger username xarakter sayi 6 dan kichikdirse InvalidArgumentException
	//Eger usernamde boyuk herf vardirsa InvalidArgumentException
	//Eger password xarakter sayi 6 dan kichikdirse InvalidArgumentException
	//Eger name xarakter sayi 3 dan kichikdirse InvalidArgumentException
	//Eger surname xarakter sayi 4 dan kichikdirse InvalidArgumentException
	void signUp(string username, string password, string name, string surname);
};


class StartUp {
public:
	static void Start() {
		Database db;
		Registration twitter(db);

		// twitter.getDatabase().addUser(user);

		//mainde yazilacaq her shey burda yazilsin.
	}




};



int main() {
	StartUp::Start();


	system("pause");

    return 0;
}