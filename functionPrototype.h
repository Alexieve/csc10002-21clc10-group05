#ifndef _FUNCTIONPROTOTYPE_H_
#define _FUNCTIONPROTOTYPE_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

struct User{
    string username, password, accountType;
    string userID, id, socialId;
    string firstName, lastName, gender, dob, _class, title;
    User *next = NULL, *prev= NULL;

    void showProfile(){
        cout << "User ID: " << id << endl;
        cout << "Social ID: " << socialId << endl;
        cout << "Name: " << lastName << " " << firstName << endl;
        cout << "Gender: " << gender << endl;
        cout << "Date of birth: " << dob << endl;
        if (accountType == "1") cout << "Class: " << _class << endl;
        getch();
    }
    void changePassword(){
        string confirmPassword = "";
        while (password != confirmPassword){
            cout << "Enter old password: ";
            cin >> confirmPassword;
        }
        cout << "Enter new password: ";
        cin >> password;
        cout << "Complete!";
        getch();
    }
};
struct Class{
    string className;
    User* student = NULL;
    Class *next, *prev;
};
struct schoolYear{
    string startYear, endYear;
    schoolYear *next, *prev;
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
void staffProcess(Account* &curAccount, Class* &headClass, schoolYear* &headSchoolYear);
schoolYear* getSchoolYear(schoolYear newData);
void pushBackSchoolYear(schoolYear* &head, schoolYear newData);
void creatSchoolYear(schoolYear* &headSchoolYear);
Class* getClass(string newData);
void pushBackClass(Class* &head, string newData);
void createClass(Class* &headClass);
void pushBackStudent(User* curStudent, Class* &curClass);
void add1stStudents(Account* headAccount, Class* &headClass);
void studentProcess(Account* &curAccount);
void showClass(Class* headClass);
#endif  _FUNCTIONPROTOTYPE_H_
