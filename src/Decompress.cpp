#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include <cstdint>

#include "Decompress.hpp"
#include "Result.hpp"

namespace fs = std::filesystem;

static Result<std::vector<std::uint32_t>, std::string> ReadCodesFromFile(const fs::path& path);

static Result<void, std::string> WriteTextToFile(const fs::path& path, const std::string& text);

namespace compressor {

    Result<void, std::string> DecompressFile(const fs::path& path)
    {
        const auto& codesResult = ReadCodesFromFile(path);
        if (!codesResult)
            return Result<void, std::string>::Err(codesResult.Error());

        const auto& codes = codesResult.Value();

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

        const auto& writeResult = WriteTextToFile(path, decompressedText);
        if (!writeResult)
            return Result<void, std::string>::Err(writeResult.Error());
        return Result<void, std::string>::Ok();
    }

}

Result<std::vector<std::uint32_t>, std::string> ReadCodesFromFile(const fs::path& path)
{
    std::ifstream file(path);
    if (!file)
        return Result<std::vector<std::uint32_t>, std::string>::Err("Failed to open file: " + path.string());

    std::vector<std::uint32_t> codes;
    std::string fileLine;

    while (std::getline(file, fileLine))
        codes.push_back(std::stoi(fileLine));

    return Result<std::vector<std::uint32_t>, std::string>::Ok(codes);
}

Result<void, std::string> WriteTextToFile(const fs::path& path, const std::string& text)
{
    std::ofstream file(path);
    if (!file)
        return Result<void, std::string>::Err("Failed to open file: " + path.string());

    file << text;
    return Result<void, std::string>::Ok();
}
