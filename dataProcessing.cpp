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
