#include "particle.h"

#include <iostream>
#include <cmath>

Particle::Particle(double inpX, double inpY, double inpVx,
                   double inpVy, double inpRadius, double inpMass) :
    x(inpX), y(inpY), vx(inpVx), vy(inpVy), radius(inpRadius), mass(inpMass), collisions(0)
{

}


void Particle::move(double dt) {
    x += vx * dt;
    y += vy * dt;
}

int Particle::getCollisions() const {
    return collisions;
}

double Particle::getX() const {
    return x;
}
double Particle::getY() const {
    return y;
}
double Particle::getVx() const {
    return vx;
}
double Particle::getVy() const {
    return vy;
}
double Particle::getRadius() const {
    return radius;
}
double Particle::getMass() const {
    return mass;
}

double Particle::timeToHitVerticalWall() const {
    if      (vx > 0) return (1.0 - x - radius) / vx;
    else if (vx < 0) return (radius - x) / vx;
    else             return -1;

}
double Particle::timeToHitHorizontalWall() const {
     if      (vy > 0) return (1.0 - y - radius) / vy;
     else if (vy < 0) return (radius - y) / vy;
     else             return -1;
 }



double Particle::timeToHit(const Particle* that) const {
    if (this == that) {
//        std::cout << "Particle::Equal" << std::endl;
        return -1;
    }

    double dx  = that->x - x;
    double dy  = that->y - y;
    double dvx = that->vx - vx;
    double dvy = that->vy - vy;
    double dvdr = dx*dvx + dy*dvy;
    if (dvdr > 0) return -1;
    double dvdv = dvx*dvx + dvy*dvy;
    if(dvdv == 0) return -1;
    double drdr = dx*dx + dy*dy;
    double sigma = radius + that->radius;
    double d = (dvdr*dvdr) - dvdv * (drdr - sigma*sigma);
    // if (drdr < sigma*sigma) StdOut.println("overlapping particles");
    if (d < 0) return -1;
//    std::cout << "ret: " << -(dvdr + std::sqrt(d)) / dvdv << std::endl;
    return -(dvdr + std::sqrt(d)) / dvdv;
}

void Particle::bounceOff(Particle* that) {
      double dx  = that->x - x;
      double dy  = that->y - y;
      double dvx = that->vx - vx;
      double dvy = that->vy - vy;
      double dvdr = dx*dvx + dy*dvy;             // dv dot dr
      double dist = radius + that->radius;   // distance between particle centers at collison

      // magnitude of normal force
      double magnitude = 2 * mass * that->mass * dvdr / ((mass + that->mass) * dist);

      // normal force, and in x and y directions
      double fx = magnitude * dx / dist;
      double fy = magnitude * dy / dist;

      // update velocities according to normal force
      vx += fx / mass;
      vy += fy / mass;
      that->vx -= fx / that->mass;
      that->vy -= fy / that->mass;

      // update collision counts
      ++collisions;
      ++that->collisions;
  }



void Particle::bounceOffVerticalWall() {
     vx = -vx;
     ++collisions;
 }


 void Particle::bounceOffHorizontalWall() {
     vy = -vy;
     ++collisions;
 }
