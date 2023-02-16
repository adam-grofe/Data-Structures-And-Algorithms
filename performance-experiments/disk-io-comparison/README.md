# Description:
This directory tests the performance implications of using the standard
library in C++ for saving an array of data in binary compared to using 
the MMap functionality of the linux kernel. 

## Dependencies:
1. Google Benchmark


## How to Build each Test:
```bash
mkdir build 
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . 
```

## Results on my Machine:
[Benchmarking Results](https://github.com/adam-grofe/Data-Structures-And-Algorithms/blob/main/performance-experiments/disk-io-comparison/results.png "Benchmarking Results")