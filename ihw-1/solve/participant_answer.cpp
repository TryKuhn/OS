/**
 * @file
 * Generating participant answer
 */

#include <string>
#include "err_msg.h"
#include "process_work.h"

class getPAnswer {
public:

    /**
     * Computer of participant answer
     * @param input name of input file
     * @param output name of output file
     */
    static void p_ans(const char* input, const char* output) {
        struct mq_attr attr = {0};
        attr.mq_maxmsg      = 10;
        attr.mq_msgsize     = (long)(TBUFFER_SIZE - 1);

        mqd_t reader = mq_open("/read-proc-q", O_RDONLY | O_CREAT, 0666, &attr);
        mqd_t writer = mq_open("/write-proc-q", O_WRONLY | O_CREAT, 0666, &attr);

        if (reader == -1) {
            printer::print_error("Can't open queue reader");
            return;
        }

        if (writer == -1) {
            printer::print_error("Can't close queue writer");
            return;
        }

        process::run_process(reader, writer);

        if (mq_close(reader) == -1) {
            printer::print_error("Can't close queue reader");
            return;
        }

        if (mq_close(writer) == -1) {
            printer::print_error("Can't close queue writer");
            return;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 1) {
        printer::print_error("Number of argc is not equal to one");
        return 0;
    }

    std::string test = argv[1];
    getPAnswer::p_ans(("tests/input" + test + ".txt").c_str(),
                      ("tests/output" + test + ".txt").c_str());
}