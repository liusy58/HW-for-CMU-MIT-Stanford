#include "studentdatabase.h"
#include <iostream>
using std::vector;
using std::string;

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

class InYearPred {
public:
    InYearPred(const string& inp) {
        yearToFind = inp;
    }

    bool operator()(Student s) {
        return s.classLevel() == yearToFind;
    }

private:
    string yearToFind;

};



std::vector<Student> StudentDatabase::studentsInYear(std::string yearToFind) {
    vector<Student> ret;

    std::copy_if(db.begin(), db.end(), std::back_inserter(ret),
                                        [&yearToFind](Student s) -> bool {
                                                return s.classLevel() == yearToFind;
                                        });



// We'll settle for a for-loop
//    for(auto student : db) {
//        if(student.classLevel() == yearToFind) {
//            ret.push_back(student);
//        }
//    }
    return ret;
}







