#include <string>

using namespace std;

class Solution
{
public:
    string shortestPalindrome(string s) // Rabin-Karp 字符串哈希算法 时间复杂度：O(|s|)  空间复杂度：O(1)
    {
        int n = s.size();
        int base = 131, mod = 1000000007;
        int left = 0, right = 0, mul = 1;
        int best = -1;
        for (int i = 0; i < n; ++i)
        {
            left = ((long long)left * base + s[i]) % mod;
            right = (right + (long long)mul * s[i]) % mod;
            if (left == right)
            {
                best = i;
            }
            mul = (long long)mul * base % mod;
        }
        string add = (best == n - 1 ? "" : s.substr(best + 1, n));
        reverse(add.begin(), add.end());
        return add + s;
    }

    string shortestPalindrome2(string s) //KMP  时间复杂度：O(|s|)   空间复杂度：O(|s|)
    {
        int n = s.size();
        vector<int> fail(n, -1); //next数组
        for (int i = 1; i < n; ++i)
        {
            int j = fail[i - 1];
            while (j != -1 && s[j + 1] != s[i])
            {
                j = fail[j];
            }
            if (s[j + 1] == s[i])
            {
                fail[i] = j + 1;
            }
        }
        int best = -1;
        for (int i = n - 1; i >= 0; --i)
        {
            while (best != -1 && s[best + 1] != s[i])
            {
                best = fail[best];
            }
            if (s[best + 1] == s[i])
            {
                ++best;
            }
        }
        string add = (best == n - 1 ? "" : s.substr(best + 1, n));
        reverse(add.begin(), add.end());
        return add + s;
    }
};
