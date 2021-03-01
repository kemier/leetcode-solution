#define DSA_STACK_LIST
#include "binTree/BinTree.h"
#include <iostream>

class Solution
{
public:
    bool DFS(BinNode<int> *root, int pre, int &ans)
    {
        if (!root)
            return true;
        bool flag1 = DFS(root->lc, root->data, ans);
        bool flag2 = DFS(root->rc, root->data, ans);
        if (flag1 && flag2)
            ans++;
        return (root->data == pre) && flag1 && flag2;
    }

    int countUnidataSubtrees(BinNode<int> *root)
    {
        if (!root)
            return 0;
        int ans = 0;
        DFS(root, root->data, ans);
        return ans;
    }
};