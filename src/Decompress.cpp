#include "Decompress.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

static std::vector<int> ReadCodesFromFile(const std::string& file_path);
static void WriteTextToFile(const std::string& file_path, std::string&& text);

namespace compressor
{
    void DecompressFile(std::string&& file_path)
    {
        const std::vector<int>& codes = ReadCodesFromFile(file_path);
        std::map<int, std::string> dict;
        int dict_size{256};

        for (int i{}; i < dict_size; i++)
            dict[i] = {static_cast<char>(i)};

        int last_code = codes.front();
        std::string decompressed_text = dict[last_code];

        for (std::size_t i{1}; i < codes.size(); i++)
        {
            int code = codes[i];
            if (std::string last_sequence = dict[last_code]; dict.contains(code))
            {
                dict[dict_size++] = last_sequence + dict[code][0];
                decompressed_text += dict[code];
            }
            else
            {
                std::string value = last_sequence + last_sequence[0];
                dict[dict_size++] = value;
                decompressed_text += value;
            }
            last_code = code;
        }

        WriteTextToFile(file_path, std::move(decompressed_text));
    }
}

std::vector<int> ReadCodesFromFile(const std::string& file_path)
{
    std::fstream file;
    file.open(file_path, std::fstream::in);

    if (!file.is_open())
        std::cerr << "Error opening the file!" << '\n';

    std::vector<int> codes;
    std::string file_line;

    while (std::getline(file, file_line))
        codes.push_back(std::stoi(file_line));

    file.close();
    return codes;
}

void WriteTextToFile(const std::string& file_path, std::string&& text)
{
    std::fstream file;
    file.open(file_path, std::fstream::trunc | std::fstream::out);

    if (!file.is_open())
    {
        std::cerr << "Error opening the file!" << '\n';
        throw std::runtime_error("Error opening the file!");
    }

    file << text;
    file.close();
}
