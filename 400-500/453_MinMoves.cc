#include <bits/stdc++.h>

using namespace std;

class Solution // Use Math
{
public:
    int minMoves(vector<int> &nums)
    {
        int minNum = *min_element(nums.begin(), nums.end());
        int res = 0;
        for (int num : nums)
        {
            res += num - minNum;
        }
        return res;
    }
};
