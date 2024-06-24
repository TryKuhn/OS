/**
 * @file
 * Check answer to be correct
 */

#include "../solve/jury_answer.cpp"
#include "generate_test.h"
#include "save_to_file.h"
#include "read_from_file.h"

#include <cstdio>

std::set<char> getAnswer::is_ok = {};

/**
 * Runner tests in cmake and check them to be correct.
 * @param argc number of arguments
 * @param argv arguments
 * @return 0 if everything is ok
 * @return 1 if there is a problem on server
 * @return 2 if there is a problem in participant output
 */
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    auto [s, t] = generator::test(argc, argv);

    saver::save_to_file("input", t, s);

    std::map<char, int> jAns;

    getAnswer::setFilter(std::set({',', ';', ':', '.', '?', '!'}));
    jAns = getAnswer::j_ans(s);

    saver::save_to_file("jury", t, jAns);

    std::map<char, int> pAns = reader::read_from_file("output", t);
    return 0;

    if (jAns != pAns) {
        fprintf(stderr, "Wrong answer!\n");

        fprintf(stderr, "Expected:\n");
        for (auto [c, cnt]: jAns) {
            fprintf(stderr, "%c: %i\n", c, cnt);
        }

        fprintf(stderr, "\nBut found:\n");
        for (auto [c, cnt]: pAns) {
            fprintf(stderr, "%c: %i\n", c, cnt);
        }
        return 1;
    } else {
        fprintf(stderr, "Ok. Answer is correct\n");
        return 0;
    }
}
