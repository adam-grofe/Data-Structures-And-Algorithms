
#include "file_io.hpp"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string filePath = "temp.bin";
    size_t N = 1000;
    int factor = 4;

    std::vector<int> v(N);
    for (size_t i = 0; i < N; ++i)
    {
        v[i] = factor * i;
    }

    save_vector<int>(v, filePath);

    std::vector<int> newVec = read_vector<int>(N, filePath);

    for (size_t i = 0; i < N; ++i)
    {
        if (v[i] != newVec[i])
        {
            throw std::runtime_error("Vectors are not equal");
        }
    }
    std::cout << "Disk IO was successful!" << std::endl;

    return 0;
}