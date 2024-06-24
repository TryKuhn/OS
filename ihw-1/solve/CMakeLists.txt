add_executable(RunMain participant_answer.cpp)
message(STATUS "${Green} Core is loaded ${ColourReset}")

add_executable(RunIO io_runner.cpp)
message(STATUS "${Green} Input/Output thread is loaded ${ColourReset}")
