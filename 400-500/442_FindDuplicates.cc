
#include <bits/stdc++.h>

using namespace std;

class Solution // hash in place
{
public:
    vector<int> findDuplicates(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ret;
        for (auto &num : nums)
        {
            int x = (num - 1) % n;
            nums[x] += n;
        }

        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > 2 * n)
                ret.push_back(i + 1);
        }
        return ret;
    }
};