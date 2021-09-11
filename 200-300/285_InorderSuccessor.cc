#define DSA_STACK_LIST
#include <stack>
#include "binTree/BinTree.h"
#include <iostream>

class Solution
{
public:
    BinNode<int> *inorderSuccessor(BinNode<int> *root, BinNode<int> *p)
    {
        stack<BinNode<int> *> s;
        iniSucSta(root, p, s);
        if (!s.empty() && s.top() == p)
        {
            getNextSuccessor(s);
        }
        return getNextSuccessor(s);
    }

private:
    void iniSucSta(BinNode<int> *root, BinNode<int> *p, stack<BinNode<int> *> &s)
    {
        while (root != NULL)
        {
            if (root->data > p->data)
            {
                s.push(root);
                root = root->lc;
            }
            else if (root->data < p->data)
            {
                root = root->rc;
            }
            else
            {
                s.push(root);
                break;
            }
        }
    }
    BinNode<int> *getNextSuccessor(stack<BinNode<int> *> &s)
    {
        if (s.empty())
        {
            return NULL;
        }
        BinNode<int> *cur = s.top();
        s.pop();
        BinNode<int> *temp = cur;
        cur = cur->rc;
        while (cur != NULL)
        {
            s.push(cur);
            cur = cur->lc;
        }
        return temp;
    }
};