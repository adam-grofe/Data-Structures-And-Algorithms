#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <class T> void save_vector(const std::vector<T>& v, const std::string& filepath)
{
    std::ofstream wf(filepath, std::ios::out | std::ios::binary);
    if (!wf)
    {
        throw std::runtime_error("Cannot open file: " + filepath);
    }

    auto typeSize = sizeof(T);
    for (size_t i = 0; i < v.size(); ++i)
    {
        wf.write((char*)&v[i], typeSize);
    }
    wf.close();
    if (!wf.good())
    {
        throw std::runtime_error("Error during writing of file: " + filepath);
    }
};

template <class T> std::vector<T> read_vector(size_t nElements, const std::string& filepath)
{
    std::vector<T> v(nElements);

    auto typeSize = sizeof(T);
    std::ifstream rf(filepath, std::ios::in | std::ios::binary);
    if (!rf)
    {
        throw std::runtime_error("Cannot open file for reading: " + filepath);
    }
    for (size_t i = 0; i < nElements; ++i)
    {
        rf.read((char*)&v[i], typeSize);
    }
    rf.close();
    if (!rf.good())
    {
        throw std::runtime_error("Error during reading of file: " + filepath);
    }
    return v;
};