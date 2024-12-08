#include "Compressor.h"
#include "Compress.h"
#include "Decompress.h"

#include <iostream>
#include <string>
#include <limits>

void RunCompressor()
{
	std::cout << "Welcome to File Compressor / Decompressor!\n";
	int operation{};

	while (true)
	{
		std::cout << "\nChose operation:\n1. Compress file\n2. Decompress file\n3. Exit\n";
		std::cin >> operation;

		if (std::cin.fail() || operation < 1 || operation > 3)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nEnter a valid operation! Please try again\n";
			continue;
		}

		if (operation == 3)
			return;

		std::cout << "Path to file: ";
		std::string file_path;
		std::cin >> file_path;

		if (operation == 1)
			CompressFile(file_path);
		if (operation == 2)
			DecompressFile(file_path);
	}
}