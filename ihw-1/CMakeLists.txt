#project(ihw-1)

#
add_executable(ihw-1
        solve/main.cpp)

# true to enable module testing, false to disable
set(OS_TESTING true)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(NOT OS_TESTING)
    message(WARNING "Testing is off")
elseif(IS_SUBPROJECT)
    message(WARNING "Submodule. Not testing")
else()
    add_subdirectory(test)
    message(STATUS "${Green}OK. Tests are loaded${ColourReset}")
endif()

if(NOT IS_SUBPROJECT)
    add_subdirectory(doc)
    message(STATUS "${Green}OK. Documentation is now loaded${ColourReset}")
endif()

