#ifndef __CPP_FINDPEAKS__
#define __CPP_FINDPEAKS__

#include <vector>

void findLocalMaxima(const std::vector<double> &v, std::vector<double> &maxPks, std::vector<int> &maxLocs);

void findLocalMinima(const std::vector<double> &v, std::vector<double> &minPks, std::vector<int> &minLocs);

void findLocalExtrema(
    const std::vector<double> &v,
    std::vector<double> &maxPks, std::vector<int> &maxLocs,
    std::vector<double> &minPks, std::vector<int> &minLocs);

#endif
