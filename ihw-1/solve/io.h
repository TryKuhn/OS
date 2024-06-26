/**
 * @file
 * Handles input/output in participant solve
 */

#ifndef OS_IO_H
#define OS_IO_H

#include "err_msg.h"

#include <mqueue.h>

const size_t TBUFFER_SIZE = 128 * sizeof(char);

/**
 * Contains handlers for input and output
 */
class handler {
public:
    /**
     * Reader part of input
     * @param reader reader queue
     * @param buff buffer where to read
     * @return length of string
     */
    static ssize_t read_part(mqd_t reader, char* buff) {
        ssize_t bytes_read =
                mq_receive(reader, buff, TBUFFER_SIZE - 1, nullptr);

        if (bytes_read < 0) {
            printer::print_error("Can't read from queue");
            return 0;
        }

        if (bytes_read == 0) {
            return 0;
        }

        if (buff[bytes_read - 1] == (char)3) {
            bytes_read = 0;
        }

        return bytes_read;
    }

    /**
     * Writer part of output
     * @param writer writer queue
     * @param buff buffer from where to write
     */
    static void write_part(mqd_t writer, char* buff, size_t len) {
        if (mq_send(writer, buff, len, 0) < 0) {
            printer::print_error("Can't send data to another process using queue");
            return;
        }
    }
};

#endif //OS_IO_H
