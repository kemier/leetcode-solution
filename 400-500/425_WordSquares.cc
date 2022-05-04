#include <bits/stdc++.h>

using namespace std;


class trie
{
public:
    bool isEnd = false;
    trie* next[26] = { NULL };
    vector<int> wd;//经过该节点的单词下标
    void insert(string& s, int idx)
    {
        trie* cur = this;
        for (int i = 0; i < s.size(); ++i)
        {
            if (!cur->next[s[i] - 'a'])
                cur->next[s[i] - 'a'] = new trie();
            cur = cur->next[s[i] - 'a'];
            cur->wd.push_back(idx);
        }
        cur->isEnd = true;
    }
};
class Solution {
    vector<vector<string>> ans;
    int n;
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        trie* t = new trie();
        for (int i = 0; i < words.size(); ++i)
            t->insert(words[i], i);
        n = words[0].size();
        vector<string> mat;
        for (auto& w : words)
        {
            mat.push_back(w);//以每个单词为1第一行，开始查找
            dfs(words, t, mat, 1);
            mat.pop_back();
        }
        return ans;
    }
    void dfs(vector<string>& words, trie* t, vector<string>& mat, int len)
    {
        if (len == n)
        {
            ans.push_back(mat);
            return;
        }
        string nextprefix;//获取下一行的前缀
        for (int i = 0; i < len; ++i)
            nextprefix += mat[i][len];
        trie* cur = t;
        for (int i = 0; i < nextprefix.size(); ++i)
        {	//在trie中检查前缀是否存在
            if (!cur->next[nextprefix[i] - 'a']) return;
            cur = cur->next[nextprefix[i] - 'a'];
        }
        for (int wd_idx : cur->wd)
        {	//存在前缀，在当前节点的单词中加入下一个单词
            mat.push_back(words[wd_idx]);
            dfs(words, t, mat, len + 1);
            mat.pop_back();
        }
    }
};

