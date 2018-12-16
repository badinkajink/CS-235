cmake_minimum_required(VERSION 3.7)
project(JackBlack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Card.h Card.cpp Player.h Player.cpp Round.h Round.cpp JackBlackSimulator.cpp test.cpp)
add_executable(JackBlack ${SOURCE_FILES})