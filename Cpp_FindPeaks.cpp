#include "Cpp_FindPeaks.h"

#include <iostream>
#include <vector>
#include <cfloat>
#include <cmath>

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

static void __findLocalExtrema(
    const vector<double> &v,
    vector<double> * pMaxPks, vector<int> * pMaxLocs,
    vector<double> * pMinPks, vector<int> * pMinLocs)
{
#define pushPeak(pPksVec, pLocsVec, val, loc) \
            do{ \
                if ( (pPksVec) != nullptr && (pLocsVec) != nullptr && (loc) != 0) { \
                    (pPksVec)->emplace_back((val)); \
                    (pLocsVec)->emplace_back((loc)); \
                } \
            }while(0)
#define pushMaxPeak(val, loc) pushPeak((pMaxPks), (pMaxLocs), (val), (loc))
#define pushMinPeak(val, loc) pushPeak((pMinPks), (pMinLocs), (val), (loc))


    int extremaPos = 0;
    double extremaV = v[0];

    bool isClimbing = true;

    bool (*compareFunc[2])(double a, double b) = { isDoubleLess, isDoubleGreater };

    for(int i = 1 ; i < v.size() ; ++i)
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
                pushMaxPeak(extremaV, extremaPos);
            else
                pushMinPeak(extremaV, extremaPos);

            --i; // return to previous point (i.e., make last peak found as starting point)
            extremaPos = i;
            extremaV = v[i];
            isClimbing = not isClimbing;
        }
    }

#undef pushPeak
#undef pushMaxPeak
#undef pushMinPeak
}

void findLocalMaxima(const vector<double> &v, vector<double> &maxPks, vector<int> &maxLocs)
{
    __findLocalExtrema(v, &maxPks, &maxLocs, nullptr, nullptr);
}

void findLocalMinima(const vector<double> &v, vector<double> &minPks, vector<int> &minLocs)
{
    __findLocalExtrema(v, nullptr, nullptr, &minPks, &minLocs);
}

void findLocalExtrema(
    const vector<double> &v,
    vector<double> &maxPks, vector<int> &maxLocs,
    vector<double> &minPks, vector<int> &minLocs)
{
    __findLocalExtrema(v, &maxPks, &maxLocs, &minPks, &minLocs);
}
