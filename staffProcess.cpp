#include "functionPrototype.h"

schoolYear* getSchoolYear(schoolYear newData){
    schoolYear* newNode = new schoolYear;
    newNode->startYear = newData.startYear;
    newNode->endYear = newData.endYear;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBackSchoolYear(schoolYear* &head, schoolYear newData){
    schoolYear* newSchoolYear = getSchoolYear(newData);
    if (head == NULL){
        head = newSchoolYear;
        return;
    }

    schoolYear* cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    newSchoolYear->prev = cur;
    cur->next = newSchoolYear;
}
void creatSchoolYear(schoolYear* &headSchoolYear){
    system("CLS");
    schoolYear input;
    cout << "Enter the start year of the new school year: ";
    cin >> input.startYear;
    cout << "Enter the end year of the new school year: ";
    cin >> input.endYear;
    pushBackSchoolYear(headSchoolYear, input);
}
Class* getClass(string newData){
    Class* newNode = new Class;
    newNode->className = newData;
    newNode->student = NULL;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBackClass(Class* &head, string newData){
    Class* newClass = getClass(newData);
    if (head == NULL){
        head = newClass;
        return;
    }

    Class* cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    newClass->prev = cur;
    cur->next = newClass;
}
void createClass(Class* &headClass){
    system("CLS");
    cout << "Enter the class's name: ";
    string className;
    cin >> className;
    pushBackClass(headClass, className);
}
void pushBackStudent(User* curStudent, Class* &curClass){
    if (curClass->student == NULL){
        curClass->student = curStudent;
        return;
    }
    User* lastStudent = curClass->student;
    while (lastStudent->next != NULL)
        lastStudent = lastStudent->next;

    lastStudent->next = curStudent;
    curStudent->prev = lastStudent;
}
void add1stStudents(Account* headAccount, Class* &headClass){
    Account* curAccount = headAccount;
    while (curAccount->prev != NULL)
        curAccount = curAccount->prev;

    while (curAccount){
        if (curAccount->data.accountType == "2"){
            Class* curClass = headClass;
            while (curClass && curClass->className != curAccount->data._class)
                curClass = curClass->next;
            pushBackStudent(&(curAccount->data), curClass);
        }
        curAccount = curAccount->next;
    }
}
void staffProcess(Account* &curAccount, Class* &headClass, schoolYear* &headSchoolYear){
    system("CLS");
    cout << "1. Create a new school year\n";
    cout << "2. Create new class\n";
    cout << "3. Add new 1st year students to 1st-year classes\n";
    string input = "";
    cin >> input;
    if (input == "1") creatSchoolYear(headSchoolYear);
    else if (input == "2") createClass(headClass);
    else if (input == "3") add1stStudents(curAccount, headClass);
}
