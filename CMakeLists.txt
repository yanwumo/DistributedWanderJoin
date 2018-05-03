cmake_minimum_required(VERSION 3.7)
project(DistributedWanderJoin)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost)

add_executable(DistributedWanderJoin main.cpp entries.h date.h entries.cpp Q3.cpp Q3.h tables.cpp tables.h index.cpp index.h)