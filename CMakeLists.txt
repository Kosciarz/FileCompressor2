cmake_minimum_required(VERSION 3.20)
project(FileCompressor2 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    "src/Main.cpp"
    "src/Compressor.cpp"
    "src/Compress.cpp"
    "src/Decompress.cpp"
    "src/Compressor.h"
    "src/Compress.h"
    "src/Decompress.h"
)

add_executable(FileCompressor2 ${SOURCES})