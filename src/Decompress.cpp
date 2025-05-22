#include "Decompress.hpp"

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>

namespace fs = std::filesystem;

static std::vector<int> ReadCodesFromFile(const fs::path& path);

static void WriteTextToFile(const fs::path& path, const std::string& text);

namespace compressor {

    void DecompressFile(const fs::path& path)
    {
        const std::vector<int>& codes = ReadCodesFromFile(path);
        std::map<int, std::string> dict;
        int dictSize = 256;

        for (int i = 0; i < dictSize; i++)
            dict[i] = {static_cast<char>(i)};

        int lastCode = codes.front();
        std::string decompressedText = dict[lastCode];

        for (std::size_t i{1}; i < codes.size(); i++)
        {
            int code = codes[i];
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

std::vector<int> ReadCodesFromFile(const fs::path& path)
{
    std::ifstream file(path);
    if (!file)
        std::cerr << "Error opening the file!" << '\n';

    std::vector<int> codes;
    std::string fileLine;

    while (std::getline(file, fileLine))
        codes.push_back(std::stoi(fileLine));

    return codes;
}

void WriteTextToFile(const fs::path& path, const std::string& text)
{
    std::ofstream file(path);
    if (!file)
        std::cerr << "Error opening the file!" << '\n';

    file << text;
}
