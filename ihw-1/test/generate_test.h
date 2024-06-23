/**
 * @file
 * Participant answer
 */

#ifndef GENERATOR
#define GENERATOR

#include <sys/stat.h>

#include "save_to_file.h"
#include "../testlib.h"


class generator {
    /**
     * Function to generate random char
     * @param alpha type of symbols: 2 for 0-1, 26 for a-z, 128 for random
     * @return Generated char
     */
    static char generate_char(int alpha) {
        int cur = rnd.next(alpha);
        if (alpha == 2) {
            int type = rnd.next(4);
            if (type < 3) {
                return static_cast<char>(cur + '0');
            } else {
                return rnd.any(std::vector<char>({',', ';', ':', '.', '?', '!'}));
            }
        } else if (alpha == 26) {
            int type = rnd.next(4);
            if (type < 3) {
                return static_cast<char>(cur + 'a');
            } else {
                return rnd.any(std::vector<char>({',', ';', ':', '.', '?', '!'}));
            }
        } else {
            int type = rnd.next(4);
            if (type == 0) {
                cur = rnd.next(26);
                return static_cast<char>(cur + 'a');
            } else if (type == 1) {
                cur = rnd.next(26);
                return static_cast<char>(cur + 'A');
            } else if (type == 2) {
                cur = rnd.next(10);
                return static_cast<char>(cur + '0');
            } else {
                return rnd.any(std::vector<char>({',', ';', ':', '.', '?', '!'}));
            }
        }
    }

public:
    /**
     * Generation of string by given restrictions
     * @param argc num of params
     * @param argv params
     * @return Generated string
     */
    static std::pair<char *, int> test(int argc, char *argv[]) {
        registerGen(argc, argv, 1);

        int test = opt<int>("test");
        int N = opt<int>("N");
        int alpha = opt<int>("Alpha");


        char *s = new char[N];

        for (int i = 0; i < N; ++i) {
            s[i] = generate_char(alpha);
        }

        saver::save_to_file("input", test, s);

        return {s, test};
    }
};

#endif
