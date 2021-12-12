#define DSA_STACK_VECTOR
#include "binTree/BinNode.h"
#include <vector>
#include <iostream>
using namespace std;

class Solution //回溯
{
public:
    vector<BinNode<int> *> generateTrees(int start, int end)
    {
        if (start > end)
        {
            return {nullptr};
        }
        vector<BinNode<int> *> allTrees;
        // 枚举可行根节点
        for (int i = start; i <= end; i++)
        {
            // 获得所有可行的左子树集合
            vector<BinNode<int> *> leftTrees = generateTrees(start, i - 1);

            // 获得所有可行的右子树集合
            vector<BinNode<int> *> rightTrees = generateTrees(i + 1, end);

            // 从左子树集合中选出一棵左子树，从右子树集合中选出一棵右子树，拼接到根节点上
            for (auto &left : leftTrees)
            {
                for (auto &right : rightTrees)
                {
                    BinNode<int> *currTree = new BinNode<int>(i);
                    currTree->lc = left;
                    currTree->rc = right;
                    allTrees.emplace_back(currTree);
                }
            }
        }
        return allTrees;
    }

    vector<BinNode<int> *> generateTrees(int n)
    {
        if (!n)
        {
            return {};
        }
        return generateTrees(1, n);
    }
};

void print(int num)
{
    cout << num << endl;
}

int main()
{
    Solution solution;
    vector<BinNode<int> *> ans = solution.generateTrees(3);
    for (auto it = ans.begin(); it != ans.end(); it++)
    {
        (*it)->travPre(print);
    }
    return 0;
}