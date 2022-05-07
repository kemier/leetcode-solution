#include <bits/stdc++.h>

using namespace std;

class Solution // backtrack + memoization
{
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
        if (maxChoosableInteger >= desiredTotal)
            return true;
        if ((1 + maxChoosableInteger) * maxChoosableInteger / 2 < desiredTotal)
            return false;
        vector<int> dp(1 << maxChoosableInteger, 0);
        return dfs(0, desiredTotal, dp, maxChoosableInteger) == 1;
    }

private:
    int dfs(int state, int desiredTotal, vector<int> &dp, int maxChoosableInteger)
    {
        if (dp[state] != 0)
        {
            return dp[state];
        }

        for (int i = 1; i <= maxChoosableInteger; i++)
        {
            int cur = 1 << (i - 1);
            if ((cur & state) != 0)
            {
                continue;
            }
            // this turn choose number larger than desiredTotal or next turn opponent can't win
            if (i >= desiredTotal || dfs(cur | state, desiredTotal - i, dp, maxChoosableInteger) == 2)
            {
                return dp[state] = 1; // 1 defines win
            }
        }
        return dp[state] = 2; // 2 defines lose
    }
};
