#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution //递归
{
public:
    int getF(int x)
    {
        if (x == 1)
            return 0;
        if (x & 1)
            return getF(x * 3 + 1) + 1;
        else
            return getF(x / 2) + 1;
    }

    int getKth(int lo, int hi, int k)
    {
        vector<int> v;
        for (int i = lo; i <= hi; ++i)
            v.push_back(i);
        sort(v.begin(), v.end(), [&](int u, int v)
             {
            if (getF(u) != getF(v)) return getF(u) < getF(v);
            else return u < v; });
        return v[k - 1];
    }
};

class Solution2 //记忆化
{
public:
    unordered_map<int, int> f;

    int getF(int x)
    {
        if (f.find(x) != f.end())
            return f[x];
        if (x == 1)
            return f[x] = 0;
        if (x & 1)
            return f[x] = getF(x * 3 + 1) + 1;
        else
            return f[x] = getF(x / 2) + 1;
    }

    int getKth(int lo, int hi, int k)
    {
        vector<int> v;
        for (int i = lo; i <= hi; ++i)
            v.push_back(i);
        sort(v.begin(), v.end(), [&](int u, int v)
             {
            if (getF(u) != getF(v)) return getF(u) < getF(v);
            else return u < v; });
        return v[k - 1];
    }
};
