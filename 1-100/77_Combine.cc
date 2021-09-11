#include <vector>

using namespace std;

class Solution//递归实现组合型枚举 时间复杂度：O({n \choose k} \times k)  空间复杂度：O(n + k) = O(n)
 )×k)
{
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int cur, int n, int k)
    {
        // 剪枝：temp 长度加上区间 [cur, n] 的长度小于 k，不可能构造出长度为 k 的 temp
        if (temp.size() + (n - cur + 1) < k)
        {
            return;
        }
        // 记录合法的答案
        if (temp.size() == k)
        {
            ans.push_back(temp);
            return;
        }
        // 考虑选择当前位置
        temp.push_back(cur);
        dfs(cur + 1, n, k);
        temp.pop_back();
        // 考虑不选择当前位置
        dfs(cur + 1, n, k);
    }

    vector<vector<int>> combine(int n, int k)
    {
        dfs(1, n, k);
        return ans;
    }
};

class Solution2 //非递归（字典序法）实现组合型枚举 时间复杂度：O({n \choose k} \times k)  空间复杂度：O(k)
{
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int cur, int n, int k)
    {
        // 剪枝：temp 长度加上区间 [cur, n] 的长度小于 k，不可能构造出长度为 k 的 temp
        if (temp.size() + (n - cur + 1) < k)
        {
            return;
        }
        // 记录合法的答案
        if (temp.size() == k)
        {
            ans.push_back(temp);
            return;
        }
        // 考虑选择当前位置
        temp.push_back(cur);
        dfs(cur + 1, n, k);
        temp.pop_back();
        // 考虑不选择当前位置
        dfs(cur + 1, n, k);
    }

    vector<vector<int>> combine(int n, int k)
    {
        dfs(1, n, k);
        return ans;
    }
};
