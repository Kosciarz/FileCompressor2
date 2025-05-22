cmake_minimum_required(VERSION 3.20)

project(FileCompressor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    "src/Main.cpp"
    "src/Compressor.cpp"
    "src/Compress.cpp"
    "src/Decompress.cpp"
)

set(HEADERS
    "src/Compressor.h"
    "src/Compress.h"
    "src/Decompress.h"
)

add_executable(FileCompressor ${SOURCES} ${HEADERS})