#include <vector>
#include <algorithm>

using namespace std;

class NumMatrix //一维前缀和 时间复杂度：O(mn) 空间复杂度：O(mn)
{
public:
    vector<vector<int>> sums;

    NumMatrix(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        if (m > 0)
        {
            int n = matrix[0].size();
            sums.resize(m, vector<int>(n + 1));
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    sums[i][j + 1] = sums[i][j] + matrix[i][j];
                }
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        int sum = 0;
        for (int i = row1; i <= row2; i++)
        {
            sum += sums[i][col2 + 1] - sums[i][col1];
        }
        return sum;
    }
};

class NumMatrix2
{ //二维前缀和 时间复杂度：O(mn) 空间复杂度：O(mn)
public:
    vector<vector<int>>
        sums;

    NumMatrix2(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        if (m > 0)
        {
            int n = matrix[0].size();
            sums.resize(m + 1, vector<int>(n + 1));
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] - sums[i][j] + matrix[i][j];
                }
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return sums[row2 + 1][col2 + 1] - sums[row1][col2 + 1] - sums[row2 + 1][col1] + sums[row1][col1];
    }
};
