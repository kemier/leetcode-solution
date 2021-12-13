#include <vector>

using namespace std;

class Solution //强联通分量
{
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

public:
    void dfs(int x, int y, vector<vector<int>> &grid, int n, int m)
    {
        grid[x][y] = 2;
        for (int i = 0; i < 4; ++i)
        {
            int tx = dx[i] + x;
            int ty = dy[i] + y;
            if (tx < 0 || tx >= n || ty < 0 || ty >= m || grid[tx][ty] != 1)
            {
                continue;
            }
            dfs(tx, ty, grid, n, m);
        }
    }
    int count(vector<vector<int>> &grid, int n, int m)
    {
        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 1)
                {
                    cnt++;
                    dfs(i, j, grid, n, m);
                }
            }
        }
        // 还原
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 2)
                {
                    grid[i][j] = 1;
                }
            }
        }
        return cnt;
    }
    int minDays(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size();
        // 岛屿数量不为 1，陆地已经分离
        if (count(grid, n, m) != 1)
        {
            return 0;
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j])
                {
                    grid[i][j] = 0;
                    if (count(grid, n, m) != 1)
                    {
                        // 更改一个陆地单元为水单元后陆地分离
                        return 1;
                    }
                    grid[i][j] = 1;
                }
            }
        }
        return 2;
    }
};

class TarjanSCC
{
private:
    const vector<vector<int>> &edges;
    vector<int> low, dfn, fa;
    int timestamp = -1;
    int n;

private:
    // Tarjan 算法求解割点模板
    void getCuttingVertex(int u, int parent, vector<int> &ans)
    {
        low[u] = dfn[u] = ++timestamp;
        fa[u] = parent;
        int child = 0;
        bool iscv = false;
        for (int v : edges[u])
        {
            if (dfn[v] == -1)
            {
                ++child;
                getCuttingVertex(v, u, ans);
                low[u] = min(low[u], low[v]);
                if (!iscv && parent != -1 && low[v] >= dfn[u])
                {
                    ans.push_back(u);
                    iscv = true;
                }
            }
            else if (v != fa[u])
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (!iscv && parent == -1 && child >= 2)
        {
            ans.push_back(u);
        }
    }

public:
    TarjanSCC(const vector<vector<int>> &_edges) : edges(_edges), n(_edges.size()) {}

    int check()
    {
        low.assign(n, -1);
        dfn.assign(n, -1);
        fa.assign(n, -1);
        timestamp = -1;

        // cutting vertices 存储割点
        vector<int> cvs;
        // connected components count 存储连通分量个数
        int cccnt = 0;
        for (int i = 0; i < n; ++i)
        {
            if (dfn[i] == -1)
            {
                ++cccnt;
                getCuttingVertex(i, -1, cvs);
            }
        }
        // 如果连通分量个数大于 1，答案为 0
        if (cccnt > 1)
        {
            return 0;
        }
        // 如果存在割点，答案为 1
        if (!cvs.empty())
        {
            return 1;
        }
        return 2;
    }
};

class Solution2 //利用Tarjan 算法
{
private:
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    int minDays(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        // 节点重标号
        int landCount = 0;
        unordered_map<int, int> relabel;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    relabel[i * n + j] = landCount;
                    ++landCount;
                }
            }
        }
        if (!landCount)
        {
            return 0;
        }
        if (landCount == 1)
        {
            return 1;
        }

        // 添加图中的边
        vector<vector<int>> edges(landCount);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    for (int d = 0; d < 4; ++d)
                    {
                        int ni = i + dirs[d][0];
                        int nj = j + dirs[d][1];
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 1)
                        {
                            edges[relabel[i * n + j]].push_back(relabel[ni * n + nj]);
                        }
                    }
                }
            }
        }

        auto scc = TarjanSCC(edges);
        return scc.check();
    }
};
