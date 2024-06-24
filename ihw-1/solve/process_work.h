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
     * @return if given annotation mark - index
     * @return END_OF_ARRAY otherwise
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
     * Reads files from query, calculate answer and returns it back through the query
     * @param reader reader queue
     * @param writer writer queue
     */
    static void run_process(mqd_t reader, mqd_t writer) {
        int cnt[6];
        memset(cnt, 0, sizeof cnt);

        while (true) {
            char read_buf[TBUFFER_SIZE];

            ssize_t len = handler::read_part(reader, read_buf);

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

        char* write_buff;

        std::string cur = ", " + std::to_string(cnt[0]) + "\n";
        write_buff = cur.data();

        handler::write_part(writer, write_buff, cur.size());

        cur = "; " + std::to_string(cnt[1]) + "\n";
        write_buff = cur.data();

        handler::write_part(writer, write_buff, cur.size());

        cur = ": " + std::to_string(cnt[2]) + "\n";
        write_buff = cur.data();

        handler::write_part(writer, write_buff, cur.size());

        cur = ". " + std::to_string(cnt[3]) + "\n";
        write_buff = cur.data();

        handler::write_part(writer, write_buff, cur.size());

        cur = "? " + std::to_string(cnt[4]) + "\n";
        write_buff = cur.data();

        handler::write_part(writer, write_buff, cur.size());

        cur = "! " + std::to_string(cnt[5]) + "\n";
        write_buff = cur.data();

        handler::write_part(writer, write_buff, cur.size());
    }
};

#endif //OS_PROCESS_WORK_H
