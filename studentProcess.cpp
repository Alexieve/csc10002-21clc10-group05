#include "functionPrototype.h"

void deleteStudentInCourse(Account* &hAccount, Account* &curAccount){
    if (!hAccount) return;

    if (curAccount->next == curAccount->prev){
        hAccount = NULL;
        delete hAccount;
        return;
    }

    if (!curAccount->prev){
        hAccount = curAccount->next;
        hAccount->prev = NULL;
    }
    else if (!curAccount->next) curAccount->prev->next = NULL;
    else{
        curAccount->prev->next = curAccount->next;
        curAccount->next->prev = curAccount->prev;
    }
    delete curAccount;
}
void viewCourseInforStudent(Course* &curCourse, Account* &curAccount){
    system("CLS");
    cout << "COURSES INFORMATION\n";
    cout << "-------------------\n";

    dataCourse dataC = curCourse->data;
    cout << "1. ID: " << dataC.id << endl;
    cout << "2. Name: " << dataC.course_name << endl;
    cout << "3. Teacher's name: " << dataC.teacher_name << endl;
    cout << "4. Credits: " << dataC.credits << endl;
    cout << "5. Max Students: " << dataC.max_students << endl;

    string sesTime[4] = {"7h30", "9h30", "13h30", "15h30"};
    cout << "6. Session 1: " << dataC.session1.day <<" - " << sesTime[int(char(dataC.session1.time[1]))-49] << endl;
    cout << "7. Session 2: " << dataC.session2.day <<" - " << sesTime[int(char(dataC.session2.time[1]))-49] << endl;
    cout << "0. Back!\n";
    cout << "---> ENROLL THIS COURSE!!! (Press x)\n";
    string input;
    cin >> input;
    if (input == "0") return;
    if (checkEnrolledCourse(curCourse->data, curAccount))
        cout << "This course is enrolled!";
    else if (checkConflictCourse(curCourse->data, curAccount->data.hCourse))
        cout << "This course is conflicted with existing enrolled course sessions!\n";
    else if (curAccount->data.nCourse >= 5)
        cout << "You have have already enrolled 5 courses!\n";
    else if (curCourse->data.nStudent >= curCourse->data.max_students)
        cout << "This course cannot enroll anymore!\n";
    else{
        addCoureForStudent(curAccount, curCourse->data);
        addAccountForCourse(curCourse, curAccount->data);
        cout << "You have enrolled '" << curCourse->data.course_name << "' course!\n";
    }
    getch();
}
void viewCourseListStudentToEnroll(Course* &headCourse, Account* &curAccount){
    system("CLS");
    if (!headCourse){
        cout << "No course available!";
        getch();
        return;
    }
    cout << "COURSES LIST\n";
    cout << "------------\n";
    Course *curCourse = headCourse;
    int cnt = 0;
    while (curCourse){
        dataCourse dataC = curCourse->data;
        cout << ++cnt << ". " << dataC.course_name << '\n';
        curCourse = curCourse->next;
    }
    cout << "0. Back!\n";
    string input;
    cin >> input;
    if (input == "0") return;
    cnt = convertToInt(input);
    curCourse = headCourse;
    while (--cnt) curCourse = curCourse->next;
    viewCourseInforStudent(curCourse, curAccount);
    viewCourseListStudentToEnroll(headCourse, curAccount);
}
void enrollCourse(Account* &curAccount, schoolYear* &headSchoolYear){
    schoolYear *curSY = headSchoolYear;
    Semester *curS = NULL;
    bool check = false;
    while (curSY && !check){
        curS = curSY->data.headSemester;
        while (curS && !check){
            if (checkEnrollTime(curS)) check = true;
            else curS = curS->next;
        }
        if (!check) curSY = curSY->next;
    }
    if (!curS){
        cout << "No Registation Available!\n";
        getch();
        return;
    }
    viewCourseListStudentToEnroll(curS->data.headCourse, curAccount);
}
void studentProcess(Account* &curAccount, Account* &headAccount, Class* &headClass, schoolYear* &headSchoolYear){
    system("CLS");
    cout << "1. Enroll in a course\n";
    cout << "2. View list of enrolled courses\n";
    cout << "3. View list of classes\n";
    cout << "4. View list of courses\n";
    cout << "0. Back!\n";
    string input = "";
    cin >> input;
    if (input == "1") enrollCourse(curAccount, headSchoolYear);
    else if (input == "2") viewCourseList(curAccount->data.hCourse, curAccount, headSchoolYear, false);
    else if (input == "3") viewClass(headClass);
    else if (input == "4"){
        schoolYear* curSchoolYear = chooseSchoolYear(headSchoolYear);
        Semester* curSemester = NULL;
        if (curSchoolYear) curSemester = chooseSemester(headSchoolYear->data.headSemester);
        if (curSemester) viewCourseList(curSemester->data.headCourse, curAccount, headSchoolYear, true);
    }
    else if (input == "0") return;
    updateAccountCourse(headSchoolYear);
    studentProcess(curAccount, headAccount, headClass, headSchoolYear);
}
