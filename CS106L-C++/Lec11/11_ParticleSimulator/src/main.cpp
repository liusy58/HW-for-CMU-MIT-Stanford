
/*
 * Program idea taken from Algorithms by Robert Sedgewick and Kevin Wayne.
 */

#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>
#include <fstream>
#include "canvas.h"
#include "event.h"
#include "particle.h"
#include <queue>
#include <chrono>

using std::cout;	using std::endl;
using std::cin;     using std::string;
using std::vector;  using std::ifstream;


const double kTimeIncrement = 1.0;

// Function prototypes
void openFile(ifstream& input);
void initParticles(ifstream& input, vector<Particle>& particles);
void pause(double ms);

template <typename PQueue>
void predict(Particle* currP, double t, vector<Particle>& particles, PQueue& pq);

template <typename DataType>
DataType getInput(const string& msg);


/*
 * Throughout this program we use pointers to the Particles in
 * the canv.points vector. This is because we want the Events
 * to refer to and modify the same particles that are being drawn
 * on the canvas. To do this we store pointers to the Particles
 * in the canvas.points vector.
 */
int main() {
    Canvas canv;
    InitCanvas(canv);
    vector<Particle> &particles = canv.points;
    ifstream input;
    openFile(input);
    initParticles(input, particles);

    DrawCanvas(canv);

    double t = 0;

    /*
     * Create the comparison function for the priority_queue to
     * determine which element has "higher" priority. This function
     * shoudl return true if the second argument (b) should have a
     * higher priority than the first argument (a).
     *
     * In our case, b has a higher priority than a if b occurs earlier
     * than a.
     */
    auto cmpFn = [](const Event& a, const Event& b) -> bool {
        return b.getEventTime() < a.getEventTime();
    };

    std::priority_queue<Event, vector<Event>, decltype(cmpFn)> pq(cmpFn);

    /* Make initial prediction of collisions and store them in queue. */
    for(auto &p : particles) {
        predict(&p, t, particles, pq);
    }

    /*
     * Start off with a dummy event that will just re-draw
     * the canvas.
     */
    pq.push(Event(0, nullptr, nullptr));


    while(!pq.empty()) {

        Event e = pq.top();
        pq.pop();

        /* Print the event so our terminal looks cool */
        cout << e << endl;

        /*
         * If the Event e was invalidated by a previous collision,
         * ignore it and continue to the next iteration of the while loop.
         */
        if(!e.isValid()) continue;
        Particle* firstP = e.getFirstParticle();
        Particle* secondP = e.getSecondParticle();

        /*
         * Advance the movement of the particles from t to the event time.
         * This will always be a small increment
         */
        for(auto &p : particles) {
            p.move(e.getEventTime() - t);
        }


        t = e.getEventTime();

        if (firstP != nullptr && secondP != nullptr) {
            firstP->bounceOff(secondP);             // particle particle collision
        } else if (firstP != nullptr && secondP == nullptr) {
            firstP->bounceOffVerticalWall();        // particle wall collision
        } else if (firstP == nullptr && secondP != nullptr) {
            secondP->bounceOffHorizontalWall();     // particle wall collision
        } else {

            /*
             * Both firstP and secondP are null so this is a dummy event. This means
             * we aren't at a point in time where an actual collision has occured
             * so we need to keep running the animation until an actual collision
             * event is dequed from the pqueue.
             *
             * To do this, we can just add another dummy event a small time incremement from
             * now into the pqueue that will get drawn the next iteration of the loop.
             */

            DrawCanvas(canv);
            pause(10);
            pq.push(Event(t + kTimeIncrement, nullptr, nullptr));
        }

        /*
         * This will make the new collision predictions involving the first
         * and second particles and add them to the queue.
         *
         * If the particle is a nullptr, nothing will happen. This is where the
         * efficiency gains are made! The O(n^2) predictions will only be made
         * during events that are actually collision. For the rest of the dummy events,
         * these functions will just instantly return and so avoid the slow check.
         */
        predict(firstP, t, particles, pq);
        predict(secondP, t, particles, pq);

    }
    return 0;
}


/*
 * Pause funciton to pause tha animation for a few milliseconds
 * so that it doesn't go by too fast.
 */
void pause(double ms) {
    auto start= std::chrono::high_resolution_clock::now();
    while(true) {
       auto end = std::chrono::high_resolution_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
       if(duration > ms) return;
    }
}


/*
 * We need to templatise this function because we don't know the
 * type of the priotiy_queue. This is because part of it's type
 * is the type of the comparator lambda function and if you recall,
 * we had to use the decltype.
 *
 * Since we can't really write the type of the priority_queue type,
 * we just let the templates deal with it.
 */
template <typename PQueue>
void predict(Particle* currP, double t, vector<Particle>& particles, PQueue& pq) {

    /* If the particle is not actually a particle, there is no need to make predictions. */
    if(currP == nullptr) return;

    for(auto &otherP : particles) {
        double dt = currP->timeToHit(&otherP);
        if(dt != -1) {      // -1 retured if collision will never happen
            pq.push(Event(t + dt, currP, &otherP));
        }
    }

    double dtX = currP->timeToHitVerticalWall();
    double dtY = currP->timeToHitHorizontalWall();

    if(dtX != -1) {         // -1 retured if collision will never happen
        pq.push(Event(t + dtX, currP, nullptr));
    }
    if(dtY != -1) {         // -1 retured if collision will never happen
        pq.push(Event(t + dtY, nullptr, currP));
    }

}


/*
 * Gets valid filename from user and opens it using an ifstream
 * that is passed by reference.
 */
void openFile(ifstream& input) {
    while(true) {
        cout << "Enter filename of graph: ";
        string filename;
        std::getline(cin, filename);
        input.open(filename.c_str());
        if(input) return;
        cout << "Cannot find the specified file." << endl;
    }
}


/*
 * Creates the graph specified in the input file and returns
 * the graph. Uses the extraction operator to initially get the
 * number of nodes and then to get each edge.
 */
void initParticles(ifstream& input, vector<Particle>& particles) {
    size_t numPoints;
    input >> numPoints;
    double x, y, vx, vy, radius, mass;
    // dummy variable because our data has extra color information for each particle
    // that we won't use
    int dummy;
    while(input >> x >> y >> vx >> vy >> radius >> mass >> dummy >> dummy >> dummy) {
        particles.push_back(Particle(x, y, vx, vy, radius, mass));
    }

}




int getSeconds() {
    return getInput<size_t>("Enter the number of seconds to run: ");
}


/*
 * Templatised function that will get any stream convertible
 * input. Reprompts until valid input of type DataType is entered.
 */
template <typename DataType>
DataType getInput(const string& msg) {
    while(true) {
        cout << msg << std::flush;
        string line;
        std::getline(cin, line);
        std::istringstream converter(line);
        DataType result;
        if(converter >> result) {
            char remaining;
            if(converter >> remaining) {
                cout << "Unexpected character. Try again." << endl;
            } else {
                return result;
            }
        } else {
            cout << "Not a valid input. Try again." << endl;
        }
    }
}

