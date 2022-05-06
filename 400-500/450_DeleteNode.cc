#include <bits/stdc++.h>

using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution // recursion
{
public:
    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (!root)
            return nullptr; // key not found in bst

        if (key < root->val)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->val)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            // case 1:  if the root itself is a leaf node
            if (!root->left && !root->right)
            {
                return nullptr;
            }

            // case 2:  if the root only has right child
            if (!root->left && root->right)
            {
                return root->right;
            }

            // case 3:  if the root only has left child
            if (root->left && !root->right)
            {
                return root->left;
            }

            // case 4:  if the root has both left and right child
            if (root->left && root->right)
            {
                //  find the successor from right subtree:
                //  1. the successor must be the samllest element in subtree
                //  2. the successor could be either the right or left child of its ancestor
                auto ancestor = root;
                auto successor = root->right;
                while (successor->left)
                {
                    ancestor = successor;
                    successor = successor->left;
                }
                root->val = successor->val;
                if (successor == ancestor->right)
                {
                    ancestor->right = deleteNode(successor, successor->val);
                }
                else
                {
                    ancestor->left = deleteNode(successor, successor->val);
                }
            }
        }
        return root;
    }
};