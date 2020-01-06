#ifndef __CPP_FINDPEAKS__
#define __CPP_FINDPEAKS__

#include <vector>

void findLocalMaximaLocs(const std::vector<double> &v, std::vector<int> &maxLocs);

void findLocalMinimaLocs(const std::vector<double> &v, std::vector<int> &minLocs);

void findLocalExtremaLocs(const std::vector<double> &v, std::vector<int> &maxLocs, std::vector<int> &minLocs);

#endif
