#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution //递归
{
public:
    vector<TreeNode *> allPossibleFBT(int n)
    {
        return dfs(n);
    }
    vector<TreeNode *> dfs(int n)
    {
        if (n == 1)
            return {new TreeNode(0)};
        vector<TreeNode *> ans;
        for (int i = 1; i < n - 1; i += 2)
        {
            auto vecLeft = dfs(i);
            auto vecRight = dfs(n - 1 - i);
            for (auto &left : vecLeft)
            {
                for (auto &right : vecRight)
                {
                    ans.push_back(new TreeNode(0, left, right));
                }
            }
        }
        return ans;
    }
};
