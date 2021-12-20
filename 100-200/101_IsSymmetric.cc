#include <queue>
#include <vector>
#include <iostream>

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
class Solution // BFS
{
public:
    bool isSymmetric(TreeNode *root)
    {
        queue<TreeNode *> floor;
        vector<int> floor_val;
        floor.push(root);
        while (!floor.empty())
        {
            int qs = floor.size(); // qs可以区分每一层，每当qs置0时（队列内一层的节点已经访问完成）换层

            while (qs > 0)
            {
                TreeNode *p = floor.front();
                floor.pop();
                cout << qs;

                if (p->left)
                {
                    floor.push(p->left);
                    floor_val.push_back((p->left)->val);
                }
                else
                {
                    floor_val.push_back(-2147483648);
                }

                if (p->right)
                {
                    floor.push(p->right);
                    floor_val.push_back((p->right)->val);
                }
                else
                {
                    floor_val.push_back(-2147483648);
                }

                qs--;
            }
            if (!array(floor_val))
                return 0;
            floor_val.clear();
        }
        return 1;
    }

    bool array(const vector<int> &floor_val)
    {
        for (int i = 0, j = floor_val.size() - 1; i < j; i++, j--)
        {

            if (floor_val[i] != floor_val[j])
            {
                return 0;
            }
        }
        return 1;
    }
};
