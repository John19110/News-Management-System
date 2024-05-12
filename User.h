#pragma once
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include<map>
#include<string>
using namespace std;
class User
{
public:
	int id;
	string username;
	string password;
	vector<string> preferredCategories;
	

	User();
	User(int, string, string, vector<string>);
	bool Login(string, string);
	string getUserName();
	string getPassword();
	bool CheckLogin(string username, string pass);
	int getID();
	string toString() const;

};



