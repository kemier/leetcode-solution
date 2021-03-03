#include <vector>
#include <string>
#define DSA_STACK_LIST
#include "binTree/BinTree.h"
#include <iostream>

class Solution //DFS
{
public:
    void construct_paths(BinNode<int> *root, string path, vector<string> &paths)
    {
        if (root != nullptr)
        {
            path += to_string(root->data);
            if (root->lc == nullptr && root->rc == nullptr)
            {                          // 当前节点是叶子节点
                paths.push_back(path); // 把路径加入到答案中
            }
            else
            {
                path += "->"; // 当前节点不是叶子节点，继续递归遍历
                construct_paths(root->lc, path, paths);
                construct_paths(root->rc, path, paths);
            }
        }
    }

    vector<string> binaryTreePaths(BinNode<int> *root)
    {
        vector<string> paths;
        construct_paths(root, "", paths);
        return paths;
    }
};

void Print(int x)
{
    cout << x << " ";
}

int main()
{
    BinTree<int> *tree = new BinTree<int>();
    BinNodePosi<int> root = tree->insertAsRoot(1);
    BinNodePosi<int> L1_l = tree->insertAsLC(root, 2);
    BinNodePosi<int> L1_r = tree->insertAsRC(root, 3);
    BinNodePosi<int> L2_lr = tree->insertAsRC(L1_l, 5);
    tree->travPre(Print);
    cout << endl;

    Solution solution;

    cout << "------------------------begin test------------------------" << endl;
    auto ans = solution.binaryTreePaths(root);
    vector<string>::iterator iter;
    for (iter = ans.begin(); iter != ans.end(); ++iter)
    {
        cout << *iter << endl;
    }
    return 0;
}