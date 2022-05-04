#include <bits/stdc++.h>

using namesapce std;


class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



class Codec {
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        if (!root) return NULL;
        TreeNode* newroot = new TreeNode(root->val);
        TreeNode* cur = NULL;
        if (!root->children.empty())
        {
            newroot->left = encode(root->children[0]);
            cur = newroot->left;
        }
        for (int i = 1; i < root->children.size(); ++i)
        {
            cur->right = encode(root->children[i]);
            cur = cur->right;
        }
        return newroot;
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        if (!root) return NULL;
        Node* newroot = new Node(root->val);
        TreeNode* cur = NULL;
        if (root->left)
        {
            newroot->children.push_back(decode(root->left));
            cur = root->left;
        }
        while (cur && cur->right)
        {
            newroot->children.push_back(decode(cur->right));
            cur = cur->right;
        }
        return newroot;
    }
};
