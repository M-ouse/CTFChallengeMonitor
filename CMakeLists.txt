cmake_minimum_required(VERSION 3.17)
project(CTFChallengeMonitor)

set(CMAKE_CXX_STANDARD 14)

add_executable(CTFChallengeMonitor main.cpp socket.hpp basic.hpp parser.hpp)