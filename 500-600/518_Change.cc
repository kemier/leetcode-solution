#include <vector>
using namespace std;

//source: https://leetcode-cn.com/problems/coin-change-2/
//dp
//Time complexity: O(n*m)
//Space complexity: O(n)
//n是amount，m是coins的长度

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        vector<int> dp(amount + 1), valid(amount + 1);
        dp[0] = 1;
        valid[0] = 1;
        for (int &coin : coins)
        {
            for (int i = coin; i <= amount; i++)
            {
                valid[i] |= valid[i - coin];
            }
        }
        if (!valid[amount])
            return 0;
        for (int &coin : coins)
        {
            for (int i = coin; i <= amount; i++)
            {
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
};

