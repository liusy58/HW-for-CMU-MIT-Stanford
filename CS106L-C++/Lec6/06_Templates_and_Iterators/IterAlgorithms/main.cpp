
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <algorithm>

using std::cout;    using std::endl;
using std::cin;     using std::string;
using std::vector;


/*
 * This is our original version of the function that count
 * the number of occurences of elemToCount in the vector.
 */
int numOccurences(vector<int>& cont, int elemToCount) {
    int counter = 0;
    vector<int>::iterator iter;
    for(iter = cont.begin(); iter != cont.end(); ++iter) {
        if(*iter == elemToCount)
            ++counter;
    }
    return counter;
}



/*
 * This is a modified version of our original function that
 * takes iterators specifying a range as opposed to the
 * entire vector container. This gives us more fine grain
 * control over the algorithm does.
 */
int numOccurences(vector<int>::iterator start, vector<int>::iterator end, int elemToCount) {
    int counter = 0;
    vector<int>::iterator iter;
    for(iter = start; iter != end; ++iter) {
        if(*iter == elemToCount)
            ++counter;
    }
    return counter;
}

/*
 * This is a templating version of the above function that will
 * work on any iterators provided by a container as long as we
 * can advance the iterator and dereference it.
 */
template <typename InputIterator, typename DataType>
int numOccurencesGen(InputIterator start, InputIterator end, DataType elemToCount) {

    int counter = 0;
    InputIterator iter;
    for(iter = start; iter != end; ++iter) {
        if(*iter == elemToCount)
            ++counter;
    }
    return counter;


// ========================

/* Alternative version */
//    int counter = 0;
//    while(start != end) {
//        if(*start == elemToCount) {
//            ++counter;
//        }
//        ++start;
//    }
//    return counter;

// ========================

/* Second alternative version */
//    int counter = 0;
//    for(; start != end; ++start) {
//        if(*start == elemToCount)
//            ++counter;
//    }
//    return counter;

}



int main() {

    std::vector<int> v {3, 1, 4, 1, 5, 9, 3};
    std::list<int> l {2, 7 , 1, 8, 2, 8 , 2};

    /* The C++ standard algorithm library defines a count function
     * that does exactly what our generic numOccurencesGen() function
     * does.
     */
    cout << "vec count : "      << numOccurencesGen(v.begin() , v.end(), 1) << endl;
    cout << "lib vec count: "   << std::count(v.begin(), v.end(), 1)        << endl;

    /*
     * Our code works for any container that provides iterators!.
     */
    cout << "list count : "     << numOccurencesGen(l.begin() , l.end(), 1) << endl;
    cout << "lib list count: "  << std::count(l.begin(), l.end(), 1)        << endl;




}
