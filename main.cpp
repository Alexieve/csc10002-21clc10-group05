#include "functionPrototype.h"
void logo(){
	TextColor(14);
	cout << "      _ _ _    _ _ _ _     _ _ _   _ _ _ _ _   _ _ _ _    " << endl;
	cout << "    /	   /  /       /  /      /      /      /      /  / " << endl;
	cout << "   /_ _ _ /  /	     /  / _ _ _/      /      /_ _ _ /  /  " << endl;
	cout << "  /         /       /  /  \\	     /      /      /  /   " << endl;
	cout << " /         /       /  /    \\        /      /      /  /    " << endl;
	cout << "/         /_ _ _ _/  /      \\      /      /      /  /_ _ _ _" << endl;
	cout << endl;
	TextColor(15);
}
bool start(Account* &headAccount, Class* &headClass, schoolYear*& headSchoolYear){
    Account* curAccount;
    TextColor(15);
    while (!login(headAccount, curAccount)); // login into program and get account data
    while (true){
        system("CLS");
        logo();
        cout << "1. Manage account\n";
        cout << "2. Main page\n";
        cout << "3. Log out\n";
        cout << "0. EXIT!\n";
        string input = "";
        cin >> input;
        if (input == "1") manageAccount(curAccount->data);
        else if (input == "2"){
            if (curAccount->data.accountType == "1") staffProcess(curAccount, headAccount, headClass, headSchoolYear);
            else studentProcess(curAccount, headAccount, headClass, headSchoolYear);
        }
        else if (input == "3") return true;
        else if (input == "0") return false;
        else{
            cout << "Wrong input, try again!";
            getch();
            continue;
        }
        updateAccountData(headAccount); // update account data after run program
        updateSeverData(headSchoolYear);
    }
}
void deleteAllAccount(Account* &headAccount){
	while(headAccount != NULL){
        while(headAccount->data.hCourse){
            Course *Del = headAccount->data.hCourse;
            headAccount->data.hCourse = headAccount->data.hCourse->next;
            delete Del;
        }
		Account *Del = headAccount;
		headAccount = headAccount->next;
		delete Del;
	}
}
void deleteAllClass(Class* &headClass){
	while(headClass != NULL){
		Class *Del = headClass;
		headClass = headClass->next;
		delete Del;
	}
}
void deleteAllCourse(Course* &headCourse){
	while(headCourse != NULL){
        while(headCourse->data.hAccount){
            Account *Del = headCourse->data.hAccount;
            headCourse->data.hAccount = headCourse->data.hAccount->next;
            delete Del;
        }
		Course *Del = headCourse;
		headCourse = headCourse->next;
		delete Del;
	}
}
void deleteAllSemester(Semester* &headSemester){
	while(headSemester != NULL){
		deleteAllCourse(headSemester->data.headCourse);
		Semester *Del = headSemester;
		headSemester = headSemester->next;
		delete Del;
	}
}
void deleteAllSY(schoolYear* &headSchoolYear){
	while(headSchoolYear != NULL){
		deleteAllSemester(headSchoolYear->data.headSemester);
		schoolYear *Del = headSchoolYear;
		headSchoolYear = headSchoolYear->next;
		delete Del;
	}
}
int main(){
    Account* headAccount = NULL;
    Class* headClass = NULL;
    schoolYear* headSchoolYear = NULL;
    loadAccount(headAccount);
    loadSeverData(headSchoolYear);
    loadAccountCourse(headAccount, headSchoolYear);
    loadClass(headClass, headAccount);
    while (start(headAccount, headClass, headSchoolYear));
    deleteAllAccount(headAccount);
    deleteAllClass(headClass);
    deleteAllSY(headSchoolYear);
    return 0;
}
