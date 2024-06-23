/**
 * @file
 * Calculation of the answer using processes
 */

#ifndef OS_PROCESS_WORK_H
#define OS_PROCESS_WORK_H

#include <cstring>
#include "io.h"

/**
 * Running process with queries
 */
class process {
    /**
     * Converts punctuation mark to index in array
     * @param c char to convert
     * @return if given aindex
     */
    static int convert(char c) {
        if (c == ',') {
            return 0;
        }
        if (c == ';') {
            return 1;
        }
        if (c == ':') {
            return 2;
        }
        if (c == '.') {
            return 3;
        }
        if (c == '?') {
            return 4;
        }
        if (c == '!') {
            return 5;
        }
        return 6;
    }
public:

    /**
     *
     * @param reader
     * @param writer
     */
    static void run_process(mqd_t reader, mqd_t writer) {
        int cnt[6];
        memset(cnt, 0, sizeof cnt);

        while (true) {
            char read_buf[TBUFFER_SIZE];

            size_t len = handler::read_part(reader, read_buf);

            if (len == 0) {
                break;
            }

            for (size_t idx = 0; idx < len; ++idx) {
                int id_char = convert(read_buf[idx]);

                if (id_char == 6) {
                    continue;
                }

                ++cnt[id_char];
            }
        }

        char writeBuff[TBUFFER_SIZE];
        for (int i = 0; i < 6; ++i) {
            snprintf(writeBuff, TBUFFER_SIZE, ", %d\n; %d\n: %d\n. %d\n? %d\n! %d\n",
                     cnt[0], cnt[1], cnt[2], cnt[3], cnt[4], cnt[5]);
        }

        handler::write_part(writer, writeBuff);
    }
};

#endif //OS_PROCESS_WORK_H
