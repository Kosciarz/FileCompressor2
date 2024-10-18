#include "Compressor.h"
#include "Compress.h"
#include "Decompress.h"

#include <iostream>
#include <string>
#include <limits>

namespace compressor
{
    void Run()
    {
        std::cout << "Welcome to File Compressor / Decompressor!\n";
        int operation{};

        do
        {
            std::cout << "\nChose operation:\n";
            std::cout << "1. Compress file\n";
            std::cout << "2. Decompress file\n";
            std::cout << "3. Exit\n";
            std::cin >> operation;

            if (std::cin.fail() || operation < 1 || operation > 3)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nEnter a valid operation! Please try again\n";
                continue;
            }

            if (operation == 3) return;

            std::cout << "Path to file: " << "\n";
            std::string file_path;
            std::cin >> file_path;

            if (operation == 1)
                CompressFile(std::move(file_path));
            if (operation == 2)
                DecompressFile(std::move(file_path));
        }
        while (true);
    }
}
