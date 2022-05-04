#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

class Solution // DFS
{
    unordered_map<int, vector<int>> m;
    vector<int> ans;

public:
    vector<int> killProcess(vector<int> &pid, vector<int> &ppid, int kill)
    {
        int i, root = -1;
        for (i = 0; i < pid.size(); ++i)
        {
            if (ppid[i])
                m[ppid[i]].push_back(pid[i]);
        }
        dfs(kill);
        return ans;
    }

    void dfs(int root)
    {
        ans.push_back(root);
        for (int i = 0; i < m[root].size(); ++i)
            dfs(m[root][i]);
    }
};

class Solution2 // BFS
{
    unordered_map<int, vector<int>> m;
    vector<int> ans;

public:
    vector<int> killProcess(vector<int> &pid, vector<int> &ppid, int kill)
    {
        int i, cur;
        for (i = 0; i < pid.size(); ++i)
        {
            if (ppid[i])
                m[ppid[i]].push_back(pid[i]);
        }
        queue<int> q;
        q.push(kill);
        while (!q.empty())
        {
            cur = q.front();
            ans.push_back(cur);
            q.pop();
            for (int i = 0; i < m[cur].size(); ++i)
                q.push(m[cur][i]);
        }
        return ans;
    }
};
