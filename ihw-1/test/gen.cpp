//
// Created by User on 6/19/2024.
//

#include "../testlib.h"
#include "jury_answer.cpp"
//#include "../four/main.cpp"

#include <string>
#include <vector>
#include <cstdio>
#include <cassert>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int test = opt<int>("test");
    int N = opt<int>("N");
    int alpha = opt<int>("Alpha");


    char *s = new char[N];

    for (int i = 0; i < N; ++i) {
        int cur = rnd.next(alpha);
        if (alpha == 2) {
            int type = rnd.next(4);
            if (type < 3) {
                s[i] = static_cast<char>(cur + '0');
            } else {
                s[i] = rnd.any(std::vector<char>({',', ';', ':', '.', '?', '!'}));
            }
        } else if (alpha == 26) {
            int type = rnd.next(4);
            if (type < 3) {
                s[i] = static_cast<char>(cur + 'a');
            } else {
                s[i] = rnd.any(std::vector<char>({',', ';', ':', '.', '?', '!'}));
            }
        } else {
            int type = rnd.next(4);
            if (type == 0) {
                cur = rnd.next(26);
                s[i] = static_cast<char>(cur + 'a');
            } else if (type == 1) {
                cur = rnd.next(26);
                s[i] = static_cast<char>(cur + 'A');
            } else if (type == 2) {
                cur = rnd.next(10);
                s[i] = static_cast<char>(cur + '0');
            } else {
                s[i] = rnd.any(std::vector<char>({',', ';', ':', '.', '?', '!'}));
            }
        }
    }

    if (mkdir("tests") == -1 && errno != EEXIST) {
        perror("Tests is not created");
        return 1;
    }

    FILE *fgen;

    fgen = fopen(("tests/input" + std::to_string(test) + ".txt").c_str(), "w");

    if (fgen == nullptr) {
        perror("Can't open input file");
        return 1;
    } else {
        for (int i = 0; i < N; ++i) {
            fprintf(fgen, "%c", s[i]);
        }
        fprintf(fgen, "\n");
    }

    fclose(fgen);

    FILE *fans;
    std::map<char, int> jAns;

    fans = fopen(("tests/jury_output" + std::to_string(test) + ".txt").c_str(), "w");

    if (fans == nullptr) {
        perror("Can't open answer file");
        return 1;
    } else {
        getAnswer::setFilter(std::set({',', ';', ':', '.', '?', '!'}));
        jAns = getAnswer::j_ans(s);

        for (auto [c, cnt]: jAns) {
            fprintf(fans, "%c %i\n", c, cnt);
        }
    }

    fclose(fans);

    FILE *fout;
    std::map<char, int> pAns;

    fout = fopen(("tests/output" + std::to_string(test) + ".txt").c_str(), "r");

    if (fout == nullptr) {
        perror("Can't open output file");
        return 1;
    } else {
        char c;
        int cnt;
        while (fscanf(fout, "%c %i\n", &c, &cnt) > 0) {
            pAns[c] = cnt;
        }
    }

    fclose(fout);

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
    }

    assert(pAns == jAns);
}
