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
Account* getAccount(User newData){
    Account* newNode = new Account;
    newNode->data = newData;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBack(Account* &head, User newData){
    Account* newAccount = getAccount(newData);
    if (head == NULL){
        head = newAccount;
        return;
    }

    Account* cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    newAccount->prev = cur;
    cur->next = newAccount;
}
void loadAccount(Account* &head){
    fstream fs;
    fs.open("userData.csv", ios::in);
    while (!fs.eof()){
        User data;
        getline(fs, data.username, ',');
        getline(fs, data.password, ',');
        getline(fs, data.accountType, ',');
        getline(fs, data.userID, ',');
        getline(fs, data.id, ',');
        getline(fs, data.socialId, ',');
        getline(fs, data.firstName, ',');
        getline(fs, data.lastName, ',');
        getline(fs, data.gender, ',');
        getline(fs, data.dob, ',');
        getline(fs, data._class, ',');
        getline(fs, data.title);
        pushBack(head, data);
    }
    fs.close();
}
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
bool checkLogin(Account* curAccount, string username0, string password0){
    if (curAccount->data.username == username0
        && curAccount->data.password == password0)
        return true;
    return false;
}
bool login(Account* head, Account* &curAccount){
    string username0, password0;
    cout << "Login!\n";
    cout << "Username: ";
    cin >> username0;
    cout << "Password: ";
    cin >> password0;

    Account* cur = head;
    while (cur && !checkLogin(cur, username0, password0))
        cur = cur->next;
    if (cur == NULL) return false;
    curAccount = cur;
    return true;
}
bool start(Account* headAccount){
    bool check = true;
    Account* curAccount = new Account;
    while (!login(headAccount, curAccount));
    manageAccount(curAccount->data);
    return check;
}
int main(){
    Account* headAccount = NULL;
    loadAccount(headAccount);
    while (start(headAccount));
    return 0;
}
