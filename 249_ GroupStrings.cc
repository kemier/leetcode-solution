#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<string>> groupStrings(vector<string> &strings)
    {
        unordered_map<string, vector<string>> m;
        string key;
        for (string &s : strings)
        {
            key = s;
            int dis = s[0] - 'a';
            for (int i = 0; i < key.size(); ++i)
                key[i] = (key[i] - dis + 26) % 26;
            m[key].push_back(s);
        }
        vector<vector<string>> ans(m.size());
        int i = 0;
        for (auto it = m.begin(); it != m.end(); ++it)
            ans[i++] = it->second;
        return ans;
    }
};

class Solution2
{
public:
    vector<vector<string>> groupStrings(vector<string> &strings)
    {
        map<vector<int>, vector<string>> m; //存储当前结果的特征值，集其包含的字符串
        vector<vector<string>> res;         //最后的结果集
        for (auto s : strings)
        {
            vector<int> v;
            for (int j = 0; j < s.length() - 1; ++j)
            {
                int x = s[j] - s[j + 1];
                if (x < 0)
                    x += 26; //这里处理越界的情况,根据题目要求，z和a相邻，特征值只相差1，但是直接用a-z的话会为-25，我直接加上26变成1
                v.push_back(x);
            }
            if (s.length() == 1) //比如a,b,c这种单个的字符，我用-1来代表它们的特征值。
            {
                v.push_back(-1);
            }
            m[v].push_back(s); //把当前字符串存入对应的特征值的数组中
        }
        for (auto i : m)
        {
            res.push_back(i.second); //最后取出map中的所有结果集
        }
        return res;
    }
};