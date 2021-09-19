#include <queue>
#include <vector>
#include <map>

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
    vector<vector<int>> verticalOrder(TreeNode *root)
    {
        if (!root)
            return result;
        queue<pair<TreeNode *, int>> que;
        que.push(make_pair(root, 1));
        while (!que.empty())
        {
            auto node = que.front();
            que.pop();
            hash[node.second].push_back(node.first->val);
            auto left = node.first->left, right = node.first->right;
            if (left)
                que.push(make_pair(left, node.second - 1));
            if (right)
                que.push(make_pair(right, node.second + 1));
        }
        for (auto val : hash)
            result.push_back(val.second);
        return result;
    }

private:
    map<int, vector<int>> hash;
    vector<vector<int>> result;
};