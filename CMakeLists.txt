cmake_minimum_required(VERSION 3.21)
project(matrixiteratos)

set(CMAKE_CXX_STANDARD 17)
include_directories(inc)
include_directories(src)


set(TARGET_NAME IIterator)

set(SOURCES main.cpp
        src/Sorter.cpp
        src/Loader.cpp
        src/MList.cpp
        src/Matrix.cpp
        src/IIterator.cpp)

add_executable(${TARGET_NAME}
                ${SOURCES})
