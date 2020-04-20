#include "studentdatabase.h"

using std::vector;


void StudentDatabase::addStudent(const Student& s) {
    db.push_back(s);
}

bool StudentDatabase::hasStudent(Student toFind) {
    for(auto student : db) {
        if(student == toFind)
            return true;
    }
    return false;
}


int StudentDatabase::size() {
    return db.size();
}


bool StudentDatabase::empty() {
    return db.empty();
}



std::vector<Student> StudentDatabase::studentsInYear(std::string yearToFind) {
    vector<Student> ret;

// Can't use pred function because we need to somehow give it yearToFind...
//    std::copy_if(db.begin(), db.end(),  std::back_inserter(ret), pred)

    // We'll settle for a for-loop
    for(auto student : db) {
        if(student.classLevel() == yearToFind) {
            ret.push_back(student);
        }
    }
    return ret;
}







