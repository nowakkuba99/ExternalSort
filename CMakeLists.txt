cmake_minimum_required(VERSION 3.0.0)
project(ExternalSort VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

add_subdirectory(testing)
add_library(readFile src/fileReader.cpp)
add_library(writeFile src/fileWriter.cpp)
add_library(solver src/solver.cpp)

target_include_directories(readFile PUBLIC src)
target_include_directories(writeFile PUBLIC src)
target_include_directories(solver PUBLIC src)

add_executable(ExternalSort src/main.cpp src/fileReader.cpp src/fileWriter.cpp src/solver.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

