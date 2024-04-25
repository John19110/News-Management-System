#include "Admin.h"
#include "News.h"
#include <cstring>
//4

Admin::Admin() {

}
Admin::Admin(string username, string password)
{
    this->username = username;
    this->password = password;
}

bool Admin::Login(string username, string password) {
    if (this->username == username && this->password == password) {
        return true;
    }
    else {
        return false;
    }
}

string Admin::getUserName() {
    return this->username;
}

string Admin::getPassword() {
    return string(password.length(), '*');
}










