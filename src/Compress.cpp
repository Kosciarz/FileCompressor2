#include "Compress.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>
#include <cstdint>

namespace fs = std::filesystem;

static std::string GetTextToCompress(const fs::path& path);

static void WriteCodesToFile(const fs::path& path, const std::vector<std::int32_t>& codes);

namespace compressor {

    void CompressFile(const fs::path& path)
    {
        const std::string textToCompress = GetTextToCompress(path);

        std::map<std::string, std::int32_t> dict;
        std::int32_t dictSize = 256;

        for (std::int32_t i = 0; i < dictSize; i++)
            dict[{static_cast<char>(i)}] = i;

        std::vector<std::int32_t> codes;
        std::string sequence;

        for (const char character : textToCompress)
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

        WriteCodesToFile(path, codes);
    }

}

std::string GetTextToCompress(const fs::path& path)
{
    std::ifstream file(path);
    if (!file)
        std::cerr << "Error: failed to open file: " << path.string() << '\n';

    const auto fileSize = std::filesystem::file_size(path);
    std::string text(fileSize, 0);
    file.read(text.data(), fileSize);
    return text;
}

void WriteCodesToFile(const fs::path& path, const std::vector<std::int32_t>& codes)
{
    std::ofstream file(path);
    if (!file)
        std::cerr << "Error: failed to open file: " << path.string() << '\n';

    for (const std::int32_t code : codes)
        file << code << '\n';
}