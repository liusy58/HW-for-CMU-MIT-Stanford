#include "Utilities.h"
#include <cctype>
#include <stdexcept>
#include <sstream>

/* All code here, except for the code for error, stolen or adapted from strlib.cpp. */

namespace {
    void trimEndInPlace(std::string& str) {
        int end = (int) str.length();
        int finish = end;
        while (finish > 0 && isspace(str[finish - 1])) {
            finish--;
        }
        if (finish < end) {
            str.erase(finish, end - finish);
        }
    }

    std::string trimEnd(const std::string& str) {
        std::string str2 = str;
        trimEndInPlace(str2);
        return str2;
    }

    void trimStartInPlace(std::string& str) {
        int start = 0;
        int finish = (int) str.length() - 1;
        while (start <= finish && isspace(str[start])) {
            start++;
        }
        if (start > 0) {
            str.erase(0, start);
        }
    }

    std::string trimStart(const std::string& str) {
        std::string str2 = str;
        trimStartInPlace(str2);
        return str2;
    }

    void trimInPlace(std::string& str) {
        trimEndInPlace(str);
        trimStartInPlace(str);
    }
}

namespace Utilities {
    bool startsWith(const std::string& str, char prefix) {
        return str.length() > 0 && str[0] == prefix;
    }

    bool startsWith(const std::string& str, const std::string& prefix) {
        if (str.length() < prefix.length()) return false;
        int nChars = prefix.length();
        for (int i = 0; i < nChars; i++) {
            if (str[i] != prefix[i]) return false;
        }
        return true;
    }

    std::string trim(const std::string& str) {
        std::string str2 = str;
        trimInPlace(str2);
        return str2;
    }

    std::vector<std::string> stringSplit(const std::string& str, char delimiter) {
        std::string str2 = str;
        std::vector<std::string> result;

        size_t index = 0;
        while (true) {
            index = str2.find(delimiter);
            if (index == std::string::npos) {
                break;
            }
            result.push_back(str2.substr(0, index));
            str2.erase(str2.begin(), str2.begin() + index + 1);
        }
        if (!str2.empty()) {
            result.push_back(str2);
        }

        return result;
    }

    void error(const std::string& message) {
        throw std::runtime_error(message);
    }

    int stringToInt(const std::string& str) {
        std::istringstream converter(str);

        int result;
        char leftover;
        if (!(converter >> result) || converter >> leftover) {
            Utilities::error("Could not interpret " + str + " as an integer.");
        }

        return result;
    }
}
