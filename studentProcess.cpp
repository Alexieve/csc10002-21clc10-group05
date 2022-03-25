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
    chooseCourseEnrolled(headCourses);
}
bool isDuplicated(Course* headCourse, ){
	Course* pCur = headCourse;
	while()
}
int chooseCourseEnrolled(Course* headCourse){
	int choose_num;
	cout << "Enter the ordinal number of the course you want to register for: ";
	cin >> choose_num;
	int num_student = 0;
	int num_courses = 0;
	Course* cur = headCourse;
	while(cur){
		if(choose_num == cur->data.id){
			if(isDuplicated())
				chooseCourseEnrolled(headCourses);
			else{
				num_course++;
				if(num_course + 1 > 5){
					cout << "Cannot continue to register because you have registed 5 courses!";
				}
				else{
					num_student++;
					if(num_course + 1 > 50){
						cout << "Cannot continue to register because this course is full, please choose another courses!";
						chooseCourseEnrolled(headCourses);
					}
					else{
						//  push curAccount into curCourse->data.studentList and push course into curAccount->data.courseList
					}
				}
			}
		}
	}
	cout << "Complete enrolling!!!";
}
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
