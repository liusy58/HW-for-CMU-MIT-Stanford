#ifndef PARTICLE_H
#define PARTICLE_H

//#include "canvas.h"

class Particle
{
public:
    Particle(double x, double  y,double  vx, double  vy,
             double radius, double mass);

    void move(double dt);
    void bounceOffVerticalWall();
    void bounceOffHorizontalWall();
    void bounceOff(Particle* that);

    int getCollisions() const;
    double getX() const;
    double getY() const;
    double getVx() const;
    double getVy() const;
    double getRadius() const;
    double getMass() const;

    double timeToHitHorizontalWall() const;
    double timeToHitVerticalWall() const;
    double timeToHit(const Particle* that) const;



private:
    double x, y, vx, vy, radius, mass;
    int collisions;
};

#endif // PARTICLE_H
