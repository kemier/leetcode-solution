#include <bits/stdc++.h>

using namespace std;

struct Equalfunc_t
{
    bool operator()(vector<int> const &a, vector<int> const &b) const
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] != b[i])
                return 0;
        }
        return 1;
    }
};

template <typename T>
T xorshift(const T &n, int i)
{
    return n ^ (n >> i);
}

struct VectorHasher
{
    // int operator()(const vector<int> &V) const
    // {
    //     int hash = V.size();
    //     for (auto &i : V)
    //     {
    //         hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    //     }
    //     return hash;
    // }
    // std::size_t operator()(std::vector<int> const &vec) const
    // {
    //     std::size_t seed = vec.size();
    //     for (auto x : vec)
    //     {
    //         x = ((x >> 16) ^ x) * 0x45d9f3b;
    //         x = ((x >> 16) ^ x) * 0x45d9f3b;
    //         x = (x >> 16) ^ x;
    //         seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    //     }
    //     return seed;
    // }
    int operator()(const vector<int> &V) const
    {
        int hash = 0;
        for (int i = 0; i < V.size(); i++)
        {
            hash ^= V[i];
        }
        return hash;
    }
};

class Solution // Timeout
{
public:
    vector<int> findRightInterval(vector<vector<int>> intervals)
    {
        vector<int> res(intervals.size(), -1);
        unordered_map<vector<int>, int, VectorHasher, Equalfunc_t> hash;
        for (int i = 0; i < intervals.size(); i++)
        {
            hash.insert(make_pair(intervals[i], i));
        }
        sort(intervals.begin(), intervals.end(), [](const auto &u, const auto &v)
             { return u[1] < v[1]; });
        for (int i = 0; i < intervals.size(); i++)
        {
            int min = INT_MAX;
            int minindex = -1;
            for (int j = i + 1; j < intervals.size(); j++)
            {
                if (intervals[j][0] >= intervals[i][1] && intervals[j][0] < min)
                {
                    min = intervals[j][0];
                    minindex = hash[intervals[j]];
                }
            }
            res[hash[intervals[i]]] = minindex;
        }
        return res;
    }
};

class Solution2 // Binary Search
{
public:
    typedef struct St
    {
        int id;
        int l;
        int r;
        friend bool operator<(const St &a, const St &b)
        {
            if (a.l != b.l)
            {
                return a.l < b.l;
            }
            return a.r < b.r;
        }
    } St;

    vector<int> findRightInterval(vector<vector<int>> &intervals)
    {
        int len = (int)intervals.size();

        vector<St> v;
        for (int i = 0; i < len; i++)
        {
            v.push_back(St{i, intervals[i][0], intervals[i][1]});
        }
        sort(v.begin(), v.end());

        vector<int> res;
        for (int i = 0, x, y, idx; i < len; i++)
        {
            x = intervals[i][0], y = intervals[i][1];

            idx = lower_bound(v.begin(), v.end(), St{0, y, y}) - v.begin();

            if (idx == len)
            {
                res.push_back(-1);
                continue;
            }
            if (v[idx].l >= y)
            {
                res.push_back(v[idx].id);
            }
            else
            {
                res.push_back(-1);
            }
        }
        return res;
    }
};
