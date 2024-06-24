/**
* @file
 * Reader input/output as another app
*/

#include <string>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>

#include "err_msg.h"
#include "io.h"

/**
 * Sender of input through the queue and handler
 */
class runIO {
    /**
     * Reader part of input through the file
     * @param reader reader file
     * @param buff buffer where to read
     * @return length of string
     */
    static ssize_t read_part(int reader, char* buff) {
        ssize_t bytes_read =
                read(reader, buff, TBUFFER_SIZE - 1);

        if (bytes_read < 0) {
            printer::print_error("Can't read from input file");
            return 0;
        }

        return bytes_read;
    }

    /**
     * Reader part of user output
     * @param writer writer queue
     * @param buff buffer from where to write
     * @return length of the string
     */
    static ssize_t write_part (mqd_t writer, char* buff) {
        ssize_t bytes_read =
                mq_receive(writer, buff, TBUFFER_SIZE - 1, nullptr);

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
     * Reads file from input, send it to user
     * Read file from user output, save it to file
     * @param reader reader queue
     * @param writer writer queue
     * @param read_file reader file
     * @param write_file writer file
     */
    static void run_process(mqd_t reader, mqd_t writer, int read_file, int write_file) {
        while (true) {
            char read_buff[TBUFFER_SIZE];

            ssize_t len = read_part(read_file, read_buff);

            if (len == 0) {
                break;
            }

            if (mq_send(reader, read_buff, (size_t)len, 0) == -1) {
                printer::print_error("Can't send data to process");
            }
        }
        printer::end_of_communication(reader);

        while (true) {
            char write_buff[TBUFFER_SIZE];

            ssize_t len = write_part(writer, write_buff);

            if (len == 0) {
                break;
            }

            if (write(write_file, write_buff, (size_t)len) < 0) {
                printer::print_error("Can't write to output file");
            }
        }
    }
public:
    /**
     * Handler of queues and files
     * @param input name of input file
     * @param output name of output file
     */
    static void run_input_output(const char* input, const char* output) {
        int read_file = open(input, O_RDONLY);
        int write_file = open(output, O_WRONLY | O_CREAT, 0644);

        bool ok = true;

        if (read_file == -1) {
            printer::print_error("Can't open input file");
            ok = false;
        }

        if (write_file == -1) {
            printer::print_error("Can't open output file");
            ok = false;
        }

        struct mq_attr attr = {0};
        attr.mq_maxmsg      = 10;
        attr.mq_msgsize     = (long)(TBUFFER_SIZE - 1);

        mqd_t reader = mq_open("/read-proc-q", O_WRONLY | O_CREAT, 0666, &attr);
        mqd_t writer = mq_open("/write-proc-q", O_RDONLY | O_CREAT, 0666, &attr);

        if (reader == -1) {
            printer::print_error("Can't open queue reader");
            ok = false;
        }

        if (writer == -1) {
            printer::print_error("Can't open queue writer");
            ok = false;
        }

        if (ok) {
            run_process(reader, writer, read_file, write_file);
        }

        if (close(read_file) < 0) {
            printer::print_error("Can't close input file");
        }

        if (close(write_file) < 0) {
            printer::print_error("Can't close output file");
        }

        if (mq_close(reader) == -1) {
            printer::print_error("Can't close queue reader");
        }
        mq_unlink("/read-proc-q");

        if (mq_close(writer) == -1) {
            printer::print_error("Can't close queue writer");
        }
        mq_unlink("/write-proc-q");
    }
};

/**
 * Run of the process
 * @param argc cmd line args count
 * @param argv cmd line args
 * @return 0 if everything is ok
 * @return code of error otherwise
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printer::print_error("Number of argc is not equal to one");
        return 0;
    }

    std::string test = argv[1];


    runIO::run_input_output((R"(../test/tests/input)" + test + ".txt").c_str(),
                            (R"(../test/tests/output)" + test + ".txt").c_str());
}