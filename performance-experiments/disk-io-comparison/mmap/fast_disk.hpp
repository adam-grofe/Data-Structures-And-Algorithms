#pragma once

#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/mman.h>
#include <unistd.h>
#include <vector>

template <class T> void save_vector(const std::vector<T>& v, const std::string& filePath)
{
    size_t n = v.size();
    size_t tSize = sizeof(T);
    size_t nBytes = n * tSize;

    // Open File
    int fd = open(filePath.c_str(), O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1)
    {
        throw std::runtime_error("Could not open file:" + filePath);
    }
    int result = lseek(fd, nBytes - 1, SEEK_SET);
    if (result == -1)
    {
        close(fd);
        throw std::runtime_error("Could not seek in file:" + filePath);
    }

    result = write(fd, "", 1);
    if (result != 1)
    {
        close(fd);
        throw std::runtime_error("Could not write in file:" + filePath);
    }

    T* map = (T*)mmap(0, nBytes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        close(fd);
        throw std::runtime_error("Could not create map");
    }
    for (size_t i = 0; i < n; ++i)
    {
        map[i] = v[i];
    }
    if (munmap(map, nBytes))
    {
        close(fd);
        throw std::runtime_error("Could not write map to disk");
    }
    close(fd);
}

template <class T> std::vector<T> read_vector(size_t nElements, const std::string& filePath)
{
    size_t nBytes = nElements * sizeof(T);

    int fd = open(filePath.c_str(), O_RDONLY);
    if (fd == -1)
    {
        throw std::runtime_error("Error open file " + filePath);
    }

    T* map = (T*)mmap(0, nBytes, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        close(fd);
        throw std::runtime_error("Error mapping file on read");
    }
    std::vector<T> v(nElements);
    for (size_t i = 0; i < nElements; ++i)
    {
        v[i] = map[i];
    }
    close(fd);
    return v;
}
