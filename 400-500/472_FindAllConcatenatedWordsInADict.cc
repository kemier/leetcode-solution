#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Solution //字典树+记忆化
{
    static const int N = 53510; //使用静态数组来做tire树，减少动态数组扩大空间的时间
    int h[N][26]{0}, cnt[N]{0}, index = 0;
    unordered_map<string, bool> mp; //记忆化，存储所有可以的字符串，让后续搜索少点
public:
    void insert(string &s)
    { // tire树构建
        int p = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            int u = s[i] - 'a';
            if (!h[p][u])
                h[p][u] = ++index;
            p = h[p][u];
        }
        ++cnt[p];
    }
    bool search(string &s, int &k)
    { // tire树搜索
        int p = 0;
        if (s == "" && k <= 1)
            return false;
        if (mp.count(s) && !mp[s])
            return false;
        if (k > 0 && mp.count(s) && mp[s])
        {
            return true;
        }
        // cout<<s<<' '<<k<<endl;
        for (int i = 0; i < s.size(); ++i)
        {
            int u = s[i] - 'a';
            if (!h[p][u])
            {
                mp[s] = false; //没有匹配到就退出
                return false;
            }
            if (h[p][u] && cnt[h[p][u]])
            {
                ++k;
                string w = s.substr(i + 1);
                if (search(w, k))
                    return true; //对这个单词进行切割
                --k;
            }
            p = h[p][u];
        }
        if (k > 0 && cnt[p])
            return true;
        return false;
    }

    vector<string> findAllConcatenatedWordsInADict(vector<string> &words)
    {
        vector<string> ans;
        for (string &q : words)
        { //构建tire树
            insert(q);
            mp[q] = true; //当出现这个单词时候说明这个词在words里面
        }
        for (string &q : words)
        {
            int k = 0;
            if (search(q, k))
                ans.push_back(q);
        }
        return ans;
    }
};
