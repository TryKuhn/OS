/**
 * @file
 * Server
*/

#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <wait.h>
#include <stdbool.h>
#include <time.h>

int sem_id;
key_t key;

struct sembuf buff;

/**
 * Quitting the program
 * @param sig signal
 */
void quit(int sig) {
    if (semctl(sem_id, 0, IPC_RMID, 0) < 0) {
        fprintf(stderr, "Error while destroying");
    }
    exit(0);
}

/**
 * Generates pseudo-random number
 * @param l left border
 * @param r right border
 * @return pseudo-random number in [l; r]
 */
int rnd_next(int l, int r) {
    assert(l <= r);

    return rand() % (r - l) + l;
}

/**
 * Generates key for semaphore
 * @return true if successful
 * @return false if failure
 */
bool generate_key() {
    key = ftok(".", 0);

    if (key < 0) {
        fprintf(stderr, "Cannot generate key\n");
        return false;
    }
    return true;
}

/**
 * Gets the id of semaphore
 * @return true if successful
 * @return false if failure
 */
bool get_semaphore_id() {
    sem_id = semget(key, 3, 0666 | IPC_CREAT);
    if (sem_id < 0) {
        fprintf(stderr, "Cannot get semaphore id\n");
        return false;
    }

    return true;
}

/**
 * Sets state to the semaphore
 * @param flag
 * @param num
 * @param operation
 * @return true if successful
 * @return false if failure
 */
bool set_state(short flag, int num, short operation) {
    buff.sem_flg = flag;
    buff.sem_num = num;
    buff.sem_op = operation;

    if (semop(sem_id, &buff, 1) < 0) {
        fprintf(stderr, "Error occurred with semaphore\n");
        return false;
    }
    return true;
}

/**
 * Handler of server behavior
 */
void behavior_handler(long forks) {
    signal(SIGINT, quit);

    if (!generate_key()) {
        return;
    }

    if (!get_semaphore_id()) {
        return;
    }

    if (!set_state(0, 0, 1)) {
        return;
    }

    for(int fork = 0; fork < forks; ++fork) {
        if (!set_state(0, 1, -1)) {
            return;
        }

        printf("Checking answer\n");

        usleep(rnd_next(100000, 500000));
        printf(".\n");
        usleep(rnd_next(100000, 500000));
        printf("..\n");
        usleep(rnd_next(100000, 500000));
        printf("...\n");

        int mark = rnd_next(1, 10);
        printf("Your mark: %i\n", mark);

        if (mark < 4) {
            printf("I know it is random mark, but I am your teacher and I found it to be honest. "
                   "We don't need Jonah\n");
        } else {
            printf("Well done comrade\n");
        }

        if (!set_state(0, 2, 1)) {
            return;
        }
    }
}

/**
 * Run client application
 * @param argc number of cmd args. They are no needed
 * @param argv cmd args
 * @return 0 if everything is correct
 * @return code of error otherwise
 */
int main(int argc, char* argv[]) {
    srand(time(NULL));

    assert(argc == 2);

    long forks = strtol(argv[1], NULL, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Overflow\n");
        return 0;
    }
    assert(forks > 0);

    behavior_handler(forks);
}
