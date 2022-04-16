#ifndef _FUNCTIONPROTOTYPE_H_
#define _FUNCTIONPROTOTYPE_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <windows.h>
using namespace std;

struct dataAccount;
struct Account;

struct Session {
    string day, time;
};
struct dataCourse {
    string startDate, endDate;
    string id, course_name, teacher_name, credits, days;
    int max_students = 50, nStudent = 0;
    double totalMark = 0, finalMark = 0, midtermMark = 0, otherMark = 0;
    Session session1, session2;
    Account *hAccount = NULL;
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

Account* getAccount(dataAccount newData);
void pushBackAccount(Account* &head, dataAccount newData);
void loadAccount(Account* &head);
void loadAccountCourse(Account* &hAccount, schoolYear* &hSchoolYear);
void manageAccount(dataAccount &account);
bool checkLogin(Account* curAccount, string username0, string password0);
bool login(Account* head, Account* &curAccount);
bool start(Account* headAccount);
void updateAccountData(Account* headAccount);
void updateAccountCourse(schoolYear* hSchoolYear);
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
void viewClass(Class* headClass);
void viewStudentInClass(Class* curClass);
Course* getCourse(dataCourse dataC);
void push_course(Course* &headCourse, dataCourse dataC);
void create_Course(Course* &headCourse);
Semester* getSemester(dataSemester dataS);
void push_Semester(Semester* &headSemester, dataSemester dataS);
void create_Semester(Semester* &headSemester);
schoolYear* chooseSchoolYear(schoolYear *headSchoolYear);
Semester* chooseSemester(Semester *headSemester);
bool viewCourseList(Course* &headCourse, Account* &curAccount, Account* &headAccount, schoolYear* &headSchoolYear, bool studentMode);
schoolYear* chooseSchoolYearToAddSemester(schoolYear *headSchoolYear);
void loadSeverData(schoolYear* &headSchoolYear);
void updateSeverData(schoolYear* headSchoolYear);
void loadClass(Class* &headClass, Account* headAccount);
void viewCourseInfor(dataCourse &dataC, Course*& headCourse, Account*& curAccount, Account* &headAccount, schoolYear* &headSchoolYear, bool studentMode);
void deleteCourse(Course* &curCourse);
void changeCourseInfor(dataCourse &dataC, int x);
bool compareDate(string year1, string month1, string day1, string year2, string month2, string day2);
bool checkEnrollTime(Semester* curSemester);
void enrollCourse(Account* &curAccount, schoolYear* &headSchoolYear);
bool checkEnrolledCourse(dataCourse dataC, Account* curAccount);
bool checkConflictCourse(dataCourse curCouse, Course* hCourse);
void addCoureForStudent(Account* &curAccount, dataCourse dataC);
void addAccountForCourse(Course* &curCourse, dataAccount newData);
void viewCourseInforStudent(Course* &curCourse, Account* &curAccount);
void viewCourseListStudentToEnroll(Course* &headCourse, Account* &curAccount);
int convertToInt(string s);
double convertToDouble(string s);
void deleteStudentInCourse(Account* &hAccount, Account* &curAccount);
void deleteAllAccount(Account* &headAccount);
void deleteAllClass(Class* &headClass);
void deleteAllCourse(Course* &headCourse);
void deleteAllSemester(Semester &headSemester);
void deleteAllSY(schoolYear* &headSchoolYear);
void exportStudentsList(schoolYear* &headSchoolYear, dataCourse dataC);
void importStudentsList(Account* &headAccount, schoolYear* &headSchoolYear);
void viewScoreBoardInCourse_A(Course* &curCourse);
void viewScoreBoardInCourse_C(Course* &headCourse);
void viewScoreBoardInCourse_S(Semester* &headSemester);
void viewScoreBoardInCourse_SY(schoolYear* &headSchoolYear);
double calculateFinalMark(Account* curAccount);
double calculateOverallGPA(Account* curAccount, schoolYear* curSchoolYear);
void viewScoreBoardInClass_Student(Class* &curClass, schoolYear* curSchoolYear);
void viewScoreBoardStudent(Account* curAccount, schoolYear* curSchoolYear);
void createNewSY(schoolYear* &headSchoolYear);
void viewCourseList_Staff(schoolYear* &headSchoolYear, Account* &headAccount, Account* &curAccount);
void viewCourseList_Student(schoolYear* &headSchoolYear, Account* &headAccount, Account* &curAccount);
void logo();
void TextColor(int x);
#endif  _FUNCTIONPROTOTYPE_H_
