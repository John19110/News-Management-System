#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
//2
using namespace std;
class User
{
public:
	int id;
	string username;
	string password;
	int attemptCount = 0;
	int maxAttempts = 3;
	vector<string> preferredCategories;

	User();
	User(int,string,string,vector<string>);
	bool Login(string,string);
	string getUserName();
	string getPassword();
	bool CheckLogin(string username, string pass);
	bool CheckAdmin(string name);
	int getID();
};

