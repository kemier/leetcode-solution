#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

using ull = uint64_t;
ull b = 97755331, mask = 23367;
#define MAXSIZE 20001
int del[MAXSIZE] = {0};
class tree;
unordered_map<ull, vector<tree *>> hm;

ull to_hash(string &str)
{
    ull ret = 0;
    for (char c : str)
        ret = ret * b + c;
    return ret;
}

class tree
{
public:
    unordered_map<ull, tree *> next;
    ull hash, ustr;
    int index;
    tree() : hash(0), index(-1) {}

    void add(vector<string>::iterator s, vector<string>::iterator e, int i, ull us)
    {
        if (s == e)
        {
            index = i;
            ustr = us * (us ^ mask);
            return;
        }
        ull h = to_hash(*s);
        if (next.count(h) == 0)
            next[h] = new tree;
        next[h]->add(s + 1, e, i, us);
    }

    void upload()
    {
        for (auto &[lstr, p] : next)
        {
            p->upload();
            hash += p->hash * b + p->ustr ^ p->hash;
        }
        if (index == -1 || hash == 0)
            return;
        hm[hash].push_back(this);
        vector<tree *> &temp = hm[hash];
        if (temp.size() == 2)
        {
            delte(temp[0]);
            delte(temp[1]);
        }
        else if (temp.size() > 2)
        {
            delte(temp.back());
        }
    }

    static void delte(tree *root)
    {
        for (auto &[lstr, p] : root->next)
            delte(p);
        if (root->index >= 0)
            del[root->index] = 1;
    }
};

class Solution //排序 + 字符串哈希 + 字典树 + 哈希表
{
public:
    tree root;
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>> &paths)
    {
        /*std::default_random_engine random(time(NULL));
        std::uniform_int_distribution<ull> dis1(100000000, 1000000000);
        b = dis1(random);*/
        memset(del, 0, sizeof(del));
        hm.clear();
        sort(paths.begin(), paths.end(), [](auto &a, auto &b)
             { return a.size() < b.size(); });
        int n = paths.size();
        for (int i = 0; i < n; ++i)
        {
            root.add(begin(paths[i]), end(paths[i]), i, to_hash(paths[i].back()));
        }
        root.upload();
        vector<vector<string>> ans;
        for (int i = 0; i < n; ++i)
        {
            if (del[i] == 0)
                ans.emplace_back(move(paths[i]));
        }
        return ans;
    }
};
