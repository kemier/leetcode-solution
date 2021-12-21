#include <vector>
#include <algorithm>
using namespace std;

class Solution //递归
{
public:
    bool PredictTheWinner(vector<int> &nums)
    {
        return total(nums, 0, nums.size() - 1, 1) >= 0;
    }

    int total(vector<int> &nums, int start, int end, int turn)
    {
        if (start == end)
        {
            return nums[start] * turn;
        }
        int scoreStart = nums[start] * turn + total(nums, start + 1, end, -turn);
        int scoreEnd = nums[end] * turn + total(nums, start, end - 1, -turn);
        return max(scoreStart * turn, scoreEnd * turn) * turn;
    }
};

class Solution2 //动态规划
{
public:
    bool PredictTheWinner(vector<int> &nums)
    {
        int length = nums.size();
        auto dp = vector<vector<int>>(length, vector<int>(length));
        for (int i = 0; i < length; i++)
        {
            dp[i][i] = nums[i];
        }
        for (int i = length - 2; i >= 0; i--)
        {
            for (int j = i + 1; j < length; j++)
            {
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }
        return dp[0][length - 1] >= 0;
    }
};

。
