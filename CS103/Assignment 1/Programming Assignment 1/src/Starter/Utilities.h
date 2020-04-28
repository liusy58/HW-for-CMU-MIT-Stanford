/* Utility functions previously exported by strlib.h and error.h that have been copied and
 * exported for the sake of the autograder.
 */
#ifndef Utilities_Included
#define Utilities_Included

#include <string>
#include <vector>

namespace Utilities {
    std::string trim(const std::string& input);
    bool startsWith(const std::string& str, const std::string& prefix);
    std::vector<std::string> stringSplit(const std::string& str, char delimiter);
    [[ noreturn ]] void error(const std::string& error);
}

#endif
