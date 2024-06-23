/**
 * @file
 * Handling error messages
 */

#ifndef OS_ERR_MSG_H
#define OS_ERR_MSG_H

#include <cstdio>
#include <cstdlib>

/**
 * Printers of the errors
 */
class printer {
public:
    /**
     * Printing error message and exits with status code 2
     * @param msg message to print
     */
    static inline void print_error(const char msg[]) {
        perror(msg);
        fprintf(stderr, "Error! %s\n", msg);
    }
};

#endif //OS_ERR_MSG_H
