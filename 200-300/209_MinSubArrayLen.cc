#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int minSubArrayLen(int s, vector<int> &nums) //暴力解法 时间复杂度:O(n square) 空间复杂度：O(1)
    {
        int n = nums.size();
        if (n == 0)
        {
            return 0;
        }
        int ans = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            int sum = 0;
            for (int j = i; j < n; j++)
            {
                sum += nums[j];
                if (sum >= s)
                {
                    ans = min(ans, j - i + 1);
                    break;
                }
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }

    int minSubArrayLen2(int s, vector<int> &nums) //前缀和 + 二分查找 时间复杂度:O(nlogn) 空间复杂度：O(n)
    {
        int n = nums.size();
        if (n == 0)
        {
            return 0;
        }
        int ans = INT_MAX;
        vector<int> sums(n + 1, 0);
        // 为了方便计算，令 size = n + 1
        // sums[0] = 0 意味着前 0 个元素的前缀和为 0
        // sums[1] = A[0] 前 1 个元素的前缀和为 A[0]
        // 以此类推
        for (int i = 1; i <= n; i++)
        {
            sums[i] = sums[i - 1] + nums[i - 1];
        }
        for (int i = 1; i <= n; i++)
        {
            int target = s + sums[i - 1];
            auto bound = lower_bound(sums.begin(), sums.end(), target);
            if (bound != sums.end())
            {
                ans = min(ans, static_cast<int>((bound - sums.begin()) - (i - 1)));
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }

    int minSubArrayLen3(int s, vector<int> &nums) //滑动窗口  时间复杂度:O(n) 空间复杂度：O(1)
    {
        int n = nums.size();
        if (n == 0)
        {
            return 0;
        }
        int ans = INT_MAX;
        int start = 0, end = 0;
        int sum = 0;
        while (end < n)
        {
            sum += nums[end];
            while (sum >= s)
            {
                ans = min(ans, end - start + 1);
                sum -= nums[start];
                start++;
            }
            end++;
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
