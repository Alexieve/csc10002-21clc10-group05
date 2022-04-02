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
        string nCourse;
        getline(fs, nCourse, ',');
        data.nCourse = convertToInt(nCourse);
        getline(fs, data.title);
        pushBackAccount(head, data);
    }
    fs.close();
}
void loadAccountCourse(Account* &hAccount, schoolYear* &hSchoolYear) {
    fstream fs;
    fs.open("courseData.csv", ios::in);
    while (!fs.eof()){
        string curStartYear, curEndYear;
        getline(fs, curStartYear, ',');
        getline(fs, curEndYear);
        schoolYear *curSY = hSchoolYear;
        while (curSY){
            if (curSY->data.startYear == curStartYear && curSY->data.endYear == curEndYear)
                break;
            curSY = curSY->next;
        }
        string curSemester, checkS = "1";
        while (checkS == "1"){
            getline(fs, curSemester, ',');
            getline(fs, checkS);
            Semester *curS = curSY->data.headSemester;
            while (curS){
                if (curS->data.num == curSemester) break;
                curS = curS->next;
            }
            string curCourse, checkC = "1";
            while (checkC == "1"){
                getline(fs, curCourse, ',');
                Course *curC = curS->data.headCourse;
                while (curC){
                    if (curC->data.id == curCourse) break;
                    curC = curC->next;
                }

                for (int i = 1; i <= curC->data.nStudent; i++){
                    string studentID;
                    getline(fs, studentID, ',');
                    Account *curStudent = hAccount;
                    while (curStudent){
                        if (curStudent->data.studentID == studentID) break;
                        curStudent = curStudent->next;
                    }
                    push_course(curStudent->data.hCourse, curC->data);
                    pushBackAccount(curC->data.hAccount, curStudent->data);
                }
                getline(fs, checkC);
            }
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
                string mxStudent, nStudent;
                getline(fs, mxStudent, ',');
                getline(fs, nStudent);
                dataC.max_students = convertToInt(mxStudent);
                dataC.nStudent = convertToInt(nStudent);

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
void updateAccountCourse(schoolYear* hSchoolYear){
    fstream fs;
    fs.open("courseData.csv", ios::out);
    schoolYear* curSY = hSchoolYear;
    bool check = false;
    while (curSY){
        if (check) fs << '\n';
        else check = true;

        dataSchoolYear dataSY = curSY->data;
        fs << dataSY.startYear << ',' << dataSY.endYear << '\n';
        Semester *curS = dataSY.headSemester;
        while (curS){
            dataSemester dataS = curS->data;
            fs << dataS.num << ',';
            if (curS->next) fs << 1 << '\n';
            else fs << 0 << '\n';
            Course *curC = dataS.headCourse;
            while (curC){
                dataCourse dataC = curC->data;
                fs << dataC.id << ',';
                Account *curStudent = dataC.hAccount;
                while (curStudent){
                    fs << curStudent->data.studentID << ',';
                    curStudent = curStudent->next;
                }
                if (curC->next) fs << 1 << '\n';
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
void updateSeverData(schoolYear* headSchoolYear){
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
                fs << curC->data.max_students << ',';
                fs << curC->data.nStudent << '\n';

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
