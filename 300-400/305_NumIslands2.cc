#include <vector>
#include <utility>

using namespace std;

class Solution //并查集
{
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>> &positions)
    {
        vector<vector<int>> mp(m, vector<int>(n, 0));
        vector<int> result;
        int num = 0;
        vector<int> par(m * n);
        for (int i = 0; i < m * n; i++)
            par[i] = i;
        for (auto val : positions)
        {
            vector<pair<int, int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto val2 : dir)
            {
                int x = val.first, y = val.second, px = x + val2.first, py = y + val2.second;
                if (px < 0 || px >= m || py < 0 || py >= n || !mp[px][py])
                    continue;
                int par1 = x * n + y, par2 = px * n + py;
                while (par[par1] != par1)
                    par[par1] = par[par[par1]], par1 = par[par1];
                while (par[par2] != par2)
                    par[par2] = par[par[par2]], par2 = par[par2];
                if (par1 != par2)
                    par[par2] = par1, num--;
            }
            mp[val.first][val.second] = 1;
            result.push_back(++num);
        }
        return result;
    }
};