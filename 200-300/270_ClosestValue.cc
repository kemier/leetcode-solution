#include <vector>
#include <string>
#include <cstdlib>
#define DSA_STACK_LIST
#include "binTree/BinTree.h"
#include <iostream>

class Solution
{
public:
    int closestValue(BinNode<int> *root, double target)
    {
        int val, closest = root->data;
        while (root != nullptr)
        {
            val = root->data;
            closest = abs(val - target) < abs(closest - target) ? val : closest;
            root = target < root->data ? root->lc : root->rc;
        }
        return closest;
    }
};