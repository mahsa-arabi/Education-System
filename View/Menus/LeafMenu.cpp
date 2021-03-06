#include "LeafMenu.h"
#include "CommandsFromFileMenu.h"

using namespace std;

LeafMenu::LeafMenu(std::string name, Menu* parent)
    : Menu{move(name), parent} {}

void LeafMenu:: showSubMenus() const {}

void LeafMenu::run() {
    setCurrentMenu(parent);

    if(name == "Show This Semester Courses"){
        showSemesterCourses();
    }

    else if(name == "Take Course"){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        string courseName;
        cout << "Enter Course Name: ";
        cin >> courseName;
        controller.takeCourse(ID, courseName);

    }

    else if(name == "Drop Course"){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        string courseName;
        cout << "Enter Course Name: ";
        cin >> courseName;
        controller.dropCourse(ID, courseName);
    }

    else if(name == "Show Student Courses In Current Semester"){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        showStuSemesterCourses(ID);
    }

    else if(name == "Calculate Student Salary"){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        cout << controller.findStudent(ID).calculateSalary() <<endl;
    }

    else if(name == "Show Professor Courses In Current Semester"){
        string ID;
        cout << "Enter Professor ID:";
        cin >> ID;
        showProfSemesterCourses(ID);
    }

    else if(name == "Submit Grade"){
        string courseName;
        cout << "Enter course name: ";
        cin >> courseName;
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        double grade;
        cout << "Enter the grade: ";
        cin >> grade;
        controller.submitGrade(courseName,ID,grade);
    }

    else if(name == "Calculate Professor Salary"){
        string ID;
        cout << "Enter Professor ID: ";
        cin >> ID;
        cout << controller.findProf(ID).calculateSalary() <<endl;
    }

    else if(name == "Add Professor"){
        string ID;
        cout << "Enter Professor ID: ";
        cin >> ID;
        string first;
        cout << "Enter Professor first name: ";
        cin >> first;
        string last;
        cout << "Enter Professor last name: ";
        cin >> last;
        string title;
        cout << "Enter Professor title: ";
        cin >> title;
        controller.addProfessor(ID,first,last,title);
    }

    else if(name == "Show Professors"){
        showProfessors();
    }

    else if(name == "Add Student"){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        string first;
        cout << "Enter First Name: ";
        cin >> first;
        string last;
        cout << "Enter Last Name: ";
        cin >> last;
        controller.addStudent(ID, first, last);
    }

    else if(name == "Show Students"){
        CommandsFromFileMenu::showStudents();
    }

    else if(name == "Add Course"){
        string courseName;
        cout << "Enter course name: ";
        cin >> courseName;
        string profLastName;
        cout << "Enter profLastName: ";
        cin >> profLastName;
        vector<string> preCourses;
        cout << "How many pre courses does it have? ";
        int a;
        cin >> a;
        for (int i = 0; i <a ; ++i) {
            string preCourse;
            cout << "Enter "<<(i+1)<<" th pre course: ";
            cin >> preCourse;
            if(!controller.inCourses(preCourse)){
                throw invalid_argument("The course hasn't found!");
            }else {
                preCourses.push_back(preCourse);
            }
        }
        controller.addCourse(courseName,profLastName,controller.currentSemester,preCourses);
    }

    else if(name == "Show All Courses"){
        showAllCourses();

    }
    else if(name == "Show Current Semester Courses"){
        showAllCourses();

    }else if(name == "Read Members From File"){
        int numOfMembers;
        cout << "Enter number of commands: ";
        cin >> numOfMembers;
        controller.readMembersFromFile(numOfMembers);

    }else if(name == "Calculate Total Salary"){
       cout<< controller.CalculateTotalSalaryMath()<<endl;
    }else{
        throw invalid_argument("This Menu has not been defined!!");
    }
}

void LeafMenu::showAllCourses() {
    for(const auto& crs : controller.courses){
        cout << crs.toString() << endl;
    }
}

void LeafMenu::showSemesterCourses() {
    for(const auto& crs : controller.currentSemesterCourses){
        cout << crs.toString() << endl;
    }
}

void LeafMenu::showStuSemesterCourses(std::string studentId) {
        auto iter = controller.findStudent(studentId).getCurrentSemesterCourses().begin();
        while(iter != controller.findStudent(studentId).getCurrentSemesterCourses().end()){
            string name=iter->first;
            cout << name <<endl;
            iter++;
        }
}

void LeafMenu::showProfSemesterCourses(std::string profId) {
    for(const auto& crs : controller.currentSemesterCourses){
        if(crs.getProfLastName()== controller.findProf(profId).getLastName()){
            cout << crs.getCourseName() <<endl;
        }
    }
}

void LeafMenu::showProfessors() {
    for(const auto& prof : controller.professors){
        cout << prof.toString() << endl;
    }

}

void LeafMenu::showCurrentCourses() {
    for (const auto& crs : controller.courses) {
        if(crs.getSemester()==controller.currentSemester){
            crs.toString();
        }
    }

}
