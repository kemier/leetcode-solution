#include <vector>

using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums) //DP  时间复杂度：O(n)  空间复杂度：O(n)
    {
        if (nums.empty())
        {
            return 0;
        }
        int size = nums.size();
        if (size == 1)
        {
            return nums[0];
        }
        vector<int> dp = vector<int>(size, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < size; i++)
        {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[size - 1];
    }

    int rob2(vector<int> &nums) //DP + 滚动数组优化第一种解法，减少存储，只用两个变量  时间复杂度：O(n)  空间复杂度：O(1)
    {
        if (nums.empty())
        {
            return 0;
        }
        int size = nums.size();
        if (size == 1)
        {
            return nums[0];
        }
        int first = nums[0], second = max(nums[0], nums[1]);
        for (int i = 2; i < size; i++)
        {
            int temp = second;
            second = max(first + nums[i], second);
            first = temp;
        }
        return second;
    }
};
