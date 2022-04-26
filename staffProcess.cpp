#include "functionPrototype.h"

void createSchoolYear(schoolYear* &headSchoolYear){
	TextColor(15);
    system("CLS");
    cout << "\t\tCREATE NEW SCHOOL YEAR\n";
    cout << "-------------------------------------------------------\n";
    dataSchoolYear input;
    cout << "Enter the start year of the new school year: ";
    cin >> input.startYear;
    cout << "Enter the end year of the new school year: ";
    cin >> input.endYear;
    pushBackSchoolYear(headSchoolYear, input);
}
void createClass(Class* &headClass){
	TextColor(15);
    system("CLS");
    cout << "\t\t    CREATE NEW CLASS\n";
    cout << "--------------------------------------------------------\n";
    cout << "Enter the class's name: ";
    string className;
    cin >> className;
    pushBackClass(headClass, className);
}
void viewStudentInCourse(Course* curCourse){
	TextColor(11);
    system("CLS");
    cout << "     " << curCourse->data.course_name << " STUDENTS LIST\n";
    cout << "-----------------------------\n";
    TextColor(15);
    Account* headStudent = curCourse->data.hAccount;
    if (!headStudent){
        cout << "No student in this courses!";
        getch();
        return;
    }
    int cnt = 0;
    while (headStudent){
        cout << ++cnt << ". " << headStudent->data.studentID << " - "
        << headStudent->data.lastName << " " << headStudent->data.firstName << endl;
        headStudent = headStudent->next;
    }
    getch();
}
void viewStudentInClass(Class* curClass){
	TextColor(11);
    system("CLS");
    cout << "     " << curClass->data.className << " STUDENTS LIST\n";
    cout << "-------------------------------\n";
    TextColor(15);
    Account* headStudent = curClass->data.student;
    if (!headStudent){
        cout << "No student in this class!";
        getch();
        return;
    }
    int cnt = 0;
    while (headStudent){
        cout << ++cnt << ". " << headStudent->data.studentID << " - "
        << headStudent->data.lastName << " " << headStudent->data.firstName << endl;
        headStudent = headStudent->next;
    }
    getch();
}
void viewClass(Class* headClass){
	TextColor(11);
    system("CLS");
    if (!headClass){
        cout << "No class available!";
        getch();
        return;
    }

    cout << "CLASSES LIST\n";
    cout << "------------\n";
    TextColor(15);
    int cnt = 0;
    Class *curClass = headClass;
    while (curClass){
        cout << ++cnt << ". " << curClass->data.className << endl;
        curClass = curClass->next;
    }
    cout << "0. Back!\n";
    string input;
    cin >> input;
    if (input[0] < '0' || input[0] > cnt + '0'){
        cout << "Wrong input, try again!";
        getch();
        viewClass(headClass);
        return;
    }
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
	TextColor(15);
    if (headCourse){
        system("CLS");
        cout << "1. Create new courses\n";
        cout << "0. Back\n";
        string input;
        cin >> input;
        if (input == "0") return;
    }

    system("CLS");
    cout << "\t\t\tCREATE NEW COURSE\n";
    cout << "-----------------------------------------------------------------\n";
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
	TextColor(11);
    system("CLS");
    cout << "\t\t  CREATE NEW SEMESTER\n";
    cout << "--------------------------------------------------------\n";
    TextColor(15);
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
void viewCourseInfor(Course* &curCourse, Course* &headCourse, Account* &curAccount, Account* &headAccount, schoolYear* &curSchoolYear, schoolYear* &headSchoolYear, bool studentMode){
    TextColor(11);
	system("CLS");
    cout << "\t\t     COURSES INFORMATION\n";
    cout << "------------------------------------------------------------\n";
    TextColor(15);
    dataCourse dataC = curCourse->data;
    cout << "1. ID: " << dataC.id << endl;
    cout << "2. Name: " << dataC.course_name << endl;
    cout << "3. Teacher's name: " << dataC.teacher_name << endl;
    cout << "4. Credits: " << dataC.credits << endl;
    cout << "5. Max Students: " << dataC.max_students << endl;

    string sesTime[4] = {"7h30", "9h30", "13h30", "15h30"};
    cout << "6. Session 1: " << dataC.session1.day <<" - " << sesTime[int(char(dataC.session1.time[1]))-49] << endl;
    cout << "7. Session 2: " << dataC.session2.day <<" - " << sesTime[int(char(dataC.session2.time[1]))-49] << endl;
    if (curAccount->data.accountType == "1"){
        cout << "8. View students list\n";
        cout << "9. Export students list\n";
    }
    cout << "0. Back!\n";
    if (!studentMode) cout << "---> DELETE THIS COURSE!!! (Press x)\n";
    if (curAccount->data.accountType == "1") cout << "(Select the information you want to change by enter number)\n";
    string input;
    cin >> input;
    if (input != "x" && (input[0] < '0' || input[0] > '9')){
        cout << "Wrong input, try again!";
        getch();
        viewCourseInfor(curCourse, headCourse, curAccount, headAccount, curSchoolYear, headSchoolYear, studentMode);
        return;
    }
    if (input == "0") return;
    if (curAccount->data.accountType == "1"){
        if (input == "x"){
            Account* delAccount = headAccount;
            while (delAccount){
                Course* courseInAccount = delAccount->data.hCourse;
                while (courseInAccount){
                    if (courseInAccount->data.id == curCourse->data.id) break;
                    courseInAccount = courseInAccount->next;
                }
                if (!courseInAccount) break;
                delAccount->data.nCourse--;
                deleteCourse(courseInAccount, delAccount->data.hCourse);
                delAccount = delAccount->next;
            }
            deleteCourse(curCourse, headCourse);
            return;
        }
        else if (input == "8") viewStudentInCourse(curCourse);
        else if (input == "9"){
            exportStudentsList(curSchoolYear, curCourse->data);
            cout << "Export complete!";
            getch();
        }
        else{
            changeCourseInfor(curCourse->data, convertToInt(input));
            cout << "Complete!";
            getch();
        }
        viewCourseInfor(curCourse, headCourse, curAccount, headAccount, curSchoolYear, headSchoolYear, studentMode);
    }
    else if (input == "x" && !studentMode){
        string cName = curCourse -> data.course_name;
        deleteCourse(curCourse, headCourse);
        Semester *curSemester = curSchoolYear -> data.headSemester;
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
                    curCourse->data.nStudent = max(0, curCourse->data.nStudent);
                    curAccount->data.nCourse = max(0, curAccount->data.nCourse);
                }
                crCourse = crCourse -> next;
            }
            curSemester = curSemester -> next;
        }
    }
}
bool viewCourseList(Course* &headCourse, Account* &curAccount, Account* &headAccount, schoolYear* &curSchoolYear, schoolYear* &headSchoolYear, bool studentMode){
    TextColor(11);
	system("CLS");
    if (!headCourse){
        cout << "No course available!";
        getch();
        return true;
    }
    cout << "\t\tCOURSES LIST\n";
    cout << "--------------------------------------------\n";
    TextColor(15);
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
    if (input[0] < '0' || input[0] > cnt + '0'){
        cout << "Wrong input, try again!";
        getch();
        return viewCourseList(headCourse, curAccount, headAccount, curSchoolYear, headSchoolYear, studentMode);
    }
    if (input == "0") return false;

    curCourse = headCourse;
    cnt = convertToInt(input);
    while (--cnt) curCourse = curCourse->next;
    TextColor(15);
    viewCourseInfor(curCourse, headCourse, curAccount, headAccount, curSchoolYear, headSchoolYear, studentMode);
    return viewCourseList(headCourse, curAccount, headAccount, curSchoolYear, headSchoolYear, studentMode);
}
schoolYear* chooseSchoolYear(schoolYear *headSchoolYear){
	TextColor(11);
    system("CLS");
    if (!headSchoolYear){
        cout << "No school year available!";
        getch();
        return NULL;
    }
    cout << "CHOOSE SCHOOL YEAR\n";
    cout << "------------------\n";
    TextColor(15);
    schoolYear *curSchoolYear = headSchoolYear;
    int i = 1;
    while (curSchoolYear){
        cout << i++ << ". " << curSchoolYear->data.startYear << " - " << curSchoolYear->data.endYear << endl;
        curSchoolYear = curSchoolYear->next;
    }
    cout << "0. Back!\n";
    string input;
    cin >> input;
    if (input[0] < '0' || input[0] > i + '0'){
        cout << "Wrong input, try again!";
        getch();
        return chooseSchoolYear(headSchoolYear);
    }
    i = convertToInt(input);
    if (i == 0) return NULL;
    curSchoolYear = headSchoolYear;
    while (--i) curSchoolYear = curSchoolYear->next;
    return curSchoolYear;
}
Semester* chooseSemester(Semester *headSemester){
	TextColor(11);
    system("CLS");
    if (!headSemester){
        cout << "No semester available!";
        getch();
        return NULL;
    }
    cout << "CHOOSE SEMESTER\n";
    cout << "------------------\n";
    TextColor(15);
    Semester *curSemester = headSemester;
    int i = 1;
    while (curSemester){
        cout << i << ". Semester " << i <<  endl;
        i++;
        curSemester = curSemester->next;
    }
    cout << "0. Back!\n";
    string input;
    cin >> input;
    if (input[0] < '0' || input[0] > i + '0'){
        cout << "Wrong input, try again!";
        getch();
        return chooseSemester(headSemester);
    }
    i = convertToInt(input);
    if (i == 0) return NULL;
    curSemester = headSemester;
    while (--i) curSemester = curSemester->next;
    return curSemester;
}
void viewScoreBoardInCourse_A(Course* &curCourse){
	TextColor(11);
    Account* headAccount = curCourse->data.hAccount;
    system("CLS");
    if (!headAccount){
        cout << "No student in this course!";
        getch();
        return;
    }
    cout << "\t\t\t\tSTUDENTS SCORE BOARD LIST\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    TextColor(15);
    Account *curAccount = headAccount;
    int cnt = 0;
    cout << "| No | Student ID |   Full Name   | Total Mark | Final Mark | Midterm Mark | Other Mark |\n";
    while (curAccount){
        dataAccount dataA = curAccount->data;
        cout << "|" << setw(4) << ++cnt
        << "|" << setw(12) << dataA.studentID
        << "|" << setw(15)  << dataA.firstName + ' ' + dataA.lastName
        << "|" << setw(12) << dataA.hCourse->data.totalMark
        << "|" << setw(12) << dataA.hCourse->data.finalMark
        << "|" << setw(14) << dataA.hCourse->data.midtermMark
        << "|" << setw(12) << dataA.hCourse->data.otherMark << "|\n";
        curAccount = curAccount->next;
    }
    getch();
}
void viewScoreBoardInCourse_C(Course* &headCourse){
	TextColor(11);
    system("CLS");
    if (!headCourse){
        cout << "No course available!";
        getch();
        return;
    }
    cout << "\t\tCOURSES LIST\n";
    cout << "-----------------------------------------------\n";
    TextColor(15);
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
    if (input[0] < '0' || input[0] > cnt + '0'){
        cout << "Wrong input, try again!";
        getch();
        viewScoreBoardInCourse_C(headCourse);
        return;
    }
    if (input == "0") return;

    curCourse = headCourse;
    cnt = convertToInt(input);
    while (--cnt) curCourse = curCourse->next;
    viewScoreBoardInCourse_A(curCourse);
    viewScoreBoardInCourse_C(headCourse);
}
void viewScoreBoardInCourse_S(Semester* &headSemester){
	TextColor(11);
    system("CLS");
    if (!headSemester){
        cout << "No semester available!";
        getch();
        return;
    }
    cout << "CHOOSE SEMESTER\n";
    cout << "------------------\n";
    TextColor(15);
    Semester *curSemester = headSemester;
    int i = 1;
    while (curSemester){
        cout << i << ". Semester " << i <<  endl;
        i++;
        curSemester = curSemester->next;
    }
    cout << "0. Back!\n";
    string input;
    cin >> input;
    if (input[0] < '0' || input[0] > i + '0'){
        cout << "Wrong input, try again!";
        getch();
        viewScoreBoardInCourse_S(headSemester);
        return;
    }
    i = convertToInt(input);
    if (i == 0) return;
    curSemester = headSemester;
    while (--i) curSemester = curSemester->next;
    viewScoreBoardInCourse_C(curSemester->data.headCourse);
    viewScoreBoardInCourse_S(headSemester);
}
void viewScoreBoardInCourse_SY(schoolYear* &headSchoolYear){
	TextColor(11);
    system("CLS");
    if (!headSchoolYear){
        cout << "No school year available!";
        getch();
        return;
    }
    cout << "CHOOSE SCHOOL YEAR\n";
    cout << "------------------\n";
    TextColor(15);
    schoolYear *curSchoolYear = headSchoolYear;
    int i = 1;
    while (curSchoolYear){
        cout << i++ << ". " << curSchoolYear->data.startYear << " - " << curSchoolYear->data.endYear << endl;
        curSchoolYear = curSchoolYear->next;
    }
    cout << "0. Back!\n";
    string input;
    cin >> input;
    if (input[0] < '0' || input[0] > i + '0'){
        cout << "Wrong input, try again!";
        getch();
        viewScoreBoardInCourse_SY(headSchoolYear);
        return;
    }
    i = convertToInt(input);
    if (i == 0) return;
    curSchoolYear = headSchoolYear;
    while (--i) curSchoolYear = curSchoolYear->next;
    viewScoreBoardInCourse_S(curSchoolYear->data.headSemester);
    viewScoreBoardInCourse_SY(headSchoolYear);
}
double calculateFinalMark(Account* curAccount){
    double res = 0;
    int cnt = 0;
    Course* curCourse = curAccount->data.hCourse;
    while (curCourse){
        cnt++;
        res += curCourse->data.totalMark;
        curCourse = curCourse->next;
    }
    return res / double(cnt);
}
double calculateOverallGPA(Account* curAccount, schoolYear* curSchoolYear){
    double resOverall = 0;
    Semester* curS =curSchoolYear->data.headSemester;
    int cntS = 0;
    while (curS){
        Course* curC = curS->data.headCourse;
        double resS = 0;
        int cntC = 0;
        while (curC){
            Account* curStudent = curC->data.hAccount;
            while (curStudent){
                if (curStudent->data.studentID == curAccount->data.studentID){
                    resS += curStudent->data.hCourse->data.totalMark;
                    cntC++;
                }
                curStudent = curStudent->next;
            }
            curC = curC->next;
        }
        if (!cntC) cntC++;
        resOverall += resS / double(cntC);
        cntS++;
        curS = curS->next;
    }
    return resOverall / double(cntS);
}
void viewScoreBoardInClass_Student(Class* &curClass, schoolYear* curSchoolYear){
	TextColor(11);
    system("CLS");
    cout << "\t\t\t" << curClass->data.className << " STUDENTS LIST\n";
    cout << "--------------------------------------------------------------------\n";
    TextColor(15);
    Account* headStudent = curClass->data.student;
    if (!headStudent){
        cout << "No student in this class!";
        getch();
        return;
    }
    time_t now = time(NULL);
    tm *const Date = localtime(&now);
    string yearNow = to_string(1900 + Date->tm_year);
    while (curSchoolYear){
        if (curSchoolYear->data.startYear <= yearNow && yearNow <= curSchoolYear->data.endYear)
            break;
        curSchoolYear = curSchoolYear->next;
    }
    cout << "| No | Student ID |   Full Name   | Final Mark | GPA | Overall GPA |\n";
    int cnt = 0;
    Account* curAccount = headStudent;
    while (curAccount){
        dataAccount dataA = curAccount->data;
        double finalMark = calculateFinalMark(curAccount);
        double overallGPA = calculateOverallGPA(curAccount, curSchoolYear) / 2.5;
        double GPA = finalMark / 2.5;
        cout << "|" << setw(4) << ++cnt
        << "|" << setw(12) << dataA.studentID
        << "|" << setw(15)  << dataA.firstName + ' ' + dataA.lastName
        << "|" << setw(12) << setprecision(3) <<  finalMark
        << "|" << setw(5) << setprecision(3) <<  GPA
        << "|" << setw(13) << setprecision(3) <<  overallGPA << "|\n";
        curAccount = curAccount->next;
    }
    getch();
}
void viewScoreBoardInClass_Class(Class* &headClass, schoolYear* curSchoolYear){
	TextColor(11);
    system("CLS");
    if (!headClass){
        cout << "No class available!";
        getch();
        return;
    }

    cout << "CLASSES LIST\n";
    cout << "------------\n";
    TextColor(15);
    int cnt = 0;
    Class *curClass = headClass;
    while (curClass){
        cout << ++cnt << ". " << curClass->data.className << endl;
        curClass = curClass->next;
    }
    cout << "0. Back!\n";
    string input;
    cin >> input;
    if (input[0] < '0' || input[0] > cnt + '0'){
        cout << "Wrong input, try again!";
        getch();
        viewScoreBoardInClass_Class(headClass, curSchoolYear);
        return;
    }
    if (input == "0") return;
    curClass = headClass;
    cnt = convertToInt(input);
    while (--cnt) curClass = curClass->next;
    viewScoreBoardInClass_Student(curClass, curSchoolYear);
    viewScoreBoardInClass_Class(headClass, curSchoolYear);
}
void createNewSY(schoolYear* &headSchoolYear){
    schoolYear* curSchoolYear = chooseSchoolYear(headSchoolYear);
    if (curSchoolYear) create_Semester(curSchoolYear->data.headSemester);
}
void viewCourseList_Staff(schoolYear* &headSchoolYear, Account* &headAccount, Account* &curAccount){
    while (true){
        schoolYear* curSchoolYear = chooseSchoolYear(headSchoolYear);
        Semester* curSemester = NULL;
        if (!curSchoolYear) break;
        while (true){
            if (curSchoolYear) curSemester = chooseSemester(curSchoolYear->data.headSemester);
            else break;
            if (!curSemester) break;
            while (true){
                bool checkBack = true;
                if (curSemester) checkBack = viewCourseList(curSemester->data.headCourse, curAccount, headAccount, curSchoolYear, headSchoolYear, false);
                else break;
                if (!checkBack) break;
            }
        }
    }
    TextColor(15);
}
void staffProcess(Account* &curAccount, Account* &headAccount, Class* &headClass, schoolYear* &headSchoolYear){
    system("CLS");
    cout << "1. Create a new school year\n";
    cout << "2. Create new class\n";
    cout << "3. Add new 1st year students to 1st-year classes\n";
    cout << "4. Create a new semester\n";
    cout << "5. View classes list\n";
    cout << "6. View courses list\n";
    cout << "7. Import scoreboard\n";
    cout << "8. View score board in courses\n";
    cout << "9. View score board in classes\n";
    cout << "0. Back!\n";
    string input = "";
    cin >> input;
    if (input == "1") createSchoolYear(headSchoolYear);
    else if (input == "2") createClass(headClass);
    else if (input == "3") add1stStudents(headAccount, headClass);
    else if (input == "4") createNewSY(headSchoolYear);
    else if (input == "5") viewClass(headClass);
    else if (input == "6") viewCourseList_Staff(headSchoolYear, headAccount, curAccount);
    else if (input == "7") importStudentsList(headAccount, headSchoolYear);
    else if (input == "8") viewScoreBoardInCourse_SY(headSchoolYear);
    else if (input == "9") viewScoreBoardInClass_Class(headClass, headSchoolYear);
    else if (input == "0") return;
    else{
        cout << "Wrong input, try again!";
        getch();
        staffProcess(curAccount, headAccount, headClass, headSchoolYear);
        return;
    }
    updateAccountCourse(headSchoolYear);
    staffProcess(curAccount, headAccount, headClass, headSchoolYear);
}
