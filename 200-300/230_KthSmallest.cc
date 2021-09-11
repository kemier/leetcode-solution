#define DSA_STACK_LIST
#include "binTree/BinTree.h"
#include "stack/stack.h"
#include <iostream>

using namespace std;

class Solution //迭代   时间复杂度：O(H+k)  H 指的是树的高度  当树是一个平衡树时：复杂度为O(logN+k)。当树是一个不平衡树时：复杂度为O(N+k)  空间复杂度：O(H+k)。当树是一个平衡树时：O(logN+k)。当树是一个非平衡树时：O(N+k)。

{
public:
    int kthSmallest(BinNode<int> *root, int k)
    {
        while (1)
        {
            while (root)
            {
                stck.insertAsLast(root);
                root = root->lc;
            }
            root = stck.pop();
            cout << root->data << endl;
            k -= 1;
            if (k == 0)
                return root->data;
            root = root->rc;
        }
    }

private:
    Stack<BinNode<int> *> stck;
};

void Print(int x)
{
    cout << x << " ";
}

int main()
{
    BinTree<int> *tree = new BinTree<int>();
    BinNodePosi<int> root = tree->insertAsRoot(5);
    BinNodePosi<int> L1_l = tree->insertAsLC(root, 3);
    BinNodePosi<int> L1_r = tree->insertAsRC(root, 6);
    BinNodePosi<int> L2_ll = tree->insertAsLC(L1_l, 2);
    BinNodePosi<int> L2_lr = tree->insertAsRC(L1_l, 4);
    BinNodePosi<int> L3_ll = tree->insertAsLC(L2_ll, 1);
    tree->travPre(Print);
    cout << endl;

    Solution solution;

    cout << "------------------------begin test------------------------" << endl;
    int ans = solution.kthSmallest(root, 3);
    cout << ans << endl;
    return 0;
}