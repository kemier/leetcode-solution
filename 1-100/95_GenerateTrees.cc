#define DSA_STACK_VECTOR
#include "binTree/BinNode.h"
#include <vector>
#include <iostream>
using namespace std;

class Solution //����
{
public:
    vector<BinNode<int> *> generateTrees(int start, int end)
    {
        if (start > end)
        {
            return {nullptr};
        }
        vector<BinNode<int> *> allTrees;
        // ö�ٿ��и��ڵ�
        for (int i = start; i <= end; i++)
        {
            // ������п��е�����������
            vector<BinNode<int> *> leftTrees = generateTrees(start, i - 1);

            // ������п��е�����������
            vector<BinNode<int> *> rightTrees = generateTrees(i + 1, end);

            // ��������������ѡ��һ������������������������ѡ��һ����������ƴ�ӵ����ڵ���
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