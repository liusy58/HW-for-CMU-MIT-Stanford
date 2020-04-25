#include "ExecutableLogic.h"
#include <stdexcept>

bool isFormulaTrueFor_partI(std::set<Person> P) {
    for(auto person:P)
        if(happy(person))
            return true;
    return false;
}

bool isFormulaTrueFor_partII(std::set<Person> P) {
    for(auto person:P)
        if(!happy(person))
            return false;
    return true;
}

bool isFormulaTrueFor_partIII(std::set<Person> P) {
    for(auto person:P)
        if(happy(person)&&loves(person,person))
            return true;
    return false;
}

bool isFormulaTrueFor_partIV(std::set<Person> P) {
    for(auto person:P)
        if(happy(person))
            if(!loves(person,person))
                return false;
    return true;
}

bool isFormulaTrueFor_partV(std::set<Person> P) {
    for(auto person1:P)
    {
        if(happy(person1))
        {
            bool flag=0;
            for(auto person2:P)
            {
                if(happy(person2)&&!loves(person1,person2))
                {
                    flag=1;
                    break;
                }
            }
            if(!flag)
                return false;
        }
    }
    return true;
}

bool partVI_left(std::set<Person> P,Person x)
{
    if(happy(x))
    {
        for(auto person:P)
            if(!loves(x,person))
                return false;
    }
    return true;
}

bool partVI_right(std::set<Person> P,Person x)
{
    for(auto person:P)
    {
        if(!loves(x,person))
            return true;
    }
    return happy(x);

}
bool isFormulaTrueFor_partVI(std::set<Person> P) {
    for(auto person1:P)
    {
        if(partVI_left(P,person1)&&partVI_right(P,person1))
            return true;
    }
    return false;
}
