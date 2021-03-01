#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class Solution
{
public:
    int strobogrammaticInRange(string low, string high)
    {
        int n1 = low.length(), n2 = high.length();
        int ret = 0;
        for (int i = n1; i <= n2; ++i)
        {
            dfs(low, high, i, "", ret);
        }
        return ret;
    }

private:
    void dfs(string &low, string &high, int n, string str, int &result)
    {
        if (n == 0)
        {
            if (stol(str) >= stol(low) && stol(str) <= stol(high))
            {
                ++result;
            }
            return;
        }
        if (n % 2 != 0)
        {
            // cout << n << endl;
            for (auto val : same)
            {
                dfs(low, high, n - 1, val, result);
            }
        }
        else
        {
            // cout << n << endl;
            for (int i = (n == 2) ? 1 : 0; i < two.size(); ++i)
            {
                dfs(low, high, n - 2, two[i].first + str + two[i].second, result);
            }
        }
    }
    vector<string> same{"0", "1", "8"};
    vector<pair<char, char>> two{{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
};

int main()
{
    Solution solution;
    cout << solution.strobogrammaticInRange("100", "999") << endl;
    return 0;
}