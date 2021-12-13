#include <functional>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution //双联通分量  tarjan算法找桥
{
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
    {
        unordered_map<int, unordered_set<int>> adjvex;
        for (auto v : connections)
        {
            int x = v[0];
            int y = v[1];
            adjvex[x].insert(y);
            adjvex[y].insert(x);
        }

        vector<vector<int>> res;

        //------------------------ tarjan算法找桥 ------------------------//
        vector<int> dfn(n, 0); // dfs到的时间
        vector<int> low(n, 0); //可以回溯到的最早的时间点
        int T = 1;             //全局时间

        std::function<void(int, int)> tarjan = [&](int x, int parent)
        {
            dfn[x] = T;
            low[x] = T;
            T++;

            for (int y : adjvex[x])
            {
                if (y == parent)
                    continue;

                if (dfn[y] == 0)
                {
                    tarjan(y, x);
                    low[x] = min(low[x], low[y]);

                    if (low[y] > dfn[x])
                        res.push_back({x, y});
                }
                else if (dfn[y] != 0)
                    low[x] = min(low[x], dfn[y]);
            }
        };

        tarjan(0, -1);
        return res;
    }
};
