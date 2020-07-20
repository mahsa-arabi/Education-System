
#include "DoubleMajorStudent.h"
using namespace std;
DoubleMajorStudent::DoubleMajorStudent(const string &studentId, string first, string last,
                                       double workHours, vector<string> passedCourses,
                                       std::map<string, double> currentSemesterCourses, string major2)
                                       :Student(move(studentId),move(first),move(last),move(workHours),move(passedCourses),
                                               move(currentSemesterCourses)),
                                       major2{move(major2)}{}
