
#include "event.h"

Event::Event(double t, Particle *inpA, Particle *inpB) :
    time(t), a(inpA), b(inpB)
{
    if(a != nullptr) countA = a->getCollisions();
    if(b != nullptr) countB = b->getCollisions();
}


double Event::getEventTime() const {
    return time;
}

Particle* Event::getFirstParticle() const {
   return a;
}

Particle* Event::getSecondParticle() const {
   return b;
}

bool Event::isValid() const {
    return (a == nullptr || a->getCollisions() == countA) &&
            (b == nullptr || b->getCollisions() == countB);

}


std::ostream& operator<<(std::ostream& os, const Event& e) {
    os << "Time: " << e.getEventTime() << "\t Particles:  " << e.getFirstParticle() << " - " << e.getSecondParticle() << "\t" << e.isValid();
    return os;
}
