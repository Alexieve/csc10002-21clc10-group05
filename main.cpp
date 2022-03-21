#include "functionPrototype.h"

bool start(Account* &headAccount, Class* &headClass, schoolYear*& headSchoolYear){
    Account* curAccount;
    while (!login(headAccount, curAccount)); // login into program and get account data
    while (true){
        system("CLS");
        cout << "1. Manage account\n";
        cout << "2. Main page\n";
        cout << "3. Log out\n";
        cout << "0. EXIT!\n";
        string input = "";
        cin >> input;
        if (input == "1") manageAccount(curAccount->data);
        else if (input == "2"){
            if (curAccount->data.accountType == "1") staffProcess(curAccount, headAccount, headClass, headSchoolYear);
            else studentProcess(curAccount);
        }
        else if (input == "3") return true;
        else if (input == "0") return false;
        updateAccountData(headAccount); // update account data after run program
    }
}
int main(){
    Account* headAccount = NULL;
    Class* headClass = NULL;
    schoolYear* headSchoolYear = NULL;
    loadAccount(headAccount);
//    loadClass(headClass, headAccount);
    loadSeverData(headSchoolYear);
    while (start(headAccount, headClass, headSchoolYear));
    return 0;
}

