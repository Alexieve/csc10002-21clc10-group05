#ifndef _FUNCTIONPROTOTYPE_H_
#define _FUNCTIONPROTOTYPE_H_

#include <iostream>
#include <fstream>
using namespace std;

struct User{
    string username, password, accountType;
    string userID, id, socialId;
    string firstName, lastName, gender, dob, _class, title;

    void showProfile(){
        cout << "User ID: " << id << endl;
        cout << "Social ID: " << socialId << endl;
        cout << "Name: " << lastName << " " << firstName << endl;
        cout << "Gender: " << gender << endl;
        cout << "Gender: " << dob << endl;
        if (accountType == "1") cout << "Class: " << _class << endl;
    }
    void changePassword(){
        string confirmPassword = "";
        while (password != confirmPassword){
            cout << "Enter old password: ";
            cin >> confirmPassword;
        }
        cout << "Enter new password: ";
        cin >> password;
    }
};
struct Account{
    User data;
    Account *next, *prev;
};
Account* getAccount(User newData);
void pushBackAccount(Account* &head, User newData);
void loadAccount(Account* &head);
void manageAccount(User &account);
bool checkLogin(Account* curAccount, string username0, string password0);
bool login(Account* head, Account* &curAccount);
bool start(Account* headAccount);
void updateAccountData(Account* headAccount);
#endif  _FUNCTIONPROTOTYPE_H_
