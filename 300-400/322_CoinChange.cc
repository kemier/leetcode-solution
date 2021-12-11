#include <vector>
#include <climits>

using namespace std;

class Solution {//记忆化搜索

// 时间复杂度：O(Sn)，其中S是金额，n是面额数。我们一共需要计算S个状态的答案，且每个状态F(S)由于上面的记忆化的措施只计算了一次，而计算一个状态的答案需要枚举n个面额值，所以一共需要O(Sn)的时间复杂度。
// 空间复杂度：O(S)，我们需要额外开一个长为S的数组来存储计算出来的答案F(S) 。

    vector<int>count;
    int dp(vector<int>& coins, int rem) {
        if (rem < 0) return -1;
        if (rem == 0) return 0;
        if (count[rem - 1] != 0) return count[rem - 1];
        int Min = INT_MAX;
        for (int coin:coins) {
            int res = dp(coins, rem - coin);
            if (res >= 0 && res < Min) {
                Min = res + 1;
            }
        }
        count[rem - 1] = Min == INT_MAX ? -1 : Min;
        return count[rem - 1];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 1) return 0;
        count.resize(amount);
        return dp(coins, amount);
    }
};


class Solution2 {//动态规划

// 时间复杂度：O(Sn)，其中S是金额，n是面额数。我们一共需要计算O(S)个状态，S为题目所给的总金额。对于每个状态，每次需要枚举 n个面额来转移状态，所以一共需要O(Sn) 的时间复杂度。
// 空间复杂度：O(S)。数组dp 需要开长度为总金额 S 的空间。
public:
    int coinChange(vector<int>& coins, int amount) {
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < (int)coins.size(); ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
