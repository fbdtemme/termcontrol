cmake_minimum_required(VERSION 3.15)

include(FetchContent)
include(GNUInstallDirs)

find_package(ctre QUIET)
if (ctre_FOUND OR TARGET ctre::ctre)
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


find_package(utf8cpp QUIET)
if (utf8cpp_FOUND OR TARGET utf8cpp)
    message(STATUS "Local installation of dependency utf8cpp found.")
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
if (gsl-lite_FOUND OR TARGET gsl::gsl-lite-v1)
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


find_package(fmt QUIET )
if (fmt_FOUND OR TARGET fmt::fmt)
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


find_package(Catch2 QUIET)
if (Catch2_FOUND OR TARGET Catch2::Catch2)
    message(STATUS "Local installation of Catch2 found.")
else()
    message(STATUS "Fetching dependency Catch2...")
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v2.x
    )
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/contrib")
endif()