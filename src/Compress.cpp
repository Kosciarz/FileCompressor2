#include "Compress.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

static std::string GetTextToCompress(const std::string& file_path);
static void WriteCodesToFile(
    const std::string& file_path,
    std::vector<int>&& codes
);

namespace compressor
{
    void CompressFile(std::string&& file_path)
    {
        const std::string text_to_compress = GetTextToCompress(file_path);

        std::map<std::string, int> dict;
        int dict_size{256};

        for (int i{}; i < dict_size; i++)
            dict[{static_cast<char>(i)}] = i;

        std::vector<int> codes;
        std::string sequence;

        for (const char& character : text_to_compress)
        {
            if (const std::string chars_to_add = sequence + character; dict.contains(chars_to_add))
                sequence = chars_to_add;
            else
            {
                codes.push_back(dict[sequence]);
                dict[chars_to_add] = dict_size++;
                sequence = character;
            }
        }

        if (!sequence.empty())
            codes.push_back(dict[sequence]);

        WriteCodesToFile(file_path, std::move(codes));
    }
}

std::string GetTextToCompress(const std::string& file_path)
{
    std::fstream file;
    file.open(file_path, std::fstream::in);

    if (!file.is_open())
        std::cerr << "Error: could not open the file!" << "\n";


    std::string data, file_line;

    while (std::getline(file, file_line))
        data += file_line + "\n";

    return data;
}

void WriteCodesToFile(
    const std::string& file_path,
    std::vector<int>&& codes
)
{
    std::fstream file;
    file.open(file_path, std::fstream::out | std::fstream::trunc);

    if (!file.is_open())
        std::cerr << "Error: could not open the file!" << "\n";


    for (const int& code : codes)
        file << code << "\n";

    file.close();
}
