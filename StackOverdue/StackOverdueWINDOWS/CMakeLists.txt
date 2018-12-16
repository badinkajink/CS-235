cmake_minimum_required(VERSION 3.7)
project(StackOverdue)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES StackOverdueSimulator.cpp Book.h Account.h Time.h BookFileReader.h BookFileReader.cpp BookManager.h BookManager.cpp AccountFileReader.h AccountFileReader.cpp AccountManager.h AccountManager.cpp Administrator.h Administrator.cpp Library.h Library.cpp)
add_executable(StackOverdue ${SOURCE_FILES})