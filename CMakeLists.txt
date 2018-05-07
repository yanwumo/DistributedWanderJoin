cmake_minimum_required(VERSION 3.7)
project(DistributedWanderJoin)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED)
find_package(MPI REQUIRED)
add_definitions(-DOMPI_SKIP_MPICXX)

add_executable(DistributedWanderJoin main.cpp entries.h date.h entries.cpp Q3.cpp Q3.h tables.cpp tables.h index.cpp index.h)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(DistributedWanderJoin ${MPI_C_LIBRARIES})

