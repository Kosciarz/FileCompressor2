#include "Compressor.hpp"
#include "Compress.hpp"
#include "Decompress.hpp"

#include <iostream>
#include <string>
#include <limits>
#include <cstdint>

static void DisplayMenu();

namespace compressor {

    void Run()
    {
        std::cout << "Welcome to File Compressor / Decompressor!\n";
        std::uint32_t operation = 0;

        while (true)
        {
            DisplayMenu();
            std::cin >> operation;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << '\n' << "Enter a valid operation. Please try again." << '\n';
                continue;
            }

            switch (operation)
            {
                case 1:
                {
                    std::cout << "Path to file: " << "\n";
                    std::filesystem::path path{};
                    std::cin >> path;
                    CompressFile(path);
                    break;
                }
                case 2:
                {
                    std::cout << "Path to file: " << "\n";
                    std::filesystem::path path{};
                    std::cin >> path;
                    DecompressFile(path);
                    break;
                }
                case 3:
                    return;
                default:
                    std::cout << '\n' << "Enter a valid operation. Please try again." << '\n';
            }
        }
    }

}

void DisplayMenu()
{
    std::cout << "Chose operation:" << '\n';
    std::cout << "1. Compress file" << '\n';
    std::cout << "2. Decompress file" << '\n';
    std::cout << "3. Exit" << '\n';
}