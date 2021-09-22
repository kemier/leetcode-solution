#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {//记忆化搜索 + 二分查找  O(n^2logn) O(n^2)
public:
    vector<unordered_map<int, int>> rec;

    bool dfs(vector<int>& stones, int i, int lastDis) {
        if (i == stones.size() - 1) {
            return true;
        }
        if (rec[i].count(lastDis)) {
            return rec[i][lastDis];
        }
        for (int curDis = lastDis - 1; curDis <= lastDis + 1; curDis++) {
            if (curDis > 0) {
                int j = lower_bound(stones.begin(), stones.end(), curDis + stones[i]) - stones.begin();
                if (j != stones.size() && stones[j] == curDis + stones[i] && dfs(stones, j, curDis)) {
                    return rec[i][lastDis] = true;
                }
            }
        }
        return rec[i][lastDis] = false;
    }

    bool canCross(vector<int>& stones) {
        int n = stones.size();
        rec.resize(n);
        return dfs(stones, 0, 0);
    }
};



class Solution2 {//动态规划  O(n^2)  O(n^2)
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        vector<vector<int>> dp(n, vector<int>(n));
        dp[0][0] = true;
        for (int i = 1; i < n; ++i) {
            if (stones[i] - stones[i - 1] > i) {
                return false;
            }
        }
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                int k = stones[i] - stones[j];
                if (k > j + 1) {
                    break;
                }
                dp[i][k] = dp[j][k - 1] || dp[j][k] || dp[j][k + 1];
                if (i == n - 1 && dp[i][k]) {
                    return true;
                }
            }
        }
        return false;
    }
};

