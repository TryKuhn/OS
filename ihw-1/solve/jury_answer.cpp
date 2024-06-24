/**
 * @file
 * Generating jury answer
 */

#include <string>
#include <map>
#include <set>

/**
 * Functions needed to generate jury output
 */
class getAnswer {

public:
    /**
     * Symbols to be checked
     */
    static std::set<char> is_ok;

    getAnswer() = default;

    /**
     * Update symbols to be checked
     * @tparam T convertable types to std::set<char>
     * @param upd new symbols
     */
    template<typename T>
    static void setFilter(T upd) {
        is_ok = upd;
    }

    /**
     * Computer of jury answer
     * @param s input string
     * @return answer to the test
     */
    static std::map<char, int> j_ans(const std::string &s) {
        std::map<char, int> answer;

        for (const char c: s) {
            if (is_ok.find(c) != is_ok.end()) {
                ++answer[c];
            }
        }

        return answer;
    }
};
