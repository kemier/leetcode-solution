#include <bits/stdc++.h>

using namespace std;

class Solution // dfs + backtrack
{
public:
    int minTransfers(vector<vector<int>> &transactions)
    {
        unordered_map<int, long> bal; // each person's overall balance
        for (auto &t : transactions)
        {
            bal[t[0]] -= t[2];
            bal[t[1]] += t[2];
        }
        for (auto &p : bal)
        {
            if (p.second)
            {
                debt.push_back(p.second);
            }
        }
        return dfs(0, 0);
    }

private:
    int dfs(int s, int cnt)
    { // min number of transactions to settle starting from debt[s]
        while (s < debt.size() && !debt[s])
        {
            ++s; // get next non-zero debt
        }
        int res = INT_MAX;
        for (long i = s + 1, prev = 0; i < debt.size(); ++i)
        {
            if (debt[i] != prev && debt[i] * debt[s] < 0)
            { // skip already tested or same sign debt
                debt[i] += debt[s];
                res = min(res, dfs(s + 1, cnt + 1)); // backtracking
                debt[i] -= debt[s];
                prev = debt[i];
            }
        }
        return res < INT_MAX ? res : cnt;
    }
    vector<long> debt; // all non-zero balances
};