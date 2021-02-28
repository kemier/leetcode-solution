#define DSA_STACK_VECTOR
#include <unordered_map>
#include "binTree/BinTree.h"

using namespace std;

class Solution //时间复杂度：O(N)  N 是二叉树的节点数  空间复杂度：O(N) ，其中 N 是二叉树的节点数
               //递归调用的栈深度取决于二叉树的高度，二叉树最坏情况下为一条链，此时高度为 N，因此空间复杂度为 O(N)
{
public:
    BinNode<int> *ans;
    bool dfs(BinNode<int> *root, BinNode<int> *p, BinNode<int> *q)
    {
        if (root == nullptr)
            return false;
        bool lson = dfs(root->lc, p, q);
        bool rson = dfs(root->rc, p, q);
        if ((lson && rson) || ((root->data == p->data || root->data == q->data) && (lson || rson)))
        {
            ans = root;
        }
        return lson || rson || (root->data == p->data || root->data == q->data);
    }
    BinNode<int> *lowestCommonAncestor(BinNode<int> *root, BinNode<int> *p, BinNode<int> *q)
    {
        dfs(root, p, q);
        return ans;
    }
};

class Solution2 //时间复杂度：O(N)，其中 N 是二叉树的节点数
                //空间复杂度：O(N) ，其中 N 是二叉树的节点数。递归调用的栈深度取决于二叉树的高度，二叉树最坏情况下为一条链，此时高度为 N，因此空间复杂度为 O(N)，哈希表存储每个节点的父节点也需要 O(N) 的空间复杂度，因此最后总的空间复杂度为O(N)

{
public:
    unordered_map<int, BinNode<int> *> fa;
    unordered_map<int, bool> vis;
    void dfs(BinNode<int> *root)
    {
        if (root->lc != nullptr)
        {
            fa[root->lc->data] = root;
            dfs(root->lc);
        }
        if (root->rc != nullptr)
        {
            fa[root->rc->data] = root;
            dfs(root->rc);
        }
    }
    BinNode<int> *lowestCommonAncestor(BinNode<int> *root, BinNode<int> *p, BinNode<int> *q)
    {
        fa[root->data] = nullptr;
        dfs(root); //从根节点开始遍历整棵二叉树，用哈希表记录每个节点的父节点指针
        while (p != nullptr)
        {
            vis[p->data] = true;
            p = fa[p->data]; //去父节点
        }
        while (q != nullptr)
        {
            if (vis[q->data])
                return q;
            q = fa[q->data]; //去父节点
        }
        return nullptr;
    }
};

void Print(int x)
{
    cout << x << " ";
}

int main()
{
    BinTree<int> *tree = new BinTree<int>();
    BinNodePosi<int> root = tree->insertAsRoot(3);
    BinNodePosi<int> L1_l = tree->insertAsLC(root, 5);
    BinNodePosi<int> L1_r = tree->insertAsRC(root, 1);
    BinNodePosi<int> L2_ll = tree->insertAsLC(L1_l, 6);
    BinNodePosi<int> L2_lr = tree->insertAsRC(L1_l, 2);
    BinNodePosi<int> L2_rl = tree->insertAsLC(L1_r, 0);
    BinNodePosi<int> L2_rr = tree->insertAsRC(L1_r, 8);
    BinNodePosi<int> L3_lrl = tree->insertAsRC(L2_lr, 7);
    BinNodePosi<int> L3_lrr = tree->insertAsRC(L2_lr, 4);

    tree->travPre(Print);
    cout << endl;

    Solution2 solution;

    cout << "------------------------begin test------------------------" << endl;
    BinNodePosi<int> pos = solution.lowestCommonAncestor(root, L1_l, L3_lrr);
    cout << pos->data << endl;
    return 0;
}