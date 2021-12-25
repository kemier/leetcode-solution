#include <vector>
#include <algorithm>

using namespace std;

class Solution //二维前缀和 + 排序
{
public:
    int kthLargestValue(vector<vector<int>> &matrix, int k)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> pre(m + 1, vector<int>(n + 1));
        vector<int> results;
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                pre[i][j] = pre[i - 1][j] ^ pre[i][j - 1] ^ pre[i - 1][j - 1] ^ matrix[i - 1][j - 1];
                results.push_back(pre[i][j]);
            }
        }

        sort(results.begin(), results.end(), greater<int>());
        return results[k - 1];
    }
};

class Solution2 //二维前缀和 + 快速选择算法
{
public:
    int kthLargestValue(vector<vector<int>> &matrix, int k)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> pre(m + 1, vector<int>(n + 1));
        vector<int> results;
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                pre[i][j] = pre[i - 1][j] ^ pre[i][j - 1] ^ pre[i - 1][j - 1] ^ matrix[i - 1][j - 1];
                results.push_back(pre[i][j]);
            }
        }

        nth_element(results.begin(), results.begin() + k - 1, results.end(), greater<int>());
        return results[k - 1];
    }
};
