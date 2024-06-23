/**
 * @file
 * Saver info to files
 */
#ifndef SAVE_TO_FILE
#define SAVE_TO_FILE

#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

#include <string>
#include <map>

/**
 * Functions needed to save information to file
 */
class saver {

public:
    /**
     * Saver string to file
     * @param name name of the prefix
     * @param test current test number
     * @param info string to save
     */
    static void save_to_file(const std::string &name, int test, const std::string &info) {
        if (mkdir("tests", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 && errno != EEXIST) {
            perror("Tests is not created");
            exit(1);
        }

        FILE *file;

        file = fopen(("tests/" + name + std::to_string(test) + ".txt").c_str(), "w");

        if (file == nullptr) {
            perror("Can't open input file");
            exit(1);
        } else {
            for (char i: info) {
                fprintf(file, "%c", i);
            }
            fprintf(file, "\n");
        }

        fclose(file);
    }

    /**
     * Saver map<char, int> to file
     * @param name name of the prefix
     * @param test current test number
     * @param info map to save
     */
    static void save_to_file(const std::string &name, int test, const std::map<char, int> &info) {
        if (mkdir("tests", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 && errno != EEXIST) {
            perror("Tests is not created");
            exit(1);
        }

        FILE *file;

        file = fopen(("tests/" + name + std::to_string(test) + ".txt").c_str(), "w");

        if (file == nullptr) {
            perror("Can't open input file");
            exit(1);
        } else {
            for (auto [c, cnt]: info) {
                fprintf(file, "%c %i\n", c, cnt);
            }
            fprintf(file, "\n");
        }

        fclose(file);
    }
};

#endif
