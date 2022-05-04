#include <vector>
#include <string>
#include <climits>

using namespace std;

class Solution //动态规划
{
public:
    int findRotateSteps(string ring, string key)
    {
        int n = ring.size(), m = key.size();
        vector<int> pos[26];
        for (int i = 0; i < n; ++i)
        {
            pos[ring[i] - 'a'].push_back(i);
        }
        vector<vector<int>> dp(m, vector<int>(n, 0x3f3f3f3f));
        for (auto &i : pos[key[0] - 'a'])
        {
            dp[0][i] = min(i, n - i) + 1;
        }
        for (int i = 1; i < m; ++i)
        {
            for (auto &j : pos[key[i] - 'a'])
            {
                for (auto &k : pos[key[i - 1] - 'a'])
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + min(abs(j - k), n - abs(j - k)) + 1);
                }
            }
        }
        return *min_element(dp[m - 1].begin(), dp[m - 1].end());
    }
};

class Solution2 // DFS
{
public:
    vector<vector<int>> memo;
    int findRotateSteps(string ring, string key)
    {
        memo.assign(ring.size(), vector<int>(key.size(), -1));
        return dfs(ring, 0, key, 0) + key.size();
    }

    int dfs(string ring, int i, string key, int j)
    {
        int n = ring.size(), m = key.size();

        if (j == key.size())
        {
            return 0;
        }

        if (memo[i][j] != -1)
            return memo[i][j];

        int step = INT_MAX;
        for (int p = 0; p < ring.size(); p++)
        {
            if (ring[p] == key[j])
            {
                step = min(step, dfs(ring, p, key, j + 1) + min(abs(p - i), n - abs(p - i)));
            }
        }

        memo[i][j] = step;
        return memo[i][j];
    }
};
