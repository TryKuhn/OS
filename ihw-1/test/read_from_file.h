/**
 * @file
 * Reader from file
 */

#ifndef READ_FROM_FILE
#define READ_FROM_FILE

#include <map>
#include <string>

/**
 * Functions needed to save information to file
 */
class reader {

public:
    /**
     * Reads map from file
     * @param name name of the prefix
     * @param test current test number
     * @return map contains of pairs<char, int>, where char is symbol, int is count of its occurrences
     */
    static std::map<char, int> read_from_file(const std::string& name, int test) {
        FILE *file;
        std::map<char, int> pAns;

        file = fopen(("tests/" + name + std::to_string(test) + ".txt").c_str(), "r");

        if (file == nullptr) {
            perror("Can't open output file");
            exit(2);
        } else {
            char c;
            int cnt;
            while (fscanf(file, "%c %i\n", &c, &cnt) > 0) {
                pAns[c] = cnt;
            }
        }

        fclose(file);

        return pAns;
    }
};

#endif
