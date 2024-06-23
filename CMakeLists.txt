cmake_minimum_required(VERSION 3.28)
project(OS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -fsanitize=undefined")

if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold  "${Esc}[1m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(White       "${Esc}[37m")
    set(BoldRed     "${Esc}[1;31m")
    set(BoldGreen   "${Esc}[1;32m")
    set(BoldYellow  "${Esc}[1;33m")
    set(BoldBlue    "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan    "${Esc}[1;36m")
    set(BoldWhite   "${Esc}[1;37m")
endif()

enable_testing()

add_subdirectory(ihw-1)
message(STATUS "${Green} HW-1 is now loaded. ${ColourReset}")

add_subdirectory(ihw-2)
message(STATUS "${Green} HW-2 is now loaded. ${ColourReset}")

add_subdirectory(ihw-3)
message(STATUS "${Green} HW-3 is now loaded. ${ColourReset}")

add_subdirectory(ihw-4)
message(STATUS "${Green} HW-4 is now loaded. ${ColourReset}")
