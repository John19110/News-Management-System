#include <string.h>
#include <fstream>
#include <vector>
//4


using namespace std;
class Admin
{
private:
	string username;
	string password;

public:



	//constructor
	Admin();
	Admin(string username, string password);
	bool Login(string username, string password);
	//getters
	string getUserName();
	string getPassword();

	

	;



};




