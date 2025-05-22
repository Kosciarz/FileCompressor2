#include "Compress.hpp"

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <map>
#include <vector>

namespace fs = std::filesystem;

static std::string GetTextToCompress(const fs::path& path);

static void WriteCodesToFile(const fs::path& path, const std::vector<int>& codes);

namespace compressor {

    void CompressFile(const fs::path& path)
    {
        const std::string textToCompress = GetTextToCompress(path);

        std::map<std::string, int> dict;
        int dictSize = 256;

        for (int i = 0; i < dictSize; i++)
            dict[{static_cast<char>(i)}] = i;

        std::vector<int> codes;
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
        std::cerr << "Error: could not open the file!" << "\n";

    const auto fileSize = std::filesystem::file_size(path);
    std::string text(fileSize, 0);
    file.read(text.data(), fileSize);
    return text;
}

void WriteCodesToFile(const fs::path& path, const std::vector<int>& codes)
{
    std::ofstream file(path);
    if (!file)
        std::cerr << "Error: could not open the file!" << "\n";

    for (const int code : codes)
        file << code << "\n";
}