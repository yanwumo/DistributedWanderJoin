cmake_minimum_required(VERSION 3.10)
project(DistributedWanderJoin)

set(CMAKE_CXX_STANDARD 17)

add_executable(DistributedWanderJoin main.cpp entries.h date.h entries.cpp Q3.cpp Q3.h tables.cpp tables.h index.cpp index.h)