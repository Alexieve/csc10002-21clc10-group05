#include "functionPrototype.h"

void loadAccount(Account* &head){
    fstream fs;
    fs.open("userData.csv", ios::in);
    while (!fs.eof()){
        dataAccount data;
        getline(fs, data.username, ',');
        getline(fs, data.password, ',');
        getline(fs, data.accountType, ',');
        getline(fs, data.userID, ',');
        getline(fs, data.studentID, ',');
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

void loadAccountCourse(Account* &head) {
    fstream fs;
    fs.open("courseData.csv", ios::in);
    while (!fs.eof()) {
        Account* curHead = head;
        while (curHead) {
            string input;
            getline(fs, input);
            int cnt = int(input[0]) - '0';
            curHead -> data.nCourse = cnt;
            while (cnt > 0) {
                dataCourse dataC;
                getline(fs, dataC.startDate, ',');
                getline(fs, dataC.endDate, ',');
                getline(fs, dataC.id, ',');
                getline(fs, dataC.course_name, ',');
                getline(fs, dataC.teacher_name, ',');
                getline(fs, dataC.credits, ',');
                getline(fs, dataC.max_students, ',');
                getline(fs, dataC.days, ',');
                getline(fs, dataC.session1.day, ',');
                getline(fs, dataC.session1.time, ',');
                getline(fs, dataC.session2.day, ',');
                if (cnt != 1)
                    getline(fs, dataC.session2.time, ',');
                else
                    getline(fs, dataC.session2.time);
                addCourseAccount(curHead -> data.hCourse, dataC);
                cnt--;
            }
            curHead = curHead -> next;
        }
    }
    fs.close();
}

void loadClass(Class* &headClass, Account* headAccount){
    Account *curAccount = headAccount;
    while (curAccount){
        if (curAccount->data._class == "NULL"){
            curAccount = curAccount->next;
            continue;
        }
        pushBackClass(headClass, curAccount->data._class);
        Account *newStudent = getAccount(curAccount->data);
        Class *curClass = headClass;
        while (curClass){
            if (curClass->data.className == curAccount->data._class){
                pushBackStudent(newStudent, curClass->data.student);
                break;
            }
            curClass = curClass->next;
        }
        curAccount = curAccount->next;
    }
}
void loadSeverData(schoolYear* &headSchoolYear){
    fstream fs;
    fs.open("severData.csv", ios::in);
    while (!fs.eof()){
        dataSchoolYear dataSY;
        getline(fs, dataSY.startYear, ',');
        getline(fs, dataSY.endYear);
        pushBackSchoolYear(headSchoolYear, dataSY);

        schoolYear *curSY = headSchoolYear;
        while (curSY->next) curSY = curSY->next;
        string checkS = "1";
        while (checkS == "1"){ /// There are still some semesters
            dataSemester dataS;
            getline(fs, dataS.num, ',');
            getline(fs, dataS.startDate, ',');
            getline(fs, dataS.endDate, ',');
            getline(fs, dataS.startReg, ',');
            getline(fs, dataS.endReg, ',');
            getline(fs, checkS);
            push_Semester(curSY->data.headSemester, dataS);

            Semester *curS = curSY->data.headSemester;
            while (curS->next) curS = curS->next;
            string checkC = "1";
            while (checkC == "1"){ /// There are still some courses
                dataCourse dataC;
                getline(fs, dataC.id, ',');
                getline(fs, dataC.course_name, ',');
                getline(fs, dataC.teacher_name, ',');
                getline(fs, dataC.credits, ',');
                getline(fs, dataC.max_students);

                getline(fs, dataC.session1.day, ',');
                getline(fs, dataC.session1.time, ',');
                getline(fs, dataC.session2.day, ',');
                getline(fs, dataC.session2.time, ',');
                getline(fs, checkC);
                push_course(curS->data.headCourse, dataC);
            }
        }
    }
    fs.close();
}

void updateAccountCourse(Account *head) {
    fstream fs;
    fs.open("courseData.csv", ios::out);
    Account* curHead = head;
    while (curHead) {
        fs << curHead -> data.nCourse << '\n';
        Course* hCourse = curHead -> data.hCourse;
        while (hCourse) {
            fs << hCourse -> data.startDate << ',';
            fs << hCourse -> data.endDate << ',';
            fs << hCourse -> data.id << ',';
            fs << hCourse -> data.course_name << ',';
            fs << hCourse -> data.teacher_name << ',';
            fs << hCourse -> data.credits << ',';
            fs << hCourse -> data.max_students << ',';
            fs << hCourse -> data.days << ',';
            fs << hCourse -> data.session1.day << ',';
            fs << hCourse -> data.session1.time << ',';
            fs << hCourse -> data.session2.day << ',';
            if (hCourse -> next)
                fs << hCourse -> data.session2.time << ',';
            else
                fs << hCourse -> data.session2.time << '\n';
            hCourse = hCourse -> next;
        }
        curHead = curHead -> next;
    }
    fs.close();
}

void updateSeverData(schoolYear* &headSchoolYear){
    fstream fs;
    fs.open("severData.csv", ios::out);
    schoolYear* curSY = headSchoolYear;
    bool check = false;
    while (curSY){
        if (check) fs << '\n';
        else check = true;

        fs << curSY->data.startYear << ',';
        fs << curSY->data.endYear << '\n';

        Semester* curS = curSY->data.headSemester;
        while (curS){
            fs << curS->data.num << ',';
            fs << curS->data.startDate << ',';
            fs << curS->data.endDate << ',';
            fs << curS->data.startReg << ',';
            fs << curS->data.endReg << ',';
            if (curS->next) fs << 1 << '\n';
            else fs << 0 << '\n';

            Course* curC = curS->data.headCourse;
            while (curC){
                fs << curC->data.id << ',';
                fs << curC->data.course_name << ',';
                fs << curC->data.teacher_name << ',';
                fs << curC->data.credits << ',';
                fs << curC->data.max_students << '\n';

                fs << curC->data.session1.day << ',';
                fs << curC->data.session1.time << ',';
                fs << curC->data.session2.day << ',';
                fs << curC->data.session2.time << ',';
                if (curC->next)  fs << 1 << '\n';
                else fs << 0;
                curC = curC->next;
            }
            curS = curS->next;
            if (curS) fs << '\n';
        }
        curSY = curSY->next;
    }
    fs.close();
}
