/**
 * @file
 * Generating participant answer
 */

#include <string>
#include "err_msg.h"
#include "process_work.h"

/**
 * Getter of input through the queue and handler
 */
class getPAnswer {
public:

    /**
     * Computer of participant answer
     */
    static void p_ans() {
        struct mq_attr attr = {0};
        attr.mq_maxmsg      = 10;
        attr.mq_msgsize     = (long)(TBUFFER_SIZE - 1);

        mqd_t reader = mq_open("/read-proc-q", O_RDONLY | O_CREAT, 0666, &attr);
        mqd_t writer = mq_open("/write-proc-q", O_WRONLY | O_CREAT, 0666, &attr);

        bool ok = true;

        if (reader == -1) {
            printer::print_error("Can't open queue reader");
            ok = false;
        }

        if (writer == -1) {
            printer::print_error("Can't close queue writer");
            ok = false;
        }

        if (ok) {
            process::run_process(reader, writer);
        }
        printer::end_of_communication(writer);

        if (mq_close(reader) == -1) {
            printer::print_error("Can't close queue reader");
        }

        if (mq_close(writer) == -1) {
            printer::print_error("Can't close queue writer");
        }

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
    getPAnswer::p_ans();
}