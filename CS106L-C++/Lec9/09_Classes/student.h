#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student(std::string inpName, std::string inpSuid, int inpUnits);
    std::string getName();
    std::string getSuid();
    int getUnits();
    std::string classLevel();

private:
    std::string name;
    std::string suid;
    int numUnits;
};

bool operator==(Student left, Student right);

#endif // STUDENT_H
