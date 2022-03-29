#ifndef _FUNCTIONPROTOTYPE_H_
#define _FUNCTIONPROTOTYPE_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <cstring>
#include <ctime>
using namespace std;


struct Session {
    string day, time;
};
struct dataCourse {
    string startDate, endDate;
    string id, course_name, teacher_name, credits, max_students = "50", days;
    Session session1, session2;
};
struct Course {
    dataCourse data;
    Course *next, *prev;
};
struct dataAccount{
    string username, password, accountType;
    string userID, studentID, socialId;
    string firstName, lastName, gender, dob, _class, title;
    int nCourse = 0;
    Course *hCourse = NULL;

    /// Functions ///
    void showProfile();
    void changePassword();
};
struct Account{
    dataAccount data;
    Account *next, *prev;
};
struct dataClass{
    string className;
    Account *student = NULL;
};
struct Class{
    dataClass data;
    Class *next, *prev;
};
struct dataSemester {
    string num;
    string startDate, endDate;
    string startReg, endReg;
    Course *headCourse = NULL;
};
struct Semester {
    dataSemester data;
    Semester *next, *prev;
};
struct dataSchoolYear{
    string startYear, endYear;
    Semester *headSemester = NULL;
};
struct schoolYear{
    dataSchoolYear data;
    schoolYear *next, *prev;
};
struct Day{
	dataDay data;
	Day *next, *prev;
};
struct dataDay{
	string name; 
	string time1, time2, time3, time4;
}; 
Account* getAccount(dataAccount newData);
void pushBackAccount(Account* &head, dataAccount newData);
void loadAccount(Account* &head);
void loadAccountCourse(Account* &head);
void manageAccount(dataAccount &account);
bool checkLogin(Account* curAccount, string username0, string password0);
bool login(Account* head, Account* &curAccount);
bool start(Account* headAccount);
void updateAccountData(Account* headAccount);
void updateAccountCourse(Account* headAccount);
void staffProcess(Account* &curAccount, Account* &headAccount, Class* &headClass, schoolYear* &headSchoolYear);
schoolYear* getSchoolYear(schoolYear newData);
void pushBackSchoolYear(schoolYear* &head, dataSchoolYear newData);
void creatSchoolYear(schoolYear* &headSchoolYear);
Class* getClass(string newData);
void pushBackClass(Class* &head, string newData);
void createClass(Class* &headClass);
void pushBackStudent(Account* &curStudent, Account* &headStudent);
void add1stStudents(Account* headAccount, Class* &headClass);
void studentProcess(Account* &curAccount, Account* &headAccount, Class* &headClass, schoolYear* &headSchoolYear);
void showClass(Class* headClass);
void push_course(Course* &headCourse, dataCourse dataC);
void create_Course(Course* &headCourse);
void push_Semester(Semester* &headSemester, dataSemester dataS);
void create_Semester(Semester* &headSemester);
schoolYear* chooseSchoolYear(schoolYear *headSchoolYear);
Semester* chooseSemester(Semester *headSemester);
void addCourseAccount(Course* &hCourse, dataCourse dataC);
void viewCourseList(Course* &headCourse, Account* &curAccount);
schoolYear* chooseSchoolYearToAddSemester(schoolYear *headSchoolYear);
void loadSeverData(schoolYear* &headSchoolYear);
void updateSeverData(schoolYear* &headSchoolYear);
void loadClass(Class* &headClass, Account* headAccount);
void viewCourseInfor(dataCourse &dataC, Course*& headCourse, Account*& curAccount);
void deleteCourse(Course* &curCourse);
void changeCourseInfor(dataCourse &dataC, int x);
bool compareDate(string year1, string month1, string day1, string year2, string month2, string day2);
bool checkEnrollTime(Semester* curSemester);
void enrollCourse(Account* &curAccount, schoolYear* &headSchoolYear);
void viewEnrolledCourse(dataAccount dataA);
Day* getDay(dataDay newData);
void pushDay(Day* &head, dataDay newData);
void createDay(Day* &headDay, Course *headCourse);
#endif  _FUNCTIONPROTOTYPE_H_
