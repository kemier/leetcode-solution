#include <bits/stdc++.h>

using namespace std;

class Solution // DFS
{
public:
    int rootSum(TreeNode *root, int targetSum)
    {
        if (!root)
        {
            return 0;
        }

        int ret = 0;
        if (root->val == targetSum)
        {
            ret++;
        }

        ret += rootSum(root->left, targetSum - root->val);
        ret += rootSum(root->right, targetSum - root->val);
        return ret;
    }

    int pathSum(TreeNode *root, int targetSum)
    {
        if (!root)
        {
            return 0;
        }

        int ret = rootSum(root, targetSum);
        ret += pathSum(root->left, targetSum);
        ret += pathSum(root->right, targetSum);
        return ret;
    }
};

class Solution2
{
public:
    unordered_map<long long, int> prefix;

    int dfs(TreeNode *root, long long curr, int targetSum)
    {
        if (!root)
        {
            return 0;
        }

        int ret = 0;
        curr += root->val;
        if (prefix.count(curr - targetSum))
        {
            ret = prefix[curr - targetSum];
        }

        prefix[curr]++;
        ret += dfs(root->left, curr, targetSum);
        ret += dfs(root->right, curr, targetSum);
        prefix[curr]--;

        return ret;
    }

    int pathSum(TreeNode *root, int targetSum)
    {
        prefix[0] = 1;
        return dfs(root, 0, targetSum);
    }
};
