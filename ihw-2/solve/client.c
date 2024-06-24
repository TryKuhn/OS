/**
 * @file
 * Client
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
 * Handler of client behavior
 */
void behavior_handler() {
    pid_t process = getpid();

    if (!generate_key()) {
        return;
    }

    if (!get_semaphore_id()) {
        return;
    }

    printf("%i: I wish to answer\n", process);

    if (!set_state(0, 0, -1)) {
        return;
    }

    printf("%i: My variant is: %i\n", process, rnd_next(1, 100));
    printf("%i: My answer is: %i\n", process, rand());

    if (!set_state(0, 1, 1)) {
        return;
    }

    printf("%i: Waiting for my mark\n", process);

    if (!set_state(0, 2, -1)) {
        return;
    }

    printf("%i: Gotten mark. I leave\n", process);

    if (!set_state(0, 0, 1)) {
        return;
    }
}

void start(long forks) {
    pid_t process;
    while (forks--) {
        process = fork();
        if (process < 0) {
            fprintf(stderr, "Unable to create fork\n");
        }
        if (process == 0) {
            behavior_handler();
        }
        if (process) {
            break;
        }
    }

    wait(NULL);
    exit(0);
}

/**
 * Run client application
 * @param argc number of cmd args. Must be equal to 1
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

    start(forks);
}
