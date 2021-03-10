#include <vector>
#include <algorithm>

using namespace std;

class NumArray //前缀和  时间复杂度：O(n) 空间复杂度：O(n)
{
public:
    vector<int> sums;

    NumArray(vector<int> &nums)
    {
        int n = nums.size();
        sums.resize(n + 1);
        for (int i = 0; i < n; i++)
        {
            sums[i + 1] = sums[i] + nums[i];
        }
    }

    int sumRange(int i, int j)
    {
        return sums[j + 1] - sums[i];
    }
};
