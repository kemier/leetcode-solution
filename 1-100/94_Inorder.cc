#include "binTree/BinNode.h"
#include <vector>

#define DSA_STACK_VECTOR

using namespace std;

class Solution //递归
{
public:
    void inorder(BinNode<int> *root, vector<int> &res)
    {
        if (!root)
        {
            return;
        }
        inorder(root->lc, res);
        res.push_back(root->data);
        inorder(root->rc, res);
    }
    vector<int> inorderTraversal(BinNode<int> *root)
    {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
