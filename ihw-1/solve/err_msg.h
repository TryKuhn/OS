/**
 * @file
 * Handling error messages
 */

#ifndef OS_ERR_MSG_H
#define OS_ERR_MSG_H

#include <cstdio>
#include <cstdlib>
#include <mqueue.h>

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

    static inline void end_of_communication(mqd_t q) {
        if (q >= 0) {
            const char msg[] = {(char)3};
            mq_send(q, msg, sizeof msg, 0);
        }
    }
};

#endif //OS_ERR_MSG_H
