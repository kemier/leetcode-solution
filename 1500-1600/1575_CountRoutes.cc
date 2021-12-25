#include <vector>

using namespace std;

class Solution //记忆化搜索
{
private:
    static constexpr int mod = 1000000007;
    vector<vector<int>> f;

public:
    int dfs(const vector<int> &locations, int pos, int finish, int rest)
    {
        if (f[pos][rest] != -1)
        {
            return f[pos][rest];
        }

        f[pos][rest] = 0;
        if (abs(locations[pos] - locations[finish]) > rest)
        {
            return 0;
        }

        int n = locations.size();
        for (int i = 0; i < n; ++i)
        {
            if (pos != i)
            {
                if (int cost = abs(locations[pos] - locations[i]); cost <= rest)
                {
                    f[pos][rest] += dfs(locations, i, finish, rest - cost);
                    f[pos][rest] %= mod;
                }
            }
        }
        if (pos == finish)
        {
            f[pos][rest] += 1;
            f[pos][rest] %= mod;
        }
        return f[pos][rest];
    }

    int countRoutes(vector<int> &locations, int start, int finish, int fuel)
    {
        f.assign(locations.size(), vector<int>(fuel + 1, -1));
        return dfs(locations, start, finish, fuel);
    }
};

class Solution2 //优化的动态规划
{
private:
    static constexpr int mod = 1000000007;

public:
    int countRoutes(vector<int> &locations, int start, int finish, int fuel)
    {
        int n = locations.size();
        int startPos = locations[start];
        int finishPos = locations[finish];
        sort(locations.begin(), locations.end());
        for (int i = 0; i < n; ++i)
        {
            if (startPos == locations[i])
            {
                start = i;
            }
            if (finishPos == locations[i])
            {
                finish = i;
            }
        }

        vector<vector<int>> dpL(n, vector<int>(fuel + 1));
        vector<vector<int>> dpR(n, vector<int>(fuel + 1));
        dpL[start][0] = dpR[start][0] = 1;

        for (int used = 0; used <= fuel; ++used)
        {
            for (int city = n - 2; city >= 0; --city)
            {
                if (int delta = locations[city + 1] - locations[city]; used >= delta)
                {
                    dpL[city][used] = ((used == delta ? 0 : dpL[city + 1][used - delta]) * 2 % mod + dpR[city + 1][used - delta]) % mod;
                }
            }
            for (int city = 1; city < n; ++city)
            {
                if (int delta = locations[city] - locations[city - 1]; used >= delta)
                {
                    dpR[city][used] = ((used == delta ? 0 : dpR[city - 1][used - delta]) * 2 % mod + dpL[city - 1][used - delta]) % mod;
                }
            }
        }

        int ans = 0;
        for (int used = 0; used <= fuel; ++used)
        {
            ans += (dpL[finish][used] + dpR[finish][used]) % mod;
            ans %= mod;
        }
        if (start == finish)
        {
            ans = (ans + mod - 1) % mod;
        }
        return ans;
    }
};
