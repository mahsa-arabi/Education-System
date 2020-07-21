#ifndef TA_19_STUDENT_H
#define TA_19_STUDENT_H

#include "Person.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Student : public Person {
    friend class Controller;
    friend class LeafMenu;
    friend std::ostream& operator<<(std::ostream & output, const Student& student);
    friend std::istream& operator>>(std::istream & input, Student& student);
private:
    std::string studentId;
    std::vector<std::string> passedCourses;
    std::map<std::string, double> currentSemesterCourses;

public:
    Student() : Person() {}   // must be private
    Student(const std::string& studentId, std::string first, std::string last , double workHours,
            std::vector<std::string> passedCourses, std::map<std::string, double> currentSemesterCourses);

    virtual double calculateSalary() const override;

    const std::string &getStudentId() const;

    std::string toString() const;

    const std::map<std::string, double> &getCurrentSemesterCourses() const;

    void setPassedCourses(const std::vector<std::string> &passedCourses);

    void setCurrentSemesterCourses(const std::map<std::string, double> &currentSemesterCourses);

    const std::vector<std::string> &getPassedCourses() const;

};


#endif //TA_19_STUDENT_H
