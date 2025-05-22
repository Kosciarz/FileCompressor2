#pragma once

#include <filesystem>
#include <string>

#include "Result.hpp"

namespace compressor {

    Result<void, std::string> DecompressFile(const std::filesystem::path& path);
    
}