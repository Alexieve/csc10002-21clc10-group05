#include "functionPrototype.h"

void manageAccount(User &account){
    cout << "1. Profile\n";
    cout << "2. Change password\n";
    cout << "3. Log out\n";
    string input = "";
    cin >> input;
    if (input == "3") return;
    if (input == "1") account.showProfile();
    else if (input == "2") account.changePassword();
}
bool start(Account* headAccount){
    bool check = true;
    Account* curAccount = new Account;
    while (!login(headAccount, curAccount));
    manageAccount(curAccount->data);
    updateAccountData(headAccount);
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
    loadAccount(headAccount);
    while (start(headAccount));
    return 0;
}
