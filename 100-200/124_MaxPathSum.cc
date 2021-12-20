#include <climits>

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
private:
    int maxSum = INT_MIN;

public:
    int maxGain(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        // 递归计算左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
        int priceNewpath = node->val + leftGain + rightGain;

        // 更新答案
        maxSum = max(maxSum, priceNewpath);

        // 返回节点的最大贡献值
        return node->val + max(leftGain, rightGain);
    }

    int maxPathSum(TreeNode *root)
    {
        maxGain(root);
        return maxSum;
    }
};

class Solution2 // DFS
{
public:
    int maxPathSum(TreeNode *root)
    {
        //因为节点值最小为-1000，即使二叉树中所有节点都是-1000
        //最大路径和就是其中一个节点，即-1000
        int maxSum = -1000;
        dfs(root, maxSum);

        return maxSum;
    }

    int dfs(TreeNode *root, int &maxSum)
    {
        if (root == nullptr)
            return 0;

        //若当前子树和小于0，则不选当前子树所在的路径，于是取0
        int left = max(0, dfs(root->left, maxSum));
        int right = max(0, dfs(root->right, maxSum));

        //路径同时经过当前节点左右子树的情况
        maxSum = max(maxSum, root->val + left + right);

        //函数的返回值是经过当前节点root并前往其左子树或右子树的路径的节点值之和的最大值
        return root->val + max(left, right);
    }
};
