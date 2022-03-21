#include "functionPrototype.h"

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
    while (cur->next)
        cur = cur->next;
    newSchoolYear->prev = cur;
    cur->next = newSchoolYear;
}
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
    while (cur->next)
        cur = cur->next;
    newClass->prev = cur;
    cur->next = newClass;
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
void showClass(Class* headClass){
    system("CLS");
    if (!headClass){
        cout << "No class available!";
        getch();
        return;
    }

    cout << "CLASSES LIST\n";
    cout << "------------\n";
    Class *curClass = headClass;
    while (curClass){
        cout << curClass->data.className << endl;
        Account *curStudent = curClass->data.student;
        if (!curStudent) cout << "No student in this class!";
        while (curStudent){
            cout << curStudent->data.firstName << " ";
            curStudent = curStudent->next;
        }
        curClass = curClass->next;
        cout << endl;
    }
    getch();
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

    lastStudent->next = curStudent;
    curStudent->prev = lastStudent;
}
void add1stStudents(Account* headAccount, Class* &headClass){
    if (!headClass){
        system("CLS");
        cout << "No class available!";
        getch();
        return;
    }
    Class* curClass = headClass;
    while (curClass){
        Account* curAccount = headAccount;
        while (curAccount){
            if (curAccount->data._class == curClass->data.className){
                Account* newStudent = getAccount(curAccount->data);
                pushBackStudent(newStudent, curClass->data.student);
            }
            curAccount = curAccount->next;
        }
        curClass = curClass->next;
    }
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
    while (curCourse->next)
        curCourse = curCourse->next;
    newCourse->prev = curCourse;
    curCourse->next = newCourse;
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
    while (curSemester->next)
        curSemester = curSemester->next;
    newSemester->prev = curSemester;
    curSemester->next = newSemester;
}
void create_Semester(Semester* &headSemester){
    system("CLS");
    cout << "CREATE NEW SEMESTER\n";
    cout << "-------------------\n";
    dataSemester dataS;
    dataS.headCourse = NULL;
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
    push_Semester(headSemester, dataS);
}
void viewCourseList(Course* headCourse){
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
    while (curCourse) {
        cnt++;
        dataCourse dataC = curCourse->data;
        cout << cnt << ". " << dataC.course_name << '\n';
        curCourse = curCourse->next;
    }
    getch();
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
    else if (input == "5") showClass(headClass);
    else if (input == "6"){
        schoolYear* curSchoolYear = chooseSchoolYear(headSchoolYear);
        Semester* curSemester = NULL;
        if (curSchoolYear) curSemester = chooseSemester(headSchoolYear->data.headSemester);
        if (curSemester) viewCourseList(curSemester->data.headCourse);
    }
    else if (input == "0") return;
    updateSeverData(headSchoolYear);
    staffProcess(curAccount, headAccount, headClass, headSchoolYear);
}

