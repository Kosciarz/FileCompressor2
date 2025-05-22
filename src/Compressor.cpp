#include <iostream>
#include <string>
#include <limits>
#include <cstdint>

#include "Compressor.hpp"
#include "Compress.hpp"
#include "Decompress.hpp"
#include "Result.hpp"

namespace fs = std::filesystem;

static void DisplayMenu();

namespace compressor {

    void Run()
    {
        std::cout << "Welcome to File Compressor / Decompressor!" << '\n';
        std::uint32_t operation = 0;

        while (true)
        {
            DisplayMenu();
            std::cin >> operation;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter a valid operation. Please try again." << '\n';
                continue;
            }

            switch (operation)
            {
                case 1:
                {
                    std::cout << "Path to file: " << "\n";
                    fs::path path{};
                    std::cin >> path;
                    const auto& compressResult = CompressFile(path);
                    if (!compressResult)
                        std::cerr << "Error: " << compressResult.Error() << '\n';
                    break;
                }
                case 2:
                {
                    std::cout << "Path to file: " << "\n";
                    fs::path path{};
                    std::cin >> path;
                    const auto& decompressResult = DecompressFile(path);
                    if (!decompressResult)
                        std::cerr << "Error: " << decompressResult.Error() << '\n';
                    break;
                }
                case 3:
                    return;
                default:
                    std::cerr << "Enter a valid operation. Please try again." << '\n';
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