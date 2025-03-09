//source: https://leetcode.com/problems/find-bottom-left-tree-value/
//dfs
//Time complexity: O(n)
//Space complexity: O(n)

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
    void dfs(TreeNode *root, int height, int &curVal, int &curHeight)
    {
        if (root == nullptr)
        {
            return;
        }
        height++;
        dfs(root->left, height, curVal, curHeight);
        dfs(root->right, height, curVal, curHeight);
        if (height > curHeight)
        {
            curHeight = height;
            curVal = root->val;
        }
    }

    int findBottomLeftValue(TreeNode *root)
    {
        int curVal, curHeight = 0;
        dfs(root, 0, curVal, curHeight);
        return curVal;
    }
};
