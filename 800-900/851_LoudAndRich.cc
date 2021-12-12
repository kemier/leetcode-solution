#include <vector>

using namespace std;

class Solution //DFS记忆化搜索
{
public:
    vector<int> loudAndRich(vector<vector<int>> &richer, vector<int> &quiet)
    {
        int n = quiet.size();
        vector<int> dp(n, -1), g[n];
        //建图
        for (auto &i : richer)
            g[i[1]].push_back(i[0]);
        for (int i = 0; i < n; i++)
            dfs(i, dp, quiet, g);
        return dp;
    }

    int dfs(int u, vector<int> &dp, vector<int> &quiet, vector<int> g[])
    {
        if (dp[u] != -1)
            return dp[u];

        dp[u] = u;
        for (int i : g[u])
        {
            int t = dfs(i, dp, quiet, g);
            if (quiet[dp[u]] > quiet[t])
                dp[u] = t;
        }
        return dp[u];
    }
};
