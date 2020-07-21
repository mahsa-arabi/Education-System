#include "Controller.h"
#include "../Model/DoubleMajorStudent.h"
#include "../Model/Student.h"
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>


using namespace std;

Controller::Controller(std::string currentSemester)
   : currentSemester{move(currentSemester)} {}


void Controller:: load(){
    ifstream inputStu("students.txt");
    int studentSize;
    inputStu >> studentSize;
    Student stu;
    for( size_t i{0}; i < studentSize; ++i ){
        inputStu >> stu;
        students.push_back(stu);
    }
    inputStu.close();

    ifstream inputProf("professors.txt");
    int profSize;
    inputProf >> profSize;
    Professor prof;
    for( size_t i{0}; i < profSize; ++i){
        inputProf >> prof;
        professors.push_back(prof);
    }
    inputProf.close();

    ifstream inputCourse("courses.txt");
    int courseSize;
    inputCourse >> courseSize;
    Course crs;
    for( size_t i{0}; i < courseSize; ++i){
        inputCourse >> crs;
        courses.push_back(crs);
        if(crs.semester == currentSemester){
            currentSemesterCourses.push_back(crs);
        }
    }
    inputCourse.close();
}

void Controller::save() const{
    ofstream outputStu("students.txt", ios::out);
    outputStu << students.size() << endl;
    for( auto const& stu : students ){
        outputStu << stu << endl;
    }
    outputStu.close();

    ofstream outputProf("professors.txt");
    outputProf << professors.size() << endl;
    for( const auto& prof : professors ){
        outputProf << prof << endl;
    }
    outputProf.close();

    ofstream outputCourse("courses.txt");
    outputCourse << courses.size() << endl;
    for( auto const& crs : courses ){
        outputCourse << crs << endl;
    }
    outputCourse.close();
}

void Controller:: addStudent(std::string ID, std::string first, std::string last){
    if(!inStudents(ID)){
        Student stu{move(ID), move(first), move(last), 0,
                    vector<string>{}, map<string, double>{}};
        students.push_back(stu);
    }
}

void Controller:: addProfessor(std::string ID, std::string first,
        std::string last, std::string title){
    if(!inProfessors(ID)){
        Professor prof{move(ID), move(first), move(last), 0, move(title)};
        professors.push_back(prof);
    }
}

void Controller:: addCourse(std::string courseName, std::string profLast, std::string semester,
               std::vector<std::string> pre){
    if( !inCourses(courseName) && inProfessorsByLastName(profLast) ){
        Course crs{move(courseName), move(profLast), move(semester), move(pre)};
        courses.push_back(crs);
        if( crs.semester == currentSemester){
            currentSemesterCourses.push_back(crs);
        }
    }else{
        throw invalid_argument("the course is already is in courses (or) the professors is not in the list!");
    }

}

bool Controller::inStudents(const std::string& ID) const{
    for( const auto& stu : students ){
        if( stu.studentId == ID){
            return true;
        }
    }
    return false;
}

bool Controller::inProfessors(const std::string& ID) const{
    for( const auto& prof : professors ){
        if( prof.profId == ID){
            return true;
        }
    }
    return false;
}

bool Controller::inCourses(const std::string& courseName) const{
    for( const auto& crs : courses ){
        if( crs.courseName == courseName){
            return true;
        }
    }
    return false;
}

bool Controller:: inProfessorsByLastName(const std::string& last) const{
    for( const auto& prof : professors ){
        if( prof.getLastName() == last){
            return true;
        }
    }
    return false;
}

