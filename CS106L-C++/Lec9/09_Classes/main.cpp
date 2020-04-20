#include <iostream>
#include "student.h"
#include "studentdatabase.h"

using std::string;
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

    if(db.hasStudent(s)) {
        cout << "Database has student!" << endl;
    }

    return 0;
}
