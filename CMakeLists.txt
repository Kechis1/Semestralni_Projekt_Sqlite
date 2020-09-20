cmake_minimum_required(VERSION 3.17)
project(build C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(tsrc)

add_executable(shell
        sqlite3.c
        sqlite3.h
        shell.c)
