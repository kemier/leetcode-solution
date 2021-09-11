#include <vector>
#include <climits>
#include <algorithm>
using namespace std;


class Solution //DP
{
public:
    int minCost(vector<vector<int>> costs)
    {
        int n = costs.size();
        if (n == 0)
            return 0;
        vector<vector<int>> total_costs(n, vector<int>(3));
        for (int i = 0; i < 3; i++)
        {
            total_costs[0][i] = costs[0][i];
        }
        if (n > 1)
        {
            for (int i = 1; i < n; i++)
            {
                total_costs[i][0] = costs[i][0] + min(total_costs[i - 1][1], total_costs[i - 1][2]);
                total_costs[i][1] = costs[i][1] + min(total_costs[i - 1][0], total_costs[i - 1][2]);
                total_costs[i][2] = costs[i][2] + min(total_costs[i - 1][0], total_costs[i - 1][1]);
            }
        }
        int max = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            max = min(max, total_costs[n - 1][i]);
        }
        return max;
    }
};
