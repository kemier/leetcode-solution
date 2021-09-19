#include <vector>

using namespace std;

class Solution //Brian Kernighan 算法
{
public:
    int countOnes(int x)
    {
        int ones = 0;
        while (x > 0)
        {
            x &= (x - 1);
            ones++;
        }
        return ones;
    }

    vector<int> countBits(int n)
    {
        vector<int> bits(n + 1);
        for (int i = 0; i <= n; i++)
        {
            bits[i] = countOnes(i);
        }
        return bits;
    }
};

class Solution2
{
public:
    vector<int> countBits(int n)
    {
        vector<int> bits(n + 1);
        int highBit = 0;
        for (int i = 1; i <= n; i++)
        {
            if ((i & (i - 1)) == 0)
            {
                highBit = i;
            }
            bits[i] = bits[i - highBit] + 1;
        }
        return bits;
    }
};

class Solution3
{
public:
    vector<int> countBits(int n)
    {
        vector<int> bits(n + 1);
        for (int i = 1; i <= n; i++)
        {
            bits[i] = bits[i >> 1] + (i & 1);
        }
        return bits;
    }
};

class Solution4 //动态规划
{
public:
    vector<int> countBits(int n)
    {
        vector<int> bits(n + 1);
        for (int i = 1; i <= n; i++)
        {
            bits[i] = bits[i & (i - 1)] + 1;
        }
        return bits;
    }
};
