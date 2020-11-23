cmake_minimum_required(VERSION 3.16.5)
project(build C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(tsrc)
include_directories(tests)

add_executable(shell
        sqlite3.c
        sqlite3.h
        shell.c)

add_executable(tests
        sqlite3.c
        sqlite3.h
        tests/myTest.c)
