#include "functionPrototype.h"

void manageAccount(User &account){
    system("CLS");
    cout << "1. Profile\n";
    cout << "2. Change password\n";
    string input = "";
    cin >> input;
    if (input == "1") account.showProfile();
    else if (input == "2") account.changePassword();
}
void studentProcess(Account* &curAccount){

}
void showClass(Class* headClass){
    Class* curClass = headClass;
    while (curClass){
        cout << curClass->className << endl;
        User* curStudent = curClass->student;
        while (curStudent){
            cout << curStudent->firstName << " ";
            curStudent = curStudent->next;
        }
        curClass = curClass->next;
        cout << endl;
    }
    getch();
}
bool start(Account* &headAccount, Class* &headClass, schoolYear*& headSchoolYear){
    // if check = false then stop the program
    // check is a temporary var to stop program
    bool check = true;
    Account* curAccount;
    while (!login(headAccount, curAccount)); // login into program and get account data

    while (true){
        system("CLS");
        cout << "1. Manage account\n";
        cout << "2. Main page\n";
        cout << "3. Log out\n";
        string input = "";
        cin >> input;
        if (input == "1") manageAccount(curAccount->data);
        else if (input == "2"){
            if (curAccount->data.accountType == "1") staffProcess(curAccount, headClass, headSchoolYear);
            else studentProcess(curAccount);
        }
        else if (input == "3") return true;
        updateAccountData(headAccount); // update account data after run program
        showClass(headClass);
    }
    return check;
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
        fs << cur->data.id << ',';
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
int main(){
    Account* headAccount = NULL;
    Class* headClass = NULL;
    schoolYear* headSchoolYear = NULL;
    Semester* headSemester = NULL;
    loadAccount(headAccount);
    while (start(headAccount, headClass, headSchoolYear));
    return 0;
}

