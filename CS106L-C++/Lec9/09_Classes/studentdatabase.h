#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H


#include <vector>
#include "student.h"

class StudentDatabase
{
public:
    void addStudent(const Student& s);
    bool hasStudent(Student toFind);
    int size();
    bool empty();

    std::vector<Student> studentsInYear(std::string yearToFind);

private:
    std::vector<Student> db;
};

#endif // STUDENTDATABASE_H
