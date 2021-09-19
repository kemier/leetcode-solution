#include <vector>
#include <climits>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    vector<int> DFS(TreeNode *root, int &ans)
    {
        if (!root)
            return vector<int>{0, INT_MAX, INT_MIN};
        auto left = DFS(root->left, ans), right = DFS(root->right, ans);
        if (root->val > left[2] && root->val < right[1])
        {
            int Min = min(root->val, left[1]), Max = max(root->val, right[2]);
            ans = max(ans, left[0] + right[0] + 1);
            return vector<int>{left[0] + right[0] + 1, Min, Max};
        }
        return vector<int>{0, INT_MIN, INT_MAX};
    }

    int largestBSTSubtree(TreeNode *root)
    {
        int ans = 0;
        DFS(root, ans);
        return ans;
    }
};