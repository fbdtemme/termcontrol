cmake_minimum_required(VERSION 3.15)

include(FetchContent)
include(GNUInstallDirs)

find_package(ctre QUIET)
if (ctre_FOUND)
    message(STATUS "Local installation of dependency ctre found.")
else()
    message(STATUS "Fetching dependency ctre ...")
    FetchContent_Declare(
            ctre
            GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions.git
            GIT_TAG        master
    )
    # disable tests
    set(CTRE_BUILD_TESTS OFF)
    set(CTRE_BUILD_PACAKGES OFF)
    FetchContent_MakeAvailable(ctre)
endif()


find_package(utf8cpp)
if (utf8cpp_FOUND)
    message(STATUS "Local installation of dependency utf8cpp found.")
#    add_library(utf8cpp INTERFACE IMPORTED)
else()
    message(STATUS "Fetching dependency utf8-cpp...")
    FetchContent_Declare(
            utf8-cpp
            GIT_REPOSITORY https://github.com/nemtrif/utfcpp.git
            GIT_TAG        master
    )
    FetchContent_MakeAvailable(utf8-cpp)
endif()

include(FetchContent)


find_package(gsl-lite QUIET)
if (gsl-lite_FOUND)
    message(STATUS "Local installation of gsl-lite found.")
else()
    message(STATUS "Fetching dependency gsl-lite...")
    FetchContent_Declare(
            gsl-lite
            GIT_REPOSITORY https://github.com/gsl-lite/gsl-lite.git
            GIT_TAG        master
    )
    FetchContent_MakeAvailable(gsl-lite)
endif()


find_package(fmt QUIET)
if (fmt_FOUND)
    message(STATUS "Local installation of dependency fmt found.")
else()
    message(STATUS "Fetching dependency fmt...")
    FetchContent_Declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG        master
    )
    set(FMT_INSTALL ON)
    set(BUILD_SHARED_LIBS ON)
    FetchContent_MakeAvailable(fmt)
endif()
