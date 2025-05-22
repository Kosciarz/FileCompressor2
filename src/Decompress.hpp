#pragma once

#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <string>

namespace compressor
{
    void DecompressFile(std::string&& file_path);
}

#endif
