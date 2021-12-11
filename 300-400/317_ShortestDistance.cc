#include <queue>
#include <vector>
#include <climits>

using namespace std;

class Solution
{
public:
    int shortestDistance(vector<vector<int>> &grid)
    {
        if (grid.size() == 0)
            return 0;
        int m = grid.size(), n = grid[0].size(), ans, flag = 0;
        vector<pair<int, int>> dir{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<vector<int>> cnt(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] != 1)
                    continue;
                ans = INT_MAX;
                queue<pair<int, int>> que;
                que.push(make_pair(i * n + j, 0));
                while (!que.empty())
                {
                    auto val = que.front();
                    que.pop();
                    for (auto v : dir)
                    {
                        int x = val.first / n + v.first, y = val.first % n + v.second;
                        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != flag)
                            continue;
                        cnt[x][y] += val.second + 1, grid[x][y]--;
                        ans = min(ans, cnt[x][y]);
                        que.push(make_pair(x * n + y, val.second + 1));
                    }
                }
                flag--;
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};