
#include "DoubleMajorStudent.h"
using namespace std;
DoubleMajorStudent::DoubleMajorStudent(const string &studentId, string first, string last,
                                       double workHours, vector<string> passedCourses,
                                       std::map<string, double> currentSemesterCourses, string major2)
                                       :Student(move(studentId),move(first),move(last),move(workHours),move(passedCourses),
                                               move(currentSemesterCourses)),
                                       major2{move(major2)}{}

std::ostream &operator<<(std::ostream &output, const DoubleMajorStudent &student) {
    Student stu=student;
    output << stu <<student.major2 <<'\t';
    return output;
}

std::istream &operator>>(std::istream &input, DoubleMajorStudent &student) {
    Student stu;
    input >> stu;
    string major2;
    input >> major2;
    DoubleMajorStudent stu2(stu.getStudentId(),stu.getFirstName(),stu.getLastName(),
            stu.getWorkHours(),stu.getPassedCourses(),stu.getCurrentSemesterCourses(),major2);
    student=stu2;
    return input;
}

double DoubleMajorStudent::calculateSalary() const {
    return (6500 * getWorkHours());
}

