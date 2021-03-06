#ifndef TA_19_LEAFMENU_H
#define TA_19_LEAFMENU_H

#include <string>
#include "Menu.h"

class LeafMenu : public Menu{
public:
    LeafMenu(std::string name, Menu* parent);
    virtual void showSubMenus() const override;
    virtual void run() override;
    static void showAllCourses();
    static void showSemesterCourses();
    static void showStuSemesterCourses(std::string studentId);
    static void showProfSemesterCourses(std::string profId);
    static void showProfessors();
    static void showCurrentCourses();
};


#endif //TA_19_LEAFMENU_H
