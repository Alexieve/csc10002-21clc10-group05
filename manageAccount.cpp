#include "functionPrototype.h"

void dataAccount::showProfile(){
	TextColor(11);
    system("CLS");
    cout << "     ACCOUNT PROFILE\n";
    cout << "--------------------------\n";
    TextColor(15);
    cout << "User ID: " << userID << endl;
    if (accountType == "2") cout << "Student ID: " << studentID << endl;
    cout << "Social ID: " << socialId << endl;
    cout << "Name: " << lastName << " " << firstName << endl;
    cout << "Gender: " << gender << endl;
    cout << "Date of birth: " << dob << endl;
    if (accountType == "2") cout << "Class: " << _class << endl;
    getch();
}
void dataAccount::changePassword(){
	TextColor(11);
    string confirmPassword = "";
    system("CLS");
    cout << "\tCHANGE PASSWORD\n";
    cout << "-------------------------------\n";
    TextColor(15);
    while (password != confirmPassword){
        cout << "Enter old password: ";
        cin >> confirmPassword;
    }
    cout << "Enter new password: ";
    cin >> password;
    cout << "Complete!";
    getch();
}
void manageAccount(dataAccount &account){
    system("CLS");
    cout << "1. Profile\n";
    cout << "2. Change password\n";
    cout << "0. Back!\n";
    string input = "";
    cin >> input;
    if (input == "1") account.showProfile();
    else if (input == "2") account.changePassword();
    else if (input == "0") return;
    else{
        cout << "Wrong input, try again!";
        getch();
    }
    manageAccount(account);
    return;
}
void updateAccountData(Account* headAccount){
    fstream fs;
    fs.open("userData.csv", ios::out);
    Account* cur = headAccount;
    bool check = false;
    while (cur){
        if (check) fs << '\n';
        else check = true;
        fs << cur->data.username << ',';
        fs << cur->data.password << ',';
        fs << cur->data.accountType << ',';
        fs << cur->data.userID << ',';
        fs << cur->data.studentID << ',';
        fs << cur->data.socialId << ',';
        fs << cur->data.firstName << ',';
        fs << cur->data.lastName << ',';
        fs << cur->data.gender << ',';
        fs << cur->data.dob << ',';
        fs << cur->data._class << ',';
        fs << cur->data.nCourse;
        cur = cur->next;
    }
    fs.close();
}
