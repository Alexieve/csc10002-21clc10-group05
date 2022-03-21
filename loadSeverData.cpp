#include "functionPrototype.h"

void loadClass(Class* &headClass, Account* headAccount){
    fstream fs;
    fs.open("classData.csv", ios::in);
    while (!fs.eof()){
        string className;
        getline(fs, className);
        pushBackClass(headClass, className);

        Class* curClass = headClass;
        while (curClass->next) curClass = curClass->next;
        string userID = "1";
        while (userID != "x"){
            getline(fs, userID, ',');
            Account* curAccount = headAccount;
            while (curAccount){
                if (curAccount->data.userID == userID){
                    Account* newStudent = getAccount(curAccount->data);
                    pushBackStudent(newStudent, curClass->data.student);
                }
                curAccount = curAccount->next;
            }
        }
    }
    fs.close();
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
            getline(fs, dataS.startYear, ',');
            getline(fs, dataS.endYear, ',');
            getline(fs, dataS.startDate, ',');
            getline(fs, dataS.endDate, ',');
            getline(fs, checkS);
            push_Semester(curSY->data.headSemester, dataS);

            Semester *curS = curSY->data.headSemester;
            while (curS->next) curS = curS->next;
            string checkC = "1";
            while (checkC == "1"){ /// There are still some courses
                dataCourse dataC;
                getline(fs, dataC.id, ',');
                getline(fs, dataC.course_name, ',');
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
            fs << curS->data.startYear << ',';
            fs << curS->data.endYear << ',';
            fs << curS->data.startDate << ',';
            fs << curS->data.endDate << ',';
            if (curS->next) fs << 1 << '\n';
            else fs << 0 << '\n';

            Course* curC = curS->data.headCourse;
            while (curC){
                fs << curC->data.id << ',';
                fs << curC->data.course_name << ',';
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
