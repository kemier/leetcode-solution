#define DSA_STACK_LIST
#include "binTree/BinTree.h"
#include <iostream>

class Solution
{
public:
    BinNode<int> *invertTree(BinNode<int> *root)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        BinNode<int> *left = invertTree(root->lc);
        BinNode<int> *right = invertTree(root->rc);
        root->lc = right;
        root->rc = left;
        return root;
    }
};

void Print(int x)
{
    cout << x << " ";
}

int main()
{
    BinTree<int> *tree = new BinTree<int>();
    BinNodePosi<int> root = tree->insertAsRoot(10);
    BinNodePosi<int> L1_l = tree->insertAsLC(root, 2);
    BinNodePosi<int> L1_r = tree->insertAsRC(root, 7);
    BinNodePosi<int> L2_ll = tree->insertAsLC(L1_l, 1);
    BinNodePosi<int> L2_lr = tree->insertAsRC(L1_l, 3);
    BinNodePosi<int> L2_rl = tree->insertAsLC(L1_r, 6);
    BinNodePosi<int> L2_rr = tree->insertAsRC(L1_r, 9);
    tree->travPre(Print);
    cout << endl;

    Solution solution;

    cout << "------------------------begin test------------------------" << endl;
    solution.invertTree(root);
    tree->travPre(Print);
    cout << endl;
    return 0;
}