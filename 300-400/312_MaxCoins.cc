
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> rec;
    vector<int> val;

public:
    int solve(int left, int right)
    {
        if (left >= right - 1)
        {
            return 0;
        }
        if (rec[left][right] != -1)
        {
            return rec[left][right];
        }
        for (int i = left + 1; i < right; i++)
        {
            int sum = val[left] * val[i] * val[right];
            sum += solve(left, i) + solve(i, right);
            rec[left][right] = max(rec[left][right], sum);
        }
        return rec[left][right];
    }

    int maxCoins(vector<int> &nums)
    {
        int n = nums.size();
        val.resize(n + 2);
        for (int i = 1; i <= n; i++)
        {
            val[i] = nums[i - 1];
        }
        val[0] = val[n + 1] = 1;
        rec.resize(n + 2, vector<int>(n + 2, -1));
        return solve(0, n + 1);
    }
};

class Solution2 //DP
{
public:
    int maxCoins(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> rec(n + 2, vector<int>(n + 2));
        vector<int> val(n + 2);
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; i++)
        {
            val[i] = nums[i - 1];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 2; j <= n + 1; j++)
            {
                for (int k = i + 1; k < j; k++)
                {
                    int sum = val[i] * val[k] * val[j];
                    sum += rec[i][k] + rec[k][j];
                    rec[i][j] = max(rec[i][j], sum);
                }
            }
        }
        return rec[0][n + 1];
    }
};

