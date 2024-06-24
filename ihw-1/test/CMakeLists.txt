add_executable(check
        check.cpp
        save_to_file.h
        ../../ihw-2/solve/server.c
        ../../ihw-3/solve/TCPClient.c
        ../../ihw-3/solve/handle_client.c)

set(LEN 10 10 10 100 100000)
set(SYMBOLS 2 26 128 128 128)

foreach(test RANGE 4)
    foreach(seed RANGE 9)
        math(EXPR test_number "${test} * 10 + ${seed}")

        list(GET LEN ${test} len)
        list(GET SYMBOLS ${test} symbols)

        add_test(
                NAME test_group_${test}_test_${seed}
                COMMAND check -test=${test_number} -N=${len} -Alpha=${symbols})
        message(STATUS "${Blue} Test name: test_group_${test}_test_${seed} ${ColourReset}")
        message(STATUS "${Blue} Added random test ${test_number}: LEN: ${len}, ALPHABET: ${symbols} ${ColourReset}")
    endforeach ()
endforeach()
