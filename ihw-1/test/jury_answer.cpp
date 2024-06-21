//
// Created by User on 6/21/2024.
//

#include <string>
#include <map>
#include <set>

class getAnswer {

public:
    static std::set<char> is_ok;
    getAnswer() = default;

    template<typename T>
    static void setFilter(T upd) {
        is_ok = upd;
    }

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

std::set<char> getAnswer::is_ok = {};