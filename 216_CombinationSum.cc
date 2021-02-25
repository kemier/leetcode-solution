#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution //二进制（子集）枚举 时间复杂度：O(M \times 2^M) M=9  空间复杂度：O(M)
{
public:
    vector<int> temp;
    vector<vector<int>> ans;

    bool check(int mask, int k, int n)
    {
        temp.clear();
        for (int i = 0; i < 9; ++i)
        {
            if ((1 << i) & mask)
            {
                temp.push_back(i + 1);
            }
        }
        return temp.size() == k && accumulate(temp.begin(), temp.end(), 0) == n;
    }

    vector<vector<int>> combinationSum(int k, int n)
    {
        for (int mask = 0; mask < (1 << 9); ++mask)
        {
            if (check(mask, k, n))
            {
                ans.emplace_back(temp);
            }
        }
        return ans;
    }
};

class Solution2 //组合枚举   时间复杂度：O({M \choose k} \times k)  空间复杂度：O(M)
{
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int cur, int n, int k, int sum)
    {
        if (temp.size() + (n - cur + 1) < k || temp.size() > k)
        {
            return;
        }
        if (temp.size() == k && accumulate(temp.begin(), temp.end(), 0) == sum)
        {
            ans.push_back(temp);
            return;
        }
        temp.push_back(cur);
        dfs(cur + 1, n, k, sum);
        temp.pop_back();
        dfs(cur + 1, n, k, sum);
    }

    vector<vector<int>> combinationSum3(int k, int n)
    {
        dfs(1, 9, k, n);
        return ans;
    }
};
