#define DSA_STACK_LIST
#include <iostream>
#include <algorithm>
#include "binTree/BinTree.h"

using namespace std;

class Solution
{
public:
    int max = 1;

    int longestConsecutive(BinNode<int> *root)
    {

        if (root == nullptr)
            return 0;
        rec(root, 1);
        return max;
    }

private:
    void rec(BinNode<int> *n, int c)
    {
        if (n->lc != nullptr)
        {
            if (n->data + 1 == n->lc->data)
            {
                rec(n->lc, c + 1);
                max = max(max, c + 1);
            }
            else
                rec(n->lc, 1);
        }

        if (n->rc != nullptr)
        {
            if (n->data + 1 == n->rc->data)
            {
                rec(n->rc, c + 1);
                max = max(max, c + 1);
            }
            else
                rec(n->rc, 1);
        }
    }
};