#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;


//source: https://leetcode-cn.com/problems/find-largest-value-in-each-tree-row/
//bfs
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
    vector<int> largestValues(TreeNode *root)
    {
        if (!root)
        {
            return {};
        }
        vector<int> res;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int len = q.size();
            int maxVal = INT_MIN;
            while (len > 0)
            {
                len--;
                auto t = q.front();
                q.pop();
                maxVal = max(maxVal, t->val);
                if (t->left)
                {
                    q.push(t->left);
                }
                if (t->right)
                {
                    q.push(t->right);
                }
            }
            res.push_back(maxVal);
        }
        return res;
    }
};
