#include "functionPrototype.h"

void creatSchoolYear(schoolYear* &headSchoolYear){
    system("CLS");
    cout << "CREATE NEW SCHOOL YEAR\n";
    cout << "----------------------\n";
    dataSchoolYear input;
    cout << "Enter the start year of the new school year: ";
    cin >> input.startYear;
    cout << "Enter the end year of the new school year: ";
    cin >> input.endYear;
    pushBackSchoolYear(headSchoolYear, input);
}
void createClass(Class* &headClass){
    system("CLS");
    cout << "CREATE NEW CLASS\n";
    cout << "----------------\n";
    cout << "Enter the class's name: ";
    string className;
    cin >> className;
    pushBackClass(headClass, className);
}
void viewStudentInClass(Class* curClass){
    system("CLS");
    cout << curClass->data.className << " STUDENTS LIST\n";
    cout << "------------------------\n";
    Account* headStudent = curClass->data.student;
    if (!headStudent){
        cout << "No student in this class!";
        getch();
        return;
    }
    while (headStudent){
        cout << headStudent->data.studentID << ". "
        << headStudent->data.lastName << " " << headStudent->data.firstName << endl;
        headStudent = headStudent->next;
    }
    getch();
}
void viewStudentInCourse(Course* curCourse){
	system("CLS");
    cout << curCourse->data.course_name << " STUDENTS LIST\n";
    cout << "------------------------\n";
    Account* headStudent = curCourse->data.hAccount;
    if (!headStudent){
        cout << "No student in this class!";
        getch();
        return;
    }
    while (headStudent){
        cout << headStudent->data.studentID << ". "
        << headStudent->data.lastName << " " << headStudent->data.firstName << endl;
        headStudent = headStudent->next;
    }
    getch();
}
void viewClass(Class* headClass){
    system("CLS");
    if (!headClass){
        cout << "No class available!";
        getch();
        return;
    }

    cout << "CLASSES LIST\n";
    cout << "------------\n";
    int cnt = 0;
    Class *curClass = headClass;
    while (curClass){
        cout << ++cnt << ". " << curClass->data.className << endl;
        curClass = curClass->next;
    }
    string input;
    cin >> input;
    if (input == "0") return;
    curClass = headClass;
    cnt = convertToInt(input);
    while (--cnt) curClass = curClass->next;
    viewStudentInClass(curClass);
    viewClass(headClass);
}
void add1stStudents(Account* headAccount, Class* &headClass){
    fstream fs;
    fs.open("classData.csv", ios::in);
    while (!fs.eof()){
        dataAccount data;
        getline(fs, data.userID, ',');
        getline(fs, data.studentID, ',');
        getline(fs, data.socialId, ',');
        getline(fs, data.firstName, ',');
        getline(fs, data.lastName, ',');
        getline(fs, data.gender, ',');
        getline(fs, data.dob, ',');
        getline(fs, data._class);
        data.username = data.studentID;
        data.password = "a";
        data.accountType = "2";
        data.title = "NULL";
        pushBackAccount(headAccount, data);
    }
    fs.close();
    loadClass(headClass, headAccount);
    system("CLS");
    cout << "Complete!";
    getch();
}
void create_Course(Course* &headCourse){
    if (headCourse){
        system("CLS");
        cout << "1. Create new courses\n";
        cout << "0. Back\n";
        string input;
        cin >> input;
        if (input == "0") return;
    }

    system("CLS");
    cout << "CREATE NEW COURSE\n";
    cout << "-----------------\n";
    dataCourse dataC;
    cout << "Enter course id : ";
    cin >> dataC.id;
    cout << "Enter course name : ";
    cin.ignore();
    getline(cin, dataC.course_name);
    cout << "Enter teacher name : ";
    cin.ignore();
    getline(cin, dataC.teacher_name);
    cout << "Enter number of credits : ";
    cin >> dataC.credits;
    cout << "Enter the maximum number of students in the course (default 50) :";
    cin >> dataC.max_students;
    cout << "Enter session 1's day (MON/ TUE/ WED/ THU/ FRI/ SAT): ";
    cin >> dataC.session1.day;
    cout << "Enter session 1's time [S1(07:30)/ S2(09:30)/ S3(13:30)/ S4(15:30)]: ";
    cin >> dataC.session1.time;
    cout << "Enter session 2's day (MON/ TUE/ WED/ THU/ FRI/ SAT): ";
    cin >> dataC.session2.day;
    cout << "Enter session 2's time [S1(07:30)/ S2(09:30)/ S3(13:30)/ S4(15:30)]: ";
    cin >> dataC.session2.time;
    push_course(headCourse, dataC);
    create_Course(headCourse);
}
void create_Semester(Semester* &headSemester){
    system("CLS");
    cout << "CREATE NEW SEMESTER\n";
    cout << "-------------------\n";
    dataSemester dataS;
    dataS.headCourse = NULL;
    cout << "Enter the semester you want to create (1, 2, 3) : ";
    cin >> dataS.num;
    cout << "Enter start date (YYYY/MM/DD) : ";
    cin >> dataS.startDate;
    cout << "Enter end date (YYYY/MM/DD) : ";
    cin >> dataS.endDate;
    cout << "Enter start registration date (YYYY/MM/DD) : ";
    cin >> dataS.startReg;
    cout << "Enter end registration date (YYYY/MM/DD) : ";
    cin >> dataS.endReg;
    create_Course(dataS.headCourse);
    push_Semester(headSemester, dataS);
}
void deleteCourse(Course* &curCourse, Course* &headCourse){
    if (!headCourse) return;

    if (curCourse->next == curCourse->prev){
        headCourse = NULL;
        delete headCourse;
        return;
    }

    if (!curCourse->prev){
        headCourse = curCourse->next;
        headCourse->prev = NULL;
    }
    else if (!curCourse->next) curCourse->prev->next = NULL;
    else{
        curCourse->prev->next = curCourse->next;
        curCourse->next->prev = curCourse->prev;
    }
    delete curCourse;
}
void changeCourseInfor(dataCourse &dataC, int x){
    if (x == 1){
        cout << "Enter course id : ";
        cin >> dataC.id;
    }
    else if (x == 2){
        cout << "Enter course name : ";
        cin.ignore();
        getline(cin, dataC.course_name);
    }
    else if (x == 3){
        cout << "Enter teacher name : ";
        cin.ignore();
        getline(cin, dataC.teacher_name);
    }
    else if (x == 4){
        cout << "Enter number of credits : ";
        cin >> dataC.credits;
    }
    else if (x == 5){
        cout << "Enter the maximum number of students in the course (default 50) :";
        cin >> dataC.max_students;
    }
    else if (x == 6){
        cout << "Enter session 1's day (MON/ TUE/ WED/ THU/ FRI/ SAT): ";
        cin >> dataC.session1.day;
        cout << "Enter session 1's time [S1(07:30)/ S2(09:30)/ S3(13:30)/ S4(15:30)]: ";
        cin >> dataC.session1.time;
    }
    else if (x == 7){
        cout << "Enter session 2's day (MON/ TUE/ WED/ THU/ FRI/ SAT): ";
        cin >> dataC.session2.day;
        cout << "Enter session 2's time [S1(07:30)/ S2(09:30)/ S3(13:30)/ S4(15:30)]: ";
        cin >> dataC.session2.time;
    }
}
void viewCourseInfor(Course* &curCourse, Course* &headCourse, Account* &curAccount, schoolYear* &headSchoolYear, bool studentMode){
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
    if (!studentMode) cout << "---> DELETE THIS COURSE!!! (Press x)\n";
    string input;
    cin >> input;
    if (input == "0") return;
    if (curAccount->data.accountType == "1"){
        cout << "(Select the information you want to change by enter number)\n";
        if (input == "x"){
            deleteCourse(curCourse, headCourse);
            return;
        }
        else changeCourseInfor(curCourse->data, int(char(input[0])) - 48);
        cout << "Complete!";
        getch();
        viewCourseInfor(curCourse, headCourse, curAccount, headSchoolYear, studentMode);
    }
    else if (input == "x" && !studentMode){
        string cName = curCourse -> data.course_name;
        deleteCourse(curCourse, headCourse);
        //FIX BUGS
        Semester *curSemester = headSchoolYear -> data.headSemester;
        bool FOUND = false;
        while (curSemester && !FOUND) {
            Course *crCourse = curSemester -> data.headCourse;
            while (crCourse && !FOUND) {
                if (crCourse -> data.course_name == cName) {
                    FOUND = true;
                    Account* delAccount = crCourse->data.hAccount;
                    while (delAccount){
                        if (delAccount->data.studentID == curAccount->data.studentID) break;
                        delAccount = delAccount->next;
                    }
                    deleteStudentInCourse(crCourse->data.hAccount, delAccount);
                    crCourse->data.nStudent--;
                    curAccount->data.nCourse--;
                }
                crCourse = crCourse -> next;
            }

            curSemester = curSemester -> next;
        }
        //FIX BUGS
        /** TEMP CLOSED
        Account* delAccount = curCourse->data.hAccount;
        while (delAccount){
            if (delAccount->data.studentID == curAccount->data.studentID) break;
            delAccount = delAccount->next;
        }
        deleteStudentInCourse(curCourse->data.hAccount, delAccount);
        curCourse->data.nStudent--;
        curAccount->data.nCourse--;
        **/
    }
}
void viewCourseList(Course* &headCourse, Account* &curAccount, schoolYear* &headSchoolYear, bool studentMode){
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

    curCourse = headCourse;
    cnt = int(char(input[0])) - 48;
    while (--cnt) curCourse = curCourse->next;
    viewCourseInfor(curCourse, headCourse, curAccount, headSchoolYear, studentMode);
    viewCourseList(headCourse, curAccount, headSchoolYear, studentMode);
}
void exportListStudent(Course* headCourse, Account* &curAccount, schoolYear* &headSchoolYear){
	
	
} 
schoolYear* chooseSchoolYear(schoolYear *headSchoolYear){
    system("CLS");
    if (!headSchoolYear){
        cout << "No school year available!";
        getch();
        return NULL;
    }
    cout << "CHOOSE SCHOOL YEAR\n";
    cout << "------------------\n";
    schoolYear *curSchoolYear = headSchoolYear;
    int i = 1;
    while (curSchoolYear){
        cout << i++ << ". " << curSchoolYear->data.startYear << " - " << curSchoolYear->data.endYear << endl;
        curSchoolYear = curSchoolYear->next;
    }
    string input;
    cin >> input;
    i = int(char(input[0])) - 48;
    curSchoolYear = headSchoolYear;
    while (--i) curSchoolYear = curSchoolYear->next;
    return curSchoolYear;
}
Semester* chooseSemester(Semester *headSemester){
    system("CLS");
    if (!headSemester){
        cout << "No semester available!";
        getch();
        return NULL;
    }
    cout << "CHOOSE SEMESTER\n";
    cout << "------------------\n";
    Semester *curSemester = headSemester;
    int i = 1;
    while (curSemester){
        cout << i << ". Semester " << i <<  endl;
        i++;
        curSemester = curSemester->next;
    }
    string input;
    cin >> input;
    i = int(char(input[0])) - 48;
    curSemester = headSemester;
    while (--i) curSemester = curSemester->next;
    return curSemester;
}
void staffProcess(Account* &curAccount, Account* &headAccount, Class* &headClass, schoolYear* &headSchoolYear){
    system("CLS");
    cout << "1. Create a new school year\n";
    cout << "2. Create new class\n";
    cout << "3. Add new 1st year students to 1st-year classes\n";
    cout << "4. Create a new semester\n";
    cout << "5. View classes list\n";
    cout << "6. View courses list\n";
    cout << "7. Export a list of students in a course\n";
    cout << "0. Back!\n";
    string input = "";
    cin >> input;
    if (input == "1") creatSchoolYear(headSchoolYear);
    else if (input == "2") createClass(headClass);
    else if (input == "3") add1stStudents(headAccount, headClass);
    else if (input == "4"){
        schoolYear* curSchoolYear = chooseSchoolYear(headSchoolYear);
        if (curSchoolYear) create_Semester(curSchoolYear->data.headSemester);
    }
    else if (input == "5") viewClass(headClass);
    else if (input == "6"){
        schoolYear* curSchoolYear = chooseSchoolYear(headSchoolYear);
        Semester* curSemester = NULL;
        if (curSchoolYear) curSemester = chooseSemester(headSchoolYear->data.headSemester);
        if (curSemester) viewCourseList(curSemester->data.headCourse, curAccount, headSchoolYear, false);
    }
    else if (input == "0") return;
//    updateSeverData(headSchoolYear);
    staffProcess(curAccount, headAccount, headClass, headSchoolYear);
}
