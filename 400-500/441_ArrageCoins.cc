#include <bits/stdc++.h>

using namespace std;

class Solution // Binary Search
{
public:
    int arrangeCoins(int n)
    {
        int left = 1, right = n;
        while (left < right)
        {
            int mid = (right - left + 1) / 2 + left;
            if ((long long)mid * (mid + 1) <= (long long)2 * n)
            {
                left = mid;
            }
            else
            {
                right = mid - 1;
            }
        }
        return left;
    }
};

class Solution2 // Use Math
{
public:
    int arrangeCoins(int n)
    {
        return (int)((sqrt((long long)8 * n + 1) - 1) / 2);
    }
};

int main()
{
    Solution s;
    cout << s.arrangeCoins(8) << endl;
}