#ifndef TA_19_CONTROLLER_H
#define TA_19_CONTROLLER_H

#include <string>
#include <vector>
#include "../Model/Student.h"
#include "../Model/Professor.h"
#include "../Model/Course.h"

class Controller {
    friend class Menu;
    friend class CommandsFromFileMenu;
    friend class LeafMenu;
private:
    std::string currentSemester;
    std::vector<Student> students;
    std::vector<Professor> professors;
    std::vector<Course> courses;
    std::vector<Course> currentSemesterCourses;
    std::vector<Person*> mathClass;
    Controller() = default;

public:
    explicit Controller(std::string currentSemester);
    void load();
    void save() const;

    void addStudent(std::string ID, std::string first, std::string last);
    void addProfessor(std::string ID, std::string first, std::string last, std::string title);
    void addCourse(std::string courseName, std::string profLast, std::string semester,
            std::vector<std::string> pre);
    void takeCourse(const std::string& studentID, const std::string& courseName);
    void dropCourse(const std::string& studentID, const std::string& courseName);
    Student& findStudent(std::string ID);
    Professor& findProf(std::string ID);
    Course& findCourse(std::string courseName);
    bool inStudents(const std::string& ID) const;
    bool inProfessors(const std::string& ID) const;
    bool inProfessorsByLastName(const std::string& last) const;
    bool inCourses(const std::string& courseName) const;
    bool inStuCourses(const std::string& studentId,const std::string& courseName);
    void submitGrade(const std::string& courseName,const std::string& studentId, double grade);
    void readMembersFromFile(int membersNumber);
    virtual double CalculateTotalSalaryMath();
    bool isPassed(std::string id,std::string courseName);
};


#endif //TA_19_CONTROLLER_H
