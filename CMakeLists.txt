cmake_minimum_required(VERSION 3.7)
project(DistributedWanderJoin)

set(CMAKE_CXX_STANDARD 11)

add_executable(DistributedWanderJoin main.cpp entries.h date.h entries.cpp Q3.cpp Q3.h tables.cpp tables.h index.cpp index.h)

#find_package(Boost)

find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(DistributedWanderJoin ${MPI_C_LIBRARIES})
