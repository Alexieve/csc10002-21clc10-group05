#include "functionPrototype.h"

bool checkLogin(Account* curAccount, string username0, string password0){
    if (curAccount->data.username == username0
        && curAccount->data.password == password0)
        return true;
    return false;
}
bool login(Account* head, Account* &curAccount){
    system("CLS");
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
    curAccount = cur; // get login account data
    return true;
}

