#pragma once

#include <filesystem>
#include <string>

#include "Result.hpp"

namespace compressor {

    Result<void, std::string> CompressFile(const std::filesystem::path& path);

}