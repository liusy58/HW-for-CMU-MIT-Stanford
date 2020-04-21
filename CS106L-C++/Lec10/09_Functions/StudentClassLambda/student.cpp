#include "student.h"

using std::string;


Student::Student(std::string inpName,
                 std::string inpSuid, int inpUnits) {
    name = inpName;
    suid = inpSuid;
    numUnits = inpUnits;
}

std::string Student::getName() {
    return name;
}

std::string Student::getSuid() {
    return suid;
}

int Student::getUnits() {
    return numUnits;
}

std::string Student::classLevel() {
    if(numUnits <= 45) {
        return "freshman";
    } else if(numUnits <= 90) {
        return "sophomore";
    } else if(numUnits <= 135) {
        return "junior";
    } else {
        return "senior";
    }
}

bool operator==(Student left, Student right) {
    return left.getSuid() == right.getSuid();
}

