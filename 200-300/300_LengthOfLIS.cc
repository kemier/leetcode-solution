#include <vector>
#include <algorithm>

using namespace std;
class Solution //DP 时间复杂度：O(n^2)  空间复杂度：O(n)
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = (int)nums.size();
        if (n == 0)
        {
            return 0;
        }
        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i)
        {
            dp[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

class Solution2 //贪心+二分查找 时间复杂度：O(n\log n)  空间复杂度：O(n)
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int len = 1, n = (int)nums.size();
        if (n == 0)
        {
            return 0;
        }
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] > d[len])
            {
                d[++len] = nums[i];
            }
            else
            {
                int l = 1, r = len, pos = 0; // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r)
                {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i])
                    {
                        pos = mid;
                        l = mid + 1;
                    }
                    else
                    {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};
