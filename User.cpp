#include "User.h"
//2
User::User() {};
User::User(int id, string username, string password, vector<string> prefferedCategories)
{
	this->id = id;
	this->username = username;
	this->password = password;
	this->preferredCategories = preferredCategories;
}
bool User::Login(string givenusername, string givenpassword)
{
	bool decision=false;

	if (givenusername==username && givenpassword==password) {
		decision= true;
		cout << "Login Successfull!\n";
	}
	return decision;
}
string User::getUserName()
{
	return this->username;
}
string User::getPassword()
{
	return string(password.length(), '*');
}
bool User::CheckLogin(string username, string pass)
{
	ifstream file("login_info.txt");
	if (!file.is_open()) {
		cerr << "Unable to locate the data" << endl;
		return false;
	}
	string storedName, storedPass;
	int id;
	bool LoginAttemptsFailed = true;
	while (file >> id >> storedName >> storedPass) {
		if (storedName == username && storedPass == pass) {
			file.close();
			cout << "Welcome, " << username << endl;
			cout << "Loading the Articals for you...." << endl;
			return true;
		}
		else {
			LoginAttemptsFailed = false;
		}
	}
	file.close();


	return LoginAttemptsFailed;
}
bool User::CheckAdmin(string name)
{
	ifstream file("login_admin.txt");
	if (!file.is_open()) {
		cerr << "Unable to locate the data" << endl;
		return false;
	}
	string adminName;
	while (file >> adminName) {
		if (adminName == name) {
			file.close();
			return true;
		}
		else {
			return false;
		}

	}
}
int User::getID() {
	return this->id;
}

	
	







