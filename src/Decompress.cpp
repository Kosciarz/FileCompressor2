#include "Decompress.hpp"

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include <cstdint>

namespace fs = std::filesystem;

static std::vector<std::int32_t> ReadCodesFromFile(const fs::path& path);

static void WriteTextToFile(const fs::path& path, const std::string& text);

namespace compressor {

    void DecompressFile(const fs::path& path)
    {
        const std::vector<std::int32_t>& codes = ReadCodesFromFile(path);
        std::map<std::int32_t, std::string> dict;
        std::int32_t dictSize = 256;

        for (std::int32_t i = 0; i < dictSize; i++)
            dict[i] = {static_cast<char>(i)};

        std::int32_t lastCode = codes.front();
        std::string decompressedText = dict[lastCode];

        for (std::size_t i = 1; i < codes.size(); i++)
        {
            std::int32_t code = codes[i];
            if (std::string lastSequence = dict[lastCode]; dict.contains(code))
            {
                dict[dictSize++] = lastSequence + dict[code][0];
                decompressedText += dict[code];
            }
            else
            {
                std::string value = lastSequence + lastSequence[0];
                dict[dictSize++] = value;
                decompressedText += value;
            }
            lastCode = code;
        }

        WriteTextToFile(path, decompressedText);
    }

}

std::vector<std::int32_t> ReadCodesFromFile(const fs::path& path)
{
    std::ifstream file(path);
    if (!file)
        std::cerr << "Error: failed to open file: " << path.string() << '\n';

    std::vector<std::int32_t> codes;
    std::string fileLine;

    while (std::getline(file, fileLine))
        codes.push_back(std::stoi(fileLine));

    return codes;
}

void WriteTextToFile(const fs::path& path, const std::string& text)
{
    std::ofstream file(path);
    if (!file)
        std::cerr << "Error: failed to open file: " << path.string() << '\n';

    file << text;
}
