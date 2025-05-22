set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    "${SOURCE_DIR}/Main.cpp"
    "${SOURCE_DIR}/Compressor.cpp"
    "${SOURCE_DIR}/Compress.cpp"
    "${SOURCE_DIR}/Decompress.cpp"
)

set(HEADERS
    "${SOURCE_DIR}/Compressor.hpp"
    "${SOURCE_DIR}/Compress.hpp"
    "${SOURCE_DIR}/Decompress.hpp"
    "${SOURCE_DIR}/Result.hpp"
)

add_executable(FileCompressor ${SOURCES} ${HEADERS})
target_compile_options(FileCompressor PRIVATE -Wall -Werror -pedantic)