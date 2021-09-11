#include <vector>
#include <utility>
#include <queue>
#include <iostream>

using namespace std;

class Solution
{
public:
    void wallsAndGates(vector<vector<int>> &rooms)
    {
        if (rooms.empty() || rooms[0].empty())
            return;
        const int INF = 2147483647;
        int m = rooms.size(), n = rooms[0].size();
        vector<pair<int, int>> directs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (rooms[i][j] != 0)
                    continue;
                q.push(make_pair(i, j));
            }
        }
        while (!q.empty())
        {
            auto pos = q.front();
            q.pop();
            int x = pos.first, y = pos.second;
            int dp = rooms[x][y] + 1;
            for (auto d : directs)
            {
                int nx = x + d.first, ny = y + d.second;
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || rooms[nx][ny] != INF)
                    continue;
                rooms[nx][ny] = dp;
                q.push(make_pair(nx, ny));
            }
        }
        return;
    }
};

int main()
{
    const int INF = 2147483647;
    Solution solution;
    vector<vector<int>> nums, ans;
    vector<int> v1{INF, -1, 0, INF};
    vector<int> v2{INF, INF, INF, -1};
    vector<int> v3{INF, -1, INF, -1};
    vector<int> v4{0, -1, INF, INF};
    nums.push_back(v1);
    nums.push_back(v2);
    nums.push_back(v3);
    nums.push_back(v4);
    solution.wallsAndGates(nums);
    vector<vector<int>>::iterator iter1;
    vector<int>::iterator iter2;
    for (iter1 = nums.begin(); iter1 != nums.end(); iter1++)
    {
        for (iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2)
        {
            cout << *iter2 << " ";
        }
        cout << endl;
    }

    return 0;
}