#include "functionPrototype.h"

schoolYear* getSchoolYear(schoolYear newData){
    schoolYear* newNode = new schoolYear;
    newNode->startYear = newData.startYear;
    newNode->endYear = newData.endYear;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBackSchoolYear(schoolYear* &head, schoolYear newData){
    schoolYear* newSchoolYear = getSchoolYear(newData);
    if (head == NULL){
        head = newSchoolYear;
        return;
    }

    schoolYear* cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    newSchoolYear->prev = cur;
    cur->next = newSchoolYear;
}
void creatSchoolYear(schoolYear* &headSchoolYear){
    system("CLS");
    schoolYear input;
    cout << "Enter the start year of the new school year: ";
    cin >> input.startYear;
    cout << "Enter the end year of the new school year: ";
    cin >> input.endYear;
    pushBackSchoolYear(headSchoolYear, input);
}
Class* getClass(string newData){
    Class* newNode = new Class;
    newNode->className = newData;
    newNode->student = NULL;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushBackClass(Class* &head, string newData){
    Class* newClass = getClass(newData);
    if (head == NULL){
        head = newClass;
        return;
    }

    Class* cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    newClass->prev = cur;
    cur->next = newClass;
}
void createClass(Class* &headClass){
    system("CLS");
    cout << "Enter the class's name: ";
    string className;
    cin >> className;
    pushBackClass(headClass, className);
}
void pushBackStudent(User* curStudent, Class* &curClass){
    if (curClass->student == NULL){
        curClass->student = curStudent;
        return;
    }
    User* lastStudent = curClass->student;
    while (lastStudent->next != NULL)
        lastStudent = lastStudent->next;

    lastStudent->next = curStudent;
    curStudent->prev = lastStudent;
}
void add1stStudents(Account* headAccount, Class* &headClass){
    Account* curAccount = headAccount;
    while (curAccount->prev != NULL)
        curAccount = curAccount->prev;

    while (curAccount){
        if (curAccount->data.accountType == "2"){
            Class* curClass = headClass;
            while (curClass && curClass->className != curAccount->data._class)
                curClass = curClass->next;
            pushBackStudent(&(curAccount->data), curClass);
        }
        curAccount = curAccount->next;
    }
}

void push_Semester(Semester* &headSemester, dataSemester dataS) {
    Semester *tmp = headSemester;
    if (tmp == NULL) {
        headSemester -> data = dataS;
    }
    else {
        Semester *new_semester = new Semester();
        while (tmp -> next != NULL)
            tmp = tmp -> next;

        new_semester -> data = dataS;
        new_semester -> next = NULL;
        new_semester -> prev = tmp;
        tmp -> next = new_semester;
    }
}

void push_course(Course* &headCourse, dataCourse dataC) {
    Course *tmp = headCourse;
    if (tmp == NULL) {
        headCourse -> data = dataC;
    }
    else {
        Course *new_course = new Course();
        while (tmp -> next != NULL)
            tmp = tmp -> next;

        new_course -> data = dataC;
        new_course -> next = NULL;
        new_course -> prev = tmp;
        tmp -> next = new_course;
    }
}

void create_Course(Course* &headCourse) {
    system("CLS");
    dataCourse dataC;
    cout << "Enter course id : ";
    cin >> dataC.id;
    cout << "Enter course name : ";
    cin.ignore();
    getline(cin, dataC.course_name);
    cout << "Enter number of credits : ";
    cin >> dataC.credits;
    cout << "Enter the maximum number of students in the course (default 50) :";
    cin >> dataC.max_students;
    cout << "Enter session 1 day (MON/ TUE/ WED/ THU/ FRI/ SAT): ";
    cin >> dataC.session1.day;
    cout << "Enter session 1 time [S1(07:30)/ S2(09:30)/ S3(13:30)/ S4(15:30)]: ";
    cin >> dataC.session1.time;
    cout << "Enter session 2 day (MON/ TUE/ WED/ THU/ FRI/ SAT): ";
    cin >> dataC.session2.day;
    cout << "Enter session 2 time [S1(07:30)/ S2(09:30)/ S3(13:30)/ S4(15:30)]: ";
    cin >> dataC.session2.time;
}

void create_Semester(Semester* &headSemester) {
    system("CLS");
    dataSemester dataS;
    cout << "Enter the semester you want to create (1, 2, 3) : ";
    cin >> dataS.num;
    cout << "Enter the start year : ";
    cin >> dataS.startYear;
    cout << "Enter the end year : ";
    cin >> dataS.endYear;
    cout << "Enter start date : ";
    cin >> dataS.startDate;
    cout << "Enter end date : ";
    cin >> dataS.endDate;
    create_Course(dataS.headCourse);

    headSemester -> data = dataS;
}

void view_courselist(Course* headCourse) {
    Course *tmp = headCourse;

    system("CLS");
    int cnt = 0;
    while (tmp != NULL) {
        cnt++;
        dataCourse dataC = tmp -> data;
        cout << cnt << " : " << dataC.course_name << '\n';
        tmp = tmp -> next;
    }
}

void staffProcess(Account* &curAccount, Class* &headClass, schoolYear* &headSchoolYear){
    system("CLS");
    cout << "1. Create a new school year\n";
    cout << "2. Create new class\n";
    cout << "3. Add new 1st year students to 1st-year classes\n";
    cout << "4. Create a new semester\n";
    string input = "";
    cin >> input;
    if (input == "1") creatSchoolYear(headSchoolYear);
    else if (input == "2") createClass(headClass);
    else if (input == "3") add1stStudents(curAccount, headClass);
}

