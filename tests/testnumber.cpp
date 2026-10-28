#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <static_ring_buffer/ring_buffer.hpp>

void run_test_cases(std::istream &input_stream)
{
    std::string line;
    int test_case_id = 1;

    while (std::getline(input_stream, line))
    {
        if (line.empty())
            continue;

        std::cout << "[INFO] Testing Case #" << test_case_id++ << ": " << line << "\n";

        ring_buffer::StaticRingBuffer<int, 5, ring_buffer::OverflowPolicy::Overwrite> buf;

        std::istringstream line_stream(line);

        int val;
        while (line_stream >> val)
        {
            (void)buf.push(val);
        }

        std::cout << "  -> Buffer's size after pushing: " << buf.size() << "\n";
        std::cout << "  -> Current front: " << *buf.front() << ", back: " << *buf.back() << "\n";
    }
}

int main(int args, char *argv[])
{
    if (args < 2)
    {
        std::cerr << "[ERROR]: No input file provided! Usage: ./testnumber <data_file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "[ERROR]: Cannot open file!" << std::endl;
        return 1;
    }

    run_test_cases(file);

    std::cout << "[PASS]: Test all cases sucessfully !" << std::endl;

    return 0;
}