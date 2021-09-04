#include <unordered_map>

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

class Solution
{
public:
    unordered_map<TreeNode *, int> f, g;

    void dfs(TreeNode *node)
    {
        if (!node)
        {
            return;
        }
        dfs(node->left);
        dfs(node->right);
        f[node] = node->val + g[node->left] + g[node->right];
        g[node] = max(f[node->left], g[node->left]) + max(f[node->right], g[node->right]);
    }

    int rob(TreeNode *root)
    {
        dfs(root);
        return max(f[root], g[root]);
    }
};

struct SubtreeStatus
{
    int selected;
    int notSelected;
};

class Solution2 //优化
{
public:
    SubtreeStatus dfs(TreeNode *node)
    {
        if (!node)
        {
            return {0, 0};
        }
        auto l = dfs(node->left);
        auto r = dfs(node->right);
        int selected = node->val + l.notSelected + r.notSelected;
        int notSelected = max(l.selected, l.notSelected) + max(r.selected, r.notSelected);
        return {selected, notSelected};
    }

    int rob(TreeNode *root)
    {
        auto rootStatus = dfs(root);
        return max(rootStatus.selected, rootStatus.notSelected);
    }
};