Student& Controller:: findStudent(string ID){
    for( auto& stu : students ){
        if(stu.studentId == ID){
            return stu;
        }
    }
    throw invalid_argument("The Student was not found!!");
}
Professor& Controller::findProf(std::string ID){
    for( auto& prof : professors ){
        if(prof.profId == ID){
            return prof;
        }
    }
    throw invalid_argument("The Professor was not found!!");
}
Course& Controller::findCourse(std::string courseName){
    for( auto& course : courses ){
        if(course.getCourseName()==courseName){
            return course;
        }
    }
    throw invalid_argument("The course was not found!");
}
void Controller:: takeCourse(const std::string& studentID, const std::string& courseName){
    bool ok=true;
    for(auto& course:findCourse(courseName).preCourses){
            if(!isPassed(studentID,course)){
                ok=false;
            }
    }
    if(ok) {
        if (!inStudents(studentID)) {
            throw invalid_argument("The student was not found!");
        } else {
                if (inCourses(courseName)) {
                    findStudent(studentID).currentSemesterCourses.insert({courseName, 0});
                }
            }
    }else {
        for(auto& course:findCourse(courseName).preCourses){
            if(!isPassed(studentID,course)){
                cout<< course <<'\t';
            }
        }
        throw invalid_argument("\nFor taking this course you most pass the above course(s) that you didn't.");
    }
}
void Controller::dropCourse(const std::string &studentID, const std::string &courseName) {
    if(!inStudents(studentID)){
        throw invalid_argument("The student was not found!");
    }else {
        if (inStuCourses(studentID, courseName)) {
            findStudent(studentID).currentSemesterCourses.erase(courseName);
        } else {
            throw invalid_argument("The course in not in student current semester courses list!!");
        }
    }
}
bool Controller::inStuCourses(const std::string &studentId,const std::string &courseName) {
    if(inCourses(courseName)) {
        auto iter = findStudent(studentId).currentSemesterCourses.begin();
        while(iter != findStudent(studentId).currentSemesterCourses.end()){
            string name=iter->first;
            if(name == courseName){
                return true;
            }
            iter++;
        }
    }
    return false;
}


void Controller::submitGrade(const std::string& courseName,const std::string& studentId, double grade){
    if(inStuCourses(studentId,courseName)){
        findStudent(studentId).currentSemesterCourses.find(courseName)->second=grade;
    }else{
        throw invalid_argument("the student doesn't have this course!");
    }
}
void Controller::readMembersFromFile(int membersNumber) {
    string member;
    char* cmd=new char[1000];
    ifstream input("members.txt");
    for (size_t i{1}; i <= membersNumber ; ++i) {
        try {
            input.getline(cmd,1000);
            member = (string) cmd;

            // Used to split string around spaces.
            istringstream ss(member);
            vector<string> results{};
            // Traverse through all word
            do {
                // Read a word
                string word;
                ss >> word;
                results.push_back(word);
                // While there is more to read
            } while (ss);


            if (results[0] == "P") {    //professor
                double wh;
                stringstream ss;
                ss << results[5];  //convert string to double
                ss >> wh;
                auto prof=new Professor (results[1], results[2], results[3], wh, results[4]);
                mathClass.push_back(prof);
            } else if (results[0] == "S") {   //student
                double wh;
                stringstream ss;
                ss << results[4];
                ss >> wh;
                auto stu=new Student (results[1], results[2], results[3], wh, vector<string>{}, map<string, double>{});
                mathClass.push_back(stu);
            } else if (results[0] == "D") {    //double major student
                double wh;
                stringstream ss;
                ss << results[4];
                ss >> wh;
                auto dStu=new DoubleMajorStudent( results[1], results[2], results[3], wh,
                                        vector<string>{}, map<string, double>{}, "DataScience");

                mathClass.push_back(dStu);
            }
        }catch(const invalid_argument& e){
            cout<< e.what() <<endl;
        }
    }
}
 double Controller:: CalculateTotalSalaryMath(){
    double totalSalary=0;
    for(const auto& person: mathClass){
        totalSalary+=person->calculateSalary(); //polymorphism
    }
    return totalSalary;
}
bool Controller::isPassed(std::string id,std::string courseName){
    for (auto& course:findStudent(id).passedCourses) {
        if(courseName == course){
            return true;
        }
    }
    return false;
}
