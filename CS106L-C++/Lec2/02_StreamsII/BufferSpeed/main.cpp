#include <iostream>
#include <chrono>

using std::cout;    using std::endl;
using std::ostream; using std::string;
using std::cerr;


/*
 * A helpful function that halts the program until
 * the user presses enter.
 */
void waitForEnter(const string& msg) {
    cout << msg;
    string l;
    std::getline(std::cin, l);
    cout << endl;
}

/*
 * The chrono library defines the types its different functions
 * return. It can be very verbose to always write the fully qualified
 * name so we can create aliases for them.
 *
 * In our program, we can use our aliases instead of the complete long
 * names.
 */

/*
 * We declate duration_t to be an alias/synonym for the
 * std::chrono::milliseconds::rep type.
 */
using duration_type = std::chrono::milliseconds::rep;

/*
 * We declate time_t to be an alias/synonym for the
 * std::chrono::high_resolution_clock::time_point type.
 */
using time_type = std::chrono::high_resolution_clock::time_point;

/*
 * This method returns the time (in ms) taken to run the
 * for loop in the function. The for loop just outputs
 * the backspace character some large number of times
 */
duration_type timeBufferSpeed(ostream& os) {
    /*
     * t1 is a variable of type time_t (which is an alias we
     * defined above). It represents the current clocks time.
     */
    time_type t1 = std::chrono::high_resolution_clock::now();

    /*
     * Runs slow for loop, outputting a backspace character
     * to the stream os some large number of times.
     */
    for(int i = 0; i < 10000000; ++i) {
        os << "\b";
    }
    os << endl;

    /*
     * t2 is a variable of type time_t (which is an alias we
     * defined above). It representst the current clocks time,
     * after the for loop has run.
     */
    time_type t2 = std::chrono::high_resolution_clock::now();

    /*
     * We return the difference of the two times, but cast the
     * different to milliseconds first.
     */
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
}


int main() {
    /*
     * Gives you time to adjust before running the tests :)
     */
    waitForEnter("Enter: ");
    cout << "Running tests..." << endl;

    /*
     * cout_time and cerr_time are variables of type duration_t
     * (which is an alias we defined above) that represent the
     * time taken (in ms) for the two streams to complete the
     * timeBufferSpeed function.
     */
    duration_type cout_time = timeBufferSpeed(cout);
    duration_type cerr_time = timeBufferSpeed(cerr);

    /*
     * Print the results! Since cout is buffered but cerr isn't
     * it is reaonable to expect that cout_time will be smaller
     * than cerr_time.
     *
     * This is implementation specific so your results may vary.
     */
    std::cout << "cout took: "
              << cout_time
              << " milliseconds" << endl;
    std::cout << "cerr took: "
              << cerr_time
              << " milliseconds" << endl;

    return 0;
}
