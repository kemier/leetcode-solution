

class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *parent;
};


//source: https://www.leetcode.cn/problems/inorder-successor-in-bst/
//二叉搜索树的中序后继节点
//Time complexity: O(h)
//Space complexity: O(1)


class Solution
{
public:
    /*
     * @param root: The root of the BST.
     * @param p: You need find the successor node of p.
     * @return: Successor of p.
     */
    Node *inorderSuccessor(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->right == nullptr)
        {
            Node *curr = node->parent, *child = node;
            while (curr != nullptr && curr->left != child)
            {
                child = curr;
                curr = curr->parent;
            }
            return curr;
        }
        else
        {
            Node *curr = node->right;
            while (curr != nullptr && curr->left != nullptr)
            {
                curr = curr->left;
            }
            return curr;
        }
    }
};
