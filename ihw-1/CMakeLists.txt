# true to enable module testing, false to disable
set(OS_TESTING true)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_subdirectory(solve)

if(NOT OS_TESTING)
    message(WARNING "Testing is off")
elseif(IS_SUBPROJECT)
    message(WARNING "Submodule. Not testing")
else()
    add_subdirectory(test)
    message(STATUS "${Green}OK. Tests ihw-1 are loaded${ColourReset}")
endif()
