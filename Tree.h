//
// Created by 曾宁 on 2023/1/8.
//

#ifndef LEETCODE_SOLUTION_TREE_H
#define LEETCODE_SOLUTION_TREE_H


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#endif //LEETCODE_SOLUTION_TREE_H
