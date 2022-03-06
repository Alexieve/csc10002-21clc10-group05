#include "functionPrototype.h"

Account* getAccount(User newData){
    Account* newNode = new Account;
    newNode->data = newData;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBackAccount(Account* &head, User newData){
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
        pushBackAccount(head, data);
    }
    fs.close();
}
