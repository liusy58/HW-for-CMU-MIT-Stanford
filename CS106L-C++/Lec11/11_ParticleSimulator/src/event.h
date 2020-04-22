#ifndef EVENT_H
#define EVENT_H

#include "particle.h"
#include <iostream>

class Event {
public:
    Event(double t,  Particle* a, Particle* b);

    double getEventTime() const;

    Particle* getFirstParticle() const;
    Particle* getSecondParticle() const;

    bool isValid() const;


private:
    double time;
    Particle* a;
    Particle* b;
    int countA;
    int countB;
};

std::ostream& operator<<(std::ostream& os, const Event& e);

#endif // EVENT_H
