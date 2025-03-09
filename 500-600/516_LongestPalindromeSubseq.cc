#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//source : https://leetcode-cn.com/problems/longest-palindromic-subsequence/
//dp
//Time complexity: O(n^2)
//Space complexity: O(n^2)


class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = n - 1; i >= 0; i--)
        {
            dp[i][i] = 1;
            char c1 = s[i];
            for (int j = i + 1; j < n; j++)
            {
                char c2 = s[j];
                if (c1 == c2)
                {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else
                {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
