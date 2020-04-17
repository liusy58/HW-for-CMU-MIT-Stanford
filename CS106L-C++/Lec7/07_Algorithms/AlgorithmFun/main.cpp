#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <cstdlib>

using namespace std;

const string kNumbersFile = "nums.txt";

// Just a simple little helper method to print out the elements of a vector
void printVector(vector<int>& nums) {
    cout << "{";
    for (auto elem : nums) {
        cout << elem << ", ";
    }
    cout << "}" << endl;
}


void vectorFun(vector<int> nums) {
   /*
    * The average of a collection of numbers can be found by:
    *   1. Computing the sum of the elements in the collection
    *   2. Dividing that sum by the number of elements in the collection
    *
    * The division step is easy, but the summing is interesting because we can
    * do all of the work using only STL algorithms and iterators.
    *
    * The accumulate function takes an iterator to start at and an iterator to
    * stop at, as well as an initial value.  The function will then add up all
    * of the values in the range specified by the first two arguments using the
    * third argument as a starting value.
    */

    double total = std::accumulate(nums.begin(), nums.end(), 0.0);
    double average = total / nums.size();
    cout << "Average: " << average << endl;

  /*
   * Some might complain that finding the average of a collection of numbers
   * isn't that difficult to write without using <algorihtm>.  Fair enough,
   * let's look at a more complicated example.
   *
   * A simple yet inefficient algorithm for finding the median element in a
   * collection is to:
   *   1. Sort the collection
   *   2. Find the median element by finding the value which is halfway between
   *   the beginning and the end.
   *
   * We could do that using the STL, but the STL gives us an even better option.
   * The nth_element function will sort the array *a little bit*.  That means that
   *   * The nth element (where n is a parameter) will be in the same position
   *     it would be in if the array was sorted.
   *   * All elements to the left of the nth element will be less than it, and
   *     all elements to the right or it will be greater than it.
   *
   * The first property guarantees that if we call nth_element with n being
   * halfway between begin and end we can recover the median by simply reading
   * that element.
   */
    std::nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
    int median = nums[nums.size() / 2];
    cout << "Median: " << median << endl;

  /*
   * Sorting a collection is another classic example of a relatively
   * complicated algorithm.  Thankfully we have a sorting algorithm in the
   * standard library, which is both fast and simple to use.
   *
   * Notice that the algorithm only needs to know where the elements start and
   * where they stop -- everything else it can figure out on its own.  We'll
   * talk more about how that magic works when we talk about templates.
   */
    std::sort(nums.begin(), nums.end());
    printVector(nums);

  /*
   * Reversing the range is also nice and simple -- just say where to start and
   * where to stop and the STL does the rest of the work.
   */
    std::reverse(nums.begin(), nums.end());
    printVector(nums);

  /*
   * The coolest thing about this code is that you can do a find and replace
   * switching the word 'vector' with the word 'deque' and the code will still
   * work.  This is the magic of iterators.  Nothing we wrote here depends on
   * the fact that we used a vector because everything we did was done in terms
   * of algorithms.  When we talk about templates we'll talk about how you can
   * write a single function template which will work with vectors, deques, and
   * any other container which has the properties you need.
   */
}

vector<int> createRandomVec(size_t sz) {
    srand(time(NULL));
    vector<int> nums;
    for (int i = 0; i < 20 ; i++) {
        nums.push_back(rand() % 500);
    }
    return nums;
}

int main() {
    /*
     * The following four lines will initialize our vector with 20 random numbers
     * between 0 and 500, inclusive.  If you're curious how they work, take a
     * look at the rand and srand functions in <cstdlib>, but otherwise you don't
     * need to understand them.
     */

    vector<int> nums = createRandomVec(20);

    vectorFun(nums);
    return 0;
}
