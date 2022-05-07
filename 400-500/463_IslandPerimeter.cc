#include <bits/stdc++.h>

using namespace std;

class Solution // iteraion
{
    constexpr static int dx[4] = {0, 1, 0, -1};
    constexpr static int dy[4] = {1, 0, -1, 0};

public:
    int islandPerimeter(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j])
                {
                    int cnt = 0;
                    for (int k = 0; k < 4; ++k)
                    {
                        int tx = i + dx[k];
                        int ty = j + dy[k];
                        if (tx < 0 || tx >= n || ty < 0 || ty >= m || !grid[tx][ty])
                        {
                            cnt += 1;
                        }
                    }
                    ans += cnt;
                }
            }
        }
        return ans;
    }
};

class Solution2 // DFS
{
    constexpr static int dx[4] = {0, 1, 0, -1};
    constexpr static int dy[4] = {1, 0, -1, 0};

public:
    int dfs(int x, int y, vector<vector<int>> &grid, int n, int m)
    {
        if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == 0)
        {
            return 1;
        }
        if (grid[x][y] == 2)
        {
            return 0;
        }
        grid[x][y] = 2;
        int res = 0;
        for (int i = 0; i < 4; ++i)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            res += dfs(tx, ty, grid, n, m);
        }
        return res;
    }
    int islandPerimeter(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 1)
                {
                    ans += dfs(i, j, grid, n, m);
                }
            }
        }
        return ans;
    }
};
