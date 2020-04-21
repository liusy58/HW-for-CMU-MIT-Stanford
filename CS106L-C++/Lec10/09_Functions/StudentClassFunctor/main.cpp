#include <iostream>
#include "student.h"
#include "studentdatabase.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;


int main() {

    Student s("Ali", "malikali", 136);
    Student s2("John", "jjadams", 25);
    Student s3("Adam", "adams", 40);



    StudentDatabase db;
    db.addStudent(s);
    db.addStudent(s2);
    db.addStudent(s3);


    vector<Student> firstYears = db.studentsInYear("freshman");
    for(Student s : firstYears) {
        cout << s.getName() <<endl;
    }


    return 0;
}
