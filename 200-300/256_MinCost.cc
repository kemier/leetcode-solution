#include <vector>
#include <climits>

using namespace std;

class Solution
{
public:
    // 典型的动态规划问题
    int minCost(vector<vector<int>> &costs)
    {
        if (costs.empty())
            return 0;
        vector threeCosts = costs[0];
        for (int i = 1; i < costs.size(); i++)
        {
            vector res(3, 0);
            res[0] = costs[i][0] + min(threeCosts[1], threeCosts[2]);
            res[1] = costs[i][1] + min(threeCosts[0], threeCosts[2]);
            res[2] = costs[i][2] + min(threeCosts[0], threeCosts[1]);
            threeCosts = res;
        }
        return getMin(threeCosts);
    }

    int minCost(vector<vector> &costs)
    {
        vector<int> res;
        res = minCost(costs, costs.size() - 1);
        return getMin(res);
    }
    vector minCost(vector<vector> &costs, int n)
    {
        vector<int> threeCosts(3, 0);
        if (n == 0)
        {
            threeCosts[0] = costs[0][0];
            threeCosts[1] = costs[0][1];
            threeCosts[2] = costs[0][2];
            return threeCosts;
        }
        threeCosts = minCost(costs, n - 1);
        vector<int> res(3, 0);
        // 更新第1个位置
        res[0] = costs[n][0] + min(threeCosts[1], threeCosts[2]);
        res[1] = costs[n][1] + min(threeCosts[0], threeCosts[2]);
        res[2] = costs[n][2] + min(threeCosts[0], threeCosts[1]);
        return res;
    }
};

class Solution2
{
public:
    int minCost(vector<vector<int>> &costs)
    {
        int n = costs.size(), house, color;
        if (n == 0)
            return 0;
        vector<vector<int>> dp(n, vector<int>(3, INT_MAX));
        dp[0] = costs[0];
        for (house = 1; house < n; house++)
        {
            for (color = 0; color < 3; ++color)
            {
                dp[house][color] = min(dp[house][color], costs[house][color] + min(dp[house - 1][(color + 1) % 3], dp[house - 1][(color + 2) % 3]));
            }
        }
        return min(dp[n - 1][0], min(dp[n - 1][1], dp[n - 1][2]));
    }
};

class Solution3
{
public:
    int minCost(vector<vector<int>> &costs)
    {
        if (costs.size() == 0)
            return 0;
        for (int i = costs.size() - 2; i > -1; i--)
        {
            for (int j = 0; j < 3; j++)
            {
                if (j == 0)
                {
                    costs[i][j] = costs[i][j] + min(costs[i + 1][1], costs[i + 1][2]);
                }
                else if (j == 1)
                {
                    costs[i][j] = costs[i][j] + min(costs[i + 1][0], costs[i + 1][2]);
                }
                else
                {
                    costs[i][j] = costs[i][j] + min(costs[i + 1][1], costs[i + 1][0]);
                }
            }
        }
        return min(costs[0][0], min(costs[0][1], costs[0][2]));
    }
};
