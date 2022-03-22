#include "functionPrototype.h"

void dataAccount::showProfile(){
    system("CLS");
    cout << "ACCOUNT PROFILE\n";
    cout << "---------------\n";
    cout << "User ID: " << studentID << endl;
    cout << "Social ID: " << socialId << endl;
    cout << "Name: " << lastName << " " << firstName << endl;
    cout << "Gender: " << gender << endl;
    cout << "Date of birth: " << dob << endl;
    if (accountType == "2") cout << "Class: " << _class << endl;
}
void dataAccount::changePassword(){
    string confirmPassword = "";
    system("CLS");
    cout << "CHANGE PASSWORD\n";
    cout << "---------------\n";
    while (password != confirmPassword){
        cout << "Enter old password: ";
        cin >> confirmPassword;
    }
    cout << "Enter new password: ";
    cin >> password;
    cout << "Complete!";
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
    getch();
    manageAccount(account);
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
        fs << cur->data.title;
        cur = cur->next;
    }
    fs.close();
}
