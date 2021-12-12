#include <vector>
#include <queue>

using namespace std;

//步骤：
// 1. 建图 2. 入队 3. 广度搜索

class Solution
{
public:
    bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs)
    {
        //建图
        int n = org.size();
        vector<vector<int>> g(n + 1);    //图
        vector<int> indegree(n + 1, 0);  //入度
        vector<bool> exit(n + 1, false); //判断seqs是否包含所有org
        for (auto &s : seqs)
        {
            for (int i = 0; i < s.size(); ++i)
            {
                if (s[i] <= 0 || s[i] > n)
                    return false; // seqs包含orgs以外结点
                exit[s[i]] = true;
                if (i < s.size() - 1)
                {
                    g[s[i]].push_back(s[i + 1]);
                    ++indegree[s[i + 1]];
                }
            }
        }

        //入度为0结点 入队
        queue<int> q;
        for (int i = 1; i <= n; ++i)
        {
            if (!exit[i])
                return false; // seqs不包含所有orgs的结点
            if (indegree[i] == 0)
                q.push(i);
        }

        //广度优先遍历
        int i = 0;
        while (!q.empty())
        {
            //序列不能被唯一重建 或 重建与序列不匹配
            if (q.size() != 1 || q.front() != org[i++])
                return false;
            //队头弹出  新入度为0结点 入队
            int cur = q.front();
            q.pop();
            for (int p : g[cur])
            {
                --indegree[p];
                if (indegree[p] == 0)
                    q.push(p);
            }
        }
        return i == n ? true : false;
    }
};
