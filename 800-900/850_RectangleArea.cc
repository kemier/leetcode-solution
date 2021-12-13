#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

class SegmentTreeNode
{
public:
    vector<int> x;
    long x_width_sum;
    int cnt; //[l, r)被重复了几次
    int l, r;
    SegmentTreeNode *left, *right;

    SegmentTreeNode()
    {
    }

    SegmentTreeNode(int _l, int _r, vector<int> &_x)
    {
        this->x = _x;
        this->x_width_sum = 0;
        this->cnt = 0;
        this->l = _l, this->r = _r;
        this->left = NULL, this->right = NULL;
    }

    int mid() //计算中间值
    {
        return (this->l + this->r) / 2;
    }

    SegmentTreeNode *_left() //获得左孩子
    {
        if (this->left == NULL)
            this->left = new SegmentTreeNode(this->l, mid(), x);
        return this->left;
    }
    SegmentTreeNode *_right() //获得右孩子
    {
        if (this->right == NULL)
            this->right = new SegmentTreeNode(mid(), this->r, x);
        return this->right;
    }

    void update(int ul, int ur, int diff)
    {
        if (ul >= ur)
            return;
        if (this->l == ul && this->r == ur)
            this->cnt += diff;
        else
        {
            _left()->update(ul, min(mid(), ur), diff);
            _right()->update(max(mid(), ul), ur, diff);
        }
        if (this->cnt > 0)
            this->x_width_sum = x[r] - x[l];
        else
            this->x_width_sum = _left()->x_width_sum + _right()->x_width_sum;
    }

    long query()
    {
        return this->x_width_sum;
    }
};

class Solution //从下往上，线性扫描+离散化+线段树
{
public:
    int rectangleArea(vector<vector<int>> &rectangles)
    {
        int MOD = 1e9 + 7;
        int OPEN = 1;
        int CLOSE = -1;
        vector<tuple<int, int, int, int>> rec;
        set<int> x_set;
        for (auto v : rectangles)
        {
            int x1 = v[0], y1 = v[1], x2 = v[2], y2 = v[3];
            rec.push_back(tuple<int, int, int, int>{y1, OPEN, x1, x2});
            rec.push_back(tuple<int, int, int, int>{y2, CLOSE, x1, x2});
            x_set.insert(x1);
            x_set.insert(x2);
        }

        sort(rec.begin(), rec.end());
        vector<int> x(x_set.begin(), x_set.end()); //去重
        int n = x.size();
        unordered_map<int, int> x_idx; //离散化
        for (int i = 0; i < n; i++)
            x_idx[x[i]] = i;

        long res = 0;
        SegmentTreeNode *activate = new SegmentTreeNode(0, n - 1, x);
        int cur_y = get<0>(rec[0]);
        for (auto [y, state, x1, x2] : rec)
        {
            res += activate->query() * (y - cur_y);
            res %= MOD;
            activate->update(x_idx[x1], x_idx[x2], state);
            cur_y = y;
        }

        return res;
    }
};
