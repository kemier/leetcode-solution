#include <vector>
#include <algorithm>

using namespace std;

class Solution //并查集
{
public:
    vector<int> vals, p, w;

    int find(int x)
    {
        if (p[x] != x)
            p[x] = find(p[x]);
        return p[x];
    }
    int get(int x)
    {
        int l = 0, r = vals.size() - 1;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (vals[mid] >= x)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
    vector<int> minInterval(vector<vector<int>> &intervals, vector<int> &queries)
    {
        for (auto &t : intervals)
            vals.push_back(t[0]), vals.push_back(t[1]);
        for (auto t : queries)
            vals.push_back(t);
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int n = vals.size();
        p.resize(n + 1), w.resize(n + 1);
        for (int i = 0; i < n + 1; i++)
        {
            p[i] = i;
            w[i] = -1;
        }
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) -> bool
             { return a[1] - a[0] < b[1] - b[0]; });
        for (auto &t : intervals)
        {
            int l = get(t[0]), r = get(t[1]), len = t[1] - t[0] + 1;
            while (find(l) <= r)
            {
                l = p[l];
                w[l] = len;
                p[l] = l + 1;
            }
        }
        vector<int> res;
        for (auto t : queries)
            res.push_back(w[get(t)]);
        return res;
    }
};
