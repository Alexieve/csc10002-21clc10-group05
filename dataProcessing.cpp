#include "functionPrototype.h"

Account* getAccount(dataAccount newData){
    Account* newNode = new Account;
    newNode->data = newData;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBackAccount(Account* &head, dataAccount newData){
    Account* newAccount = getAccount(newData);
    if (!head){
        head = newAccount;
        return;
    }

    Account* cur = head;
    while (cur->next){
        if (cur->data.studentID == newData.studentID) return;
        cur = cur->next;
    }
    if (cur->data.studentID == newData.studentID) return;
    newAccount->prev = cur;
    cur->next = newAccount;
}
schoolYear* getSchoolYear(dataSchoolYear newData){
    schoolYear* newNode = new schoolYear;
    newNode->data.startYear = newData.startYear;
    newNode->data.endYear = newData.endYear;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBackSchoolYear(schoolYear* &head, dataSchoolYear newData){
    schoolYear* newSchoolYear = getSchoolYear(newData);
    if (!head){
        head = newSchoolYear;
        return;
    }

    schoolYear* cur = head;
    while (cur->next){
        if (cur->data.startYear == newData.startYear && cur->data.endYear == newData.endYear) return;
        cur = cur->next;
    }
    if (cur->data.startYear == newData.startYear && cur->data.endYear == newData.endYear) return;
    newSchoolYear->prev = cur;
    cur->next = newSchoolYear;
}
Class* getClass(string newData){
    Class* newNode = new Class;
    newNode->data.className = newData;
    newNode->data.student = NULL;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBackClass(Class* &head, string newData){
    Class* newClass = getClass(newData);
    if (!head){
        head = newClass;
        return;
    }

    Class* cur = head;
    while (cur->next){
        if (cur->data.className == newData) return;
        cur = cur->next;
    }
    if (cur->data.className == newData) return;
    newClass->prev = cur;
    cur->next = newClass;
}
void pushBackStudent(Account* &curStudent, Account* &headStudent){
    if (!headStudent){
        headStudent = curStudent;
        return;
    }
    Account* lastStudent = headStudent;
    while (lastStudent->next){
        if (lastStudent->data.username == curStudent->data.username) return;
        lastStudent = lastStudent->next;
    }

    if (lastStudent->data.username == curStudent->data.username) return;
    lastStudent->next = curStudent;
    curStudent->prev = lastStudent;
}
Course* getCourse(dataCourse dataC){
    Course *newCourse = new Course;
    newCourse->data = dataC;
    newCourse->next = newCourse->prev = NULL;
    return newCourse;
}
void push_course(Course* &headCourse, dataCourse dataC){
    Course* newCourse = getCourse(dataC);
    if (!headCourse){
        headCourse = newCourse;
        return;
    }
    Course *curCourse = headCourse;
    while (curCourse->next){
        if (curCourse->data.id == dataC.id) return;
        curCourse = curCourse->next;
    }
    if (curCourse->data.id == dataC.id) return;
    newCourse->prev = curCourse;
    curCourse->next = newCourse;
}
Semester* getSemester(dataSemester dataS){
    Semester *newSemester = new Semester;
    newSemester->data = dataS;
    newSemester->next = newSemester->prev = NULL;
    return newSemester;
}
void push_Semester(Semester* &headSemester, dataSemester dataS){
    Semester* newSemester = getSemester(dataS);
    if (!headSemester){
        headSemester = newSemester;
        return;
    }
    Semester *curSemester = headSemester;
    while (curSemester->next){
        if (curSemester->data.num == dataS.num) return;
        curSemester = curSemester->next;
    }
    if (curSemester->data.num == dataS.num) return;
    newSemester->prev = curSemester;
    curSemester->next = newSemester;
}
bool compareDate(string year1, string month1, string day1, string year2, string month2, string day2){
    if (year1 > year2) return false;
    else if (year1 < year2) return true;
    else{
        if (month1 > month2) return false;
        else if (month1 < month2) return true;
        else{
            if (day1 > day2) return false;
            else return true;
        }
    }
}
bool checkEnrollTime(Semester* curSemester){
    string startReg = curSemester->data.startReg;
    string endReg = curSemester->data.endReg;

    string yearStart = startReg.substr(0,4);
    string monthStart = startReg.substr(5,2);
    string dayStart = startReg.substr(8,2);
    string yearEnd = endReg.substr(0,4);
    string monthEnd = endReg.substr(5,2);
    string dayEnd = endReg.substr(8,2);

    time_t now = time(NULL);
    tm *const Date = localtime(&now);
    string yearNow = to_string(1900 + Date->tm_year);
    string monthNow = to_string(1 + Date->tm_mon);
    string dayNow = to_string(Date->tm_mday);
    if (monthNow.length() == 1) monthNow = "0" + monthNow;
    if (dayNow.length() == 1) dayNow = "0" + dayNow;

    bool check1 = compareDate(yearStart, monthStart, dayStart, yearNow, monthNow, dayNow);
    bool check2 = compareDate(yearNow, monthNow, dayNow, yearEnd, monthEnd, dayEnd);
    if (check1 && check2) return true;
    return false;
}
