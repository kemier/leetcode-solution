//
// Created by 曾宁 on 2023/1/8.
//

#include <bits/stdc++.h>
#include "../Tree.h"
using namespace std;

class Solution {
private TreeNode head;//翻转之后的新的根节点
public TreeNode upsideDownBinaryTree(TreeNode root) {
        if(root == null){
            return null;
        }
        dfs(root);
        return head;
    }
public TreeNode dfs(TreeNode node){
        if(node == null){
            return null;
        }
        if(node.left == null && node.right == null){
            if(head == null){//最左的节点就是新的根节点
                head = node;
            }
            return node;
        }
        TreeNode left = dfs(node.left);
        TreeNode right = dfs(node.right);
        if(left != null){
            left.left = right;//左孩子的左子树成为当前的右节点
            left.right = node;//左孩子的右子树为其父节点（也即node）
        }
        //清空当前父节点的左右子树
        node.left = null;
        node.right = null;
        return node;
    }
}

