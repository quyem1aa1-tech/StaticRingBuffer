#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "[ERROR] Missing required argument: Path to test file" << std::endl;
        return 0;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "[ERROR] Cannot open file: " << argv[1] << '\n';
        return 1;
    }

    std::string name;
    while (std::getline(file, name))
    {
        std::cout << "Hello " << name << std::endl;
    }

    return 0;
}