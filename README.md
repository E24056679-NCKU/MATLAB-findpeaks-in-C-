# MATLAB findpeaks in C++
Implementation of MATLAB findpeaks function in C++

Three functions for finding local_maxima or local_minima or both
These three functions are the wrapper functions of the same function

void findLocalMaxima(const std::vector<double> &v, std::vector<double> &maxPks, std::vector<int> &maxLocs);

void findLocalMinima(const std::vector<double> &v, std::vector<double> &minPks, std::vector<int> &minLocs);

void findLocalExtrema(
    const std::vector<double> &v,
    std::vector<double> &maxPks, std::vector<int> &maxLocs,
    std::vector<double> &minPks, std::vector<int> &minLocs);
