#define DSA_STACK_VECTOR
#include <vector>
#include "binTree/BinTree.h"
#include <iostream>

using namespace std;

//利用二叉搜索树的特点:任一节点r的左（右）子树中，所有节点（若存在）均小于（大于）r

class Solution //两次遍历  时间复杂度：O(n)  空间复杂度：O(n)
{
public:
    vector<BinNode<int> *> getPath(BinNode<int> *root, BinNode<int> *target)
    {
        vector<BinNode<int> *> path;
        BinNode<int> *node = root;
        while (node != target)
        {
            path.push_back(node);
            if (target->data < node->data)
            {
                node = node->lc;
            }
            else
            {
                node = node->rc;
            }
        }
        path.push_back(node);
        return path;
    }

    BinNode<int> *lowestCommonAncestor(BinNode<int> *root, BinNode<int> *p, BinNode<int> *q)
    {
        vector<BinNode<int> *> path_p = getPath(root, p);
        vector<BinNode<int> *> path_q = getPath(root, q);
        BinNode<int> *ancestor;
        for (int i = 0; i < path_p.size() && i < path_q.size(); ++i)
        {
            if (path_p[i] == path_q[i])
            {
                ancestor = path_p[i];
            }
            else
            {
                break;
            }
        }
        return ancestor;
    }
};

class Solution2 //一次遍历  时间复杂度：O(n)  空间复杂度：O(1)
{
public:
    BinNode<int> *lowestCommonAncestor(BinNode<int> *root, BinNode<int> *p, BinNode<int> *q)
    {
        BinNode<int> *ancestor = root;
        while (true)
        {
            if (p->data < ancestor->data && q->data < ancestor->data)
            {
                ancestor = ancestor->lc;
            }
            else if (p->data > ancestor->data && q->data > ancestor->data)
            {
                ancestor = ancestor->rc;
            }
            else
            {
                break;
            }
        }
        return ancestor;
    }
};

void Print(int x)
{
    cout << x << " ";
}

int main()
{
    BinTree<int> *tree = new BinTree<int>();
    BinNodePosi<int> root = tree->insertAsRoot(6);
    BinNodePosi<int> L1_l = tree->insertAsLC(root, 2);
    BinNodePosi<int> L1_r = tree->insertAsRC(root, 8);
    BinNodePosi<int> L2_ll = tree->insertAsLC(L1_l, 0);
    BinNodePosi<int> L2_lr = tree->insertAsRC(L1_l, 4);
    BinNodePosi<int> L2_rl = tree->insertAsLC(L1_r, 7);
    BinNodePosi<int> L2_rr = tree->insertAsRC(L1_r, 9);
    BinNodePosi<int> L3_lrl = tree->insertAsRC(L2_lr, 3);
    BinNodePosi<int> L3_lrr = tree->insertAsRC(L2_lr, 5);

    tree->travPre(Print);
    cout << endl;

    Solution2 solution;

    cout << "------------------------begin test------------------------" << endl;
    BinNodePosi<int> pos = solution.lowestCommonAncestor(root, L2_lr, L2_rl);
    cout << pos->data << endl;
    return 0;
}