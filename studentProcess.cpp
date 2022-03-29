#include "functionPrototype.h"

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
    viewCourseList(curS->data.headCourse, curAccount);
    /// choose course to enroll
    /// check if this course is not conflict with exist course
    /// if not conflict, then push curAccount into curCourse->data.studentList
    /// and push course into curAccount->data.courseList
    /// and increase course->data.numStudent by 1 (max = maxStudent)
    /// and increase curAccount->data.numCourse by 1 (max = 5)
    /// if conflict, then announce that this course is conflict with other course

    /// how to check conflict is create a linked list have 6 days from MON - SAT
    /// each day will have 4 times (S1 - S4)
    /// when success enroll a course, push day and time into this linked list of curAccount   
}
// create linked list have 6 days
Day* getDay(dataDay newData){
    Day* newNode = new Day;
    newNode->data.name = newData.name;
    newNode->data.time1 = newData.time1;
    newNode->data.time2 = newData.time2;
    newNode->data.time3 = newData.time3;
    newNode->data.time4 = newData.time4;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
void pushDay(Day* &head, dataDay newData){
    Day* newDay = getDat(newData);
    if (!head){
        head = Day;
        return;
    }

    Day* cur = head;
    while (cur->next){
        if (cur->data.time1 == newData.time1 && cur->data.time2 == newData.time2 && cur->data.time3 == newData.time3 && cur->data.time4 == newData.time4) return;
        cur = cur->next;
    }
    if (cur->data.time1 == newData.time1 && cur->data.time2 == newData.time2 && cur->data.time3 == newData.time3 && cur->data.time4 == newData.time4) return;
    newDay->prev = cur;
    cur->next = newDay;
}
/*
void createDay(Day* &headDay, Course *headCourse){
	dataDay dataD;
	dataD.name = headCourse->data.session1.day;
    pushDay(headDay, dataD);
}
*/
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
    else if (input == "2") viewEnrolledCourse(curAccount -> data);
    else if (input == "3")  
    else if (input == "0") return;
    studentProcess(curAccount, headAccount, headClass, headSchoolYear);
}
