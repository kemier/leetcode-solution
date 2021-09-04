#include <vector>
#include <unordered_map>
#include <strng>

using namespace std;

class Solution
{
public:
    struct node
    {
        int ch[26];
        int flag;
        node()
        {
            flag = -1;
            memset(ch, 0, sizeof(ch));
        }
    };

    vector<node> tree;

    void insert(string &s, int id)
    {
        int len = s.length(), add = 0;
        for (int i = 0; i < len; i++)
        {
            int x = s[i] - 'a';
            if (!tree[add].ch[x])
            {
                tree.emplace_back();
                tree[add].ch[x] = tree.size() - 1;
            }
            add = tree[add].ch[x];
        }
        tree[add].flag = id;
    }

    int findWord(string &s, int left, int right)
    {
        int add = 0;
        for (int i = right; i >= left; i--)
        {
            int x = s[i] - 'a';
            if (!tree[add].ch[x])
            {
                return -1;
            }
            add = tree[add].ch[x];
        }
        return tree[add].flag;
    }

    bool isPalindrome(string &s, int left, int right)
    {
        int len = right - left + 1;
        for (int i = 0; i < len / 2; i++)
        {
            if (s[left + i] != s[right - i])
            {
                return false;
            }
        }
        return true;
    }

    vector<vector<int>> palindromePairs(vector<string> &words)
    {
        tree.emplace_back(node());
        int n = words.size();
        for (int i = 0; i < n; i++)
        {
            insert(words[i], i);
        }
        vector<vector<int>> ret;
        for (int i = 0; i < n; i++)
        {
            int m = words[i].size();
            for (int j = 0; j <= m; j++)
            {
                if (isPalindrome(words[i], j, m - 1))
                {
                    int left_id = findWord(words[i], 0, j - 1);
                    if (left_id != -1 && left_id != i)
                    {
                        ret.push_back({i, left_id});
                    }
                }
                if (j && isPalindrome(words[i], 0, j - 1))
                {
                    int right_id = findWord(words[i], j, m - 1);
                    if (right_id != -1 && right_id != i)
                    {
                        ret.push_back({right_id, i});
                    }
                }
            }
        }
        return ret;
    }
};

class Solution2 //哈希表
{
private:
    vector<string> wordsRev;
    unordered_map<string_view, int> indices;

public:
    int findWord(const string_view &s, int left, int right)
    {
        auto iter = indices.find(s.substr(left, right - left + 1));
        return iter == indices.end() ? -1 : iter->second;
    }

    bool isPalindrome(const string_view &s, int left, int right)
    {
        int len = right - left + 1;
        for (int i = 0; i < len / 2; i++)
        {
            if (s[left + i] != s[right - i])
            {
                return false;
            }
        }
        return true;
    }

    vector<vector<int>> palindromePairs(vector<string> &words)
    {
        int n = words.size();
        for (const string &word : words)
        {
            wordsRev.push_back(word);
            reverse(wordsRev.back().begin(), wordsRev.back().end());
        }
        for (int i = 0; i < n; ++i)
        {
            indices.emplace(wordsRev[i], i);
        }

        vector<vector<int>> ret;
        for (int i = 0; i < n; i++)
        {
            int m = words[i].size();
            if (!m)
            {
                continue;
            }
            string_view wordView(words[i]);
            for (int j = 0; j <= m; j++)
            {
                if (isPalindrome(wordView, j, m - 1))
                {
                    int left_id = findWord(wordView, 0, j - 1);
                    if (left_id != -1 && left_id != i)
                    {
                        ret.push_back({i, left_id});
                    }
                }
                if (j && isPalindrome(wordView, 0, j - 1))
                {
                    int right_id = findWord(wordView, j, m - 1);
                    if (right_id != -1 && right_id != i)
                    {
                        ret.push_back({right_id, i});
                    }
                }
            }
        }
        return ret;
    }
};

struct Trie
{
    struct node
    {
        int ch[26];
        int flag;
        node()
        {
            flag = -1;
            memset(ch, 0, sizeof(ch));
        }
    };

    vector<node> tree;

    Trie() { tree.emplace_back(); }

    void insert(string &s, int id)
    {
        int len = s.length(), add = 0;
        for (int i = 0; i < len; i++)
        {
            int x = s[i] - 'a';
            if (!tree[add].ch[x])
            {
                tree.emplace_back();
                tree[add].ch[x] = tree.size() - 1;
            }
            add = tree[add].ch[x];
        }
        tree[add].flag = id;
    }

    vector<int> query(string &s)
    {
        int len = s.length(), add = 0;
        vector<int> ret(len + 1, -1);
        for (int i = 0; i < len; i++)
        {
            ret[i] = tree[add].flag;
            int x = s[i] - 'a';
            if (!tree[add].ch[x])
            {
                return ret;
            }
            add = tree[add].ch[x];
        }
        ret[len] = tree[add].flag;
        return ret;
    }
};

class Solution //字典树+马拉车
{
public:
    vector<pair<int, int>> manacher(string &s)
    {
        int n = s.length();
        string tmp = "#";
        tmp += s[0];
        for (int i = 1; i < n; i++)
        {
            tmp += '*';
            tmp += s[i];
        }
        tmp += '!';
        int m = n * 2;
        vector<int> len(m);
        vector<pair<int, int>> ret(n);
        int p = 0, maxn = -1;
        for (int i = 1; i < m; i++)
        {
            len[i] = maxn >= i ? min(len[2 * p - i], maxn - i) : 0;
            while (tmp[i - len[i] - 1] == tmp[i + len[i] + 1])
            {
                len[i]++;
            }
            if (i + len[i] > maxn)
            {
                p = i, maxn = i + len[i];
            }
            if (i - len[i] == 1)
            {
                ret[(i + len[i]) / 2].first = 1;
            }
            if (i + len[i] == m - 1)
            {
                ret[(i - len[i]) / 2].second = 1;
            }
        }
        return ret;
    }

    vector<vector<int>> palindromePairs(vector<string> &words)
    {
        Trie trie1, trie2;

        int n = words.size();
        for (int i = 0; i < n; i++)
        {
            trie1.insert(words[i], i);
            string tmp = words[i];
            reverse(tmp.begin(), tmp.end());
            trie2.insert(tmp, i);
        }

        vector<vector<int>> ret;
        for (int i = 0; i < n; i++)
        {
            const vector<pair<int, int>> &rec = manacher(words[i]);

            const vector<int> &id1 = trie2.query(words[i]);
            reverse(words[i].begin(), words[i].end());
            const vector<int> &id2 = trie1.query(words[i]);

            int m = words[i].size();

            int all_id = id1[m];
            if (all_id != -1 && all_id != i)
            {
                ret.push_back({i, all_id});
            }
            for (int j = 0; j < m; j++)
            {
                if (rec[j].first)
                {
                    int left_id = id2[m - j - 1];
                    if (left_id != -1 && left_id != i)
                    {
                        ret.push_back({left_id, i});
                    }
                }
                if (rec[j].second)
                {
                    int right_id = id1[j];
                    if (right_id != -1 && right_id != i)
                    {
                        ret.push_back({i, right_id});
                    }
                }
            }
        }
        return ret;
    }
};
