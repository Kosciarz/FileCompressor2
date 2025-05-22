#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>
#include <cstdint>

#include "Compress.hpp"
#include "Result.hpp"

namespace fs = std::filesystem;

Result<std::string, std::string> GetTextToCompress(const fs::path& path);

static Result<void, std::string> WriteCodesToFile(const fs::path& path, const std::vector<std::int32_t>& codes);

namespace compressor {

    Result<void, std::string> CompressFile(const fs::path& path)
    {
        const auto& textResult = GetTextToCompress(path);
        if (!textResult)
            return Result<void, std::string>::Err(textResult.Error());

        const auto& text = textResult.Value();

        std::map<std::string, std::int32_t> dict;
        std::int32_t dictSize = 256;

        for (std::int32_t i = 0; i < dictSize; i++)
            dict[{static_cast<char>(i)}] = i;

        std::vector<std::int32_t> codes;
        std::string sequence;

        for (const char character : text)
        {
            if (const std::string charsToAdd = sequence + character; dict.contains(charsToAdd))
            {
                sequence = charsToAdd;
            }
            else
            {
                codes.push_back(dict[sequence]);
                dict[charsToAdd] = dictSize++;
                sequence = character;
            }
        }

        if (!sequence.empty())
            codes.push_back(dict[sequence]);

        const auto& writeResult = WriteCodesToFile(path, codes);
        if (!writeResult)
            return Result<void, std::string>::Err(writeResult.Error());
        return Result<void, std::string>::Ok();
    }

}

Result<std::string, std::string> GetTextToCompress(const fs::path& path)
{
    std::ifstream file(path);
    if (!file)
        return Result<std::string, std::string>::Err("Failed to open file: " + path.string());

    const auto fileSize = std::filesystem::file_size(path);
    std::string text(fileSize, 0);
    file.read(text.data(), fileSize);
    return Result<std::string, std::string>::Ok(text);
}

Result<void, std::string> WriteCodesToFile(const fs::path& path, const std::vector<std::int32_t>& codes)
{
    std::ofstream file(path);
    if (!file)
        return Result<void, std::string>::Err("Failed to open file: " + path.string());

    for (const std::int32_t code : codes)
        file << code << '\n';
    
    return Result<void, std::string>::Ok();
}