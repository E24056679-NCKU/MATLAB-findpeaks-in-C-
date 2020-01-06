#include "Cpp_FindPeaks.h"

#include <iostream>
#include <vector>
#include <cfloat>
#include <cmath>
#include <algorithm>

using namespace std;

inline static bool isDoubleEqual(double a, double b)
{
    return abs(a-b) < DBL_EPSILON;
}

inline static bool isDoubleGreater(double a, double b)
{
    return (!isDoubleEqual(a, b)) && (a > b);
}

inline static bool isDoubleLess(double a, double b)
{
    return (!isDoubleEqual(a, b)) && (a < b);
}

static void __findLocalExtremaLocs(
    const vector<double> &v,
    vector<int> * pMaxLocs,
    vector<int> * pMinLocs)
{
#define pushPeak(pLocsVec, loc) \
            do{ \
                if ( (pLocsVec) != nullptr ) { \
                    (pLocsVec)->emplace_back((loc)); \
                } \
            }while(0)


    // MATLAB findpeaks() considers boundary flat as non-peak, e.g., v = [3 3 1 3 3 ], v(2) and v(4) are not peak
    int begin = 1, end = v.size()-2;
    while (v[begin] == v[begin-1])
        ++begin;
    ++begin;
    while (v[end] == v[end+1])
        --end;
    ++end;

    int extremaPos = begin-1;
    double extremaV = v[begin];

    bool isClimbing = true;

    bool (*compareFunc[2])(double a, double b) = { isDoubleLess, isDoubleGreater };

    for(int i = begin ; i < v.size() ; ++i)
    {
        /*
            if isClimbing == false
                compareFunc will be (v[i] < v[i-1])
            if isClimbing == false
                compareFunc will be (v[i] > v[i-1])
        */

        if ( compareFunc[isClimbing](v[i], v[i-1]) ) // still Climbing/Diving
        {
            extremaPos = i;
            extremaV = v[i];
        }

        if ( compareFunc[isClimbing](extremaV, v[i]) ) // end of Climbing/Diving
        {
            if (isClimbing)
                pushPeak(pMaxLocs, extremaPos);
            else
                pushPeak(pMinLocs, extremaPos);

            --i; // return to previous point (i.e., make last peak found as starting point)
            extremaPos = i;
            extremaV = v[i];
            isClimbing = not isClimbing;
        }
    }

#undef pushPeak
}

void findLocalMaximaLocs(const vector<double> &v, vector<int> &maxLocs)
{
    __findLocalExtremaLocs(v, &maxLocs, nullptr);
}

void findLocalMinimaLocs(const vector<double> &v, vector<int> &minLocs)
{
    __findLocalExtremaLocs(v, nullptr, &minLocs);
}

void findLocalExtremaLocs(
    const vector<double> &v,
    vector<int> &maxLocs,
    vector<int> &minLocs)
{
    __findLocalExtremaLocs(v, &maxLocs, &minLocs);
}
