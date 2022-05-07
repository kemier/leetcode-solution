#include <bits/stdc++.h>

using namespace std;

class Solution // builtin func
{
public:
    int hammingDistance(int x, int y)
    {
        return __builtin_popcount(x ^ y);
    }
};

class Solution2 // shift and compare
{
public:
    int hammingDistance(int x, int y)
    {
        int s = x ^ y, ret = 0;
        while (s)
        {
            ret += s & 1;
            s >>= 1;
        }
        return ret;
    }
};

class Solution3 // Brian Kernighan's algorithm
{
public:
    int hammingDistance(int x, int y)
    {
        int s = x ^ y, ret = 0;
        while (s)
        {
            s &= s - 1;
            ret++;
        }
        return ret;
    }
};
