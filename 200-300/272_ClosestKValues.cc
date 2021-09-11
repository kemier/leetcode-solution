#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <set>
#include <cstdlib>
#define DSA_STACK_LIST
#include "binTree/BinTree.h"
#include <iostream>

using namespace std;
class Solution
{

public:
    vector<int> closestKdataues(BinNode<int> *root, double target, int k)
    {
        priority_queue<double, vector<double>, greater<double>> maxHeap;
        set<int> set;

        rec(root, target, k, maxHeap, set);
        cout << set.size() << endl;
        vector<int> tmp(set.begin(), set.end());

        return tmp;
    }

private:
    void rec(BinNode<int> *root, double target, int k, priority_queue<double, vector<double>, greater<double>> &maxHeap, set<int> &set)
    {
        if (root == nullptr)
            return;
        double diff = abs(root->data - target);
        if (maxHeap.size() < k)
        {
            maxHeap.push(diff);
            set.insert(root->data);
        }
        else if (diff < maxHeap.top())
        {
            double x = maxHeap.top();
            if (!set.erase((int)(target + x)))
                set.erase((int)(target - x));
            maxHeap.pop();
            maxHeap.push(diff);
            set.insert(root->data);
        }
        else
        {
            if (root->data > target)
                rec(root->lc, target, k, maxHeap, set);
            else
                rec(root->rc, target, k, maxHeap, set);
            return;
        }
        rec(root->lc, target, k, maxHeap, set);
        rec(root->rc, target, k, maxHeap, set);
    }
};
void Print(int x)
{
    cout << x << " ";
}

int main()
{
    BinTree<int> *tree = new BinTree<int>();
    BinNodePosi<int> root = tree->insertAsRoot(4);
    BinNodePosi<int> L1_l = tree->insertAsLC(root, 2);
    BinNodePosi<int> L1_r = tree->insertAsRC(root, 5);
    BinNodePosi<int> L2_ll = tree->insertAsLC(L1_l, 1);
    BinNodePosi<int> L2_lr = tree->insertAsRC(L1_l, 3);

    tree->travPre(Print);
    cout << endl;

    Solution solution;

    cout << "------------------------begin test------------------------" << endl;
    auto ans = solution.closestKdataues(root, 3.714286, 2);
    vector<int>::iterator iter;
    for (iter = ans.begin(); iter != ans.end(); ++iter)
    {
        cout << *iter << endl;
    }
    return 0;
}

struct cmp
{
    bool operator()(vector<double> &a, vector<double> &b)
    {
        return a[0] < b[0]; //差值大的在上
    }
};
class Solution2
{
public:
    vector<int> closestKdataues(BinNode<int> *root, double target, int k)
    {
        stack<BinNode<int> *> s;
        priority_queue<vector<double>, vector<vector<double>>, cmp> q;
        BinNode<int> *cur;
        while (root || !s.empty())
        {
            while (root)
            {
                s.push(root);
                root = root->lc;
            }
            cur = s.top();
            s.pop();
            root = cur->rc;
            if (q.size() < k)
                q.push({fabs(cur->data - target), double(cur->data)});
            else if (q.size() == k && q.top()[0] > fabs(cur->data - target))
            { //有更小的差值
                q.pop();
                q.push({fabs(cur->data - target), double(cur->data)});
            }
            if (q.size() == k && cur->data - target >= q.top()[0])
                break;
        }
        vector<int> ans(k);
        int i = 0;
        while (!q.empty())
        {
            ans[i++] = q.top()[1];
            q.pop();
        }
        return ans;
    }
};
