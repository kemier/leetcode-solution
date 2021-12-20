#include <vector>
#include <queue>

using namespace std;

class Solution
{ //记忆化深度优先搜索
public:
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int rows, columns;

    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
        {
            return 0;
        }
        rows = matrix.size();
        columns = matrix[0].size();
        auto memo = vector<vector<int>>(rows, vector<int>(columns));
        int ans = 0;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                ans = max(ans, dfs(matrix, i, j, memo));
            }
        }
        return ans;
    }

    int dfs(vector<vector<int>> &matrix, int row, int column, vector<vector<int>> &memo)
    {
        if (memo[row][column] != 0)
        {
            return memo[row][column];
        }
        ++memo[row][column];
        for (int i = 0; i < 4; ++i)
        {
            int newRow = row + dirs[i][0], newColumn = column + dirs[i][1];
            if (newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns && matrix[newRow][newColumn] > matrix[row][column])
            {
                memo[row][column] = max(memo[row][column], dfs(matrix, newRow, newColumn, memo) + 1);
            }
        }
        return memo[row][column];
    }
};

class Solution2
{ //拓扑排序
public:
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int rows, columns;

    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
        {
            return 0;
        }
        rows = matrix.size();
        columns = matrix[0].size();
        auto outdegrees = vector<vector<int>>(rows, vector<int>(columns));
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                for (int k = 0; k < 4; ++k)
                {
                    int newRow = i + dirs[k][0], newColumn = j + dirs[k][1];
                    if (newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns && matrix[newRow][newColumn] > matrix[i][j])
                    {
                        ++outdegrees[i][j];
                    }
                }
            }
        }
        queue<pair<int, int>> q;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (outdegrees[i][j] == 0)
                {
                    q.push({i, j});
                }
            }
        }
        int ans = 0;
        while (!q.empty())
        {
            ++ans;
            int size = q.size();
            for (int i = 0; i < size; ++i)
            {
                auto cell = q.front();
                q.pop();
                int row = cell.first, column = cell.second;
                for (int k = 0; k < 4; ++k)
                {
                    int newRow = row + dirs[k][0], newColumn = column + dirs[k][1];
                    if (newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns && matrix[newRow][newColumn] < matrix[row][column])
                    {
                        --outdegrees[newRow][newColumn];
                        if (outdegrees[newRow][newColumn] == 0)
                        {
                            q.push({newRow, newColumn});
                        }
                    }
                }
            }
        }
        return ans;
    }
};

class Solution2 // DFS+记忆化搜索
{
public:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    vector<vector<int>> mem;
    int m, n;

    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size();
        n = matrix[0].size();

        mem = vector<vector<int>>(m, vector<int>(n, 0));

        int ans = 1;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ans = max(ans, dfs(i, j, matrix));
            }
        }

        return ans;
    }

    int dfs(int si, int sj, vector<vector<int>> &matrix)
    {
        if (mem[si][sj])
            return mem[si][sj];
        int step = 1;
        for (int d = 0; d < 4; d++)
        {
            int ni = si + dx[d];
            int nj = sj + dy[d];
            if (ni < 0 || nj < 0 || ni >= m || nj >= n)
                continue;
            if (matrix[ni][nj] > matrix[si][sj])
                step = max(step, 1 + dfs(ni, nj, matrix));
        }

        mem[si][sj] = step;
        return step;
    }
};
