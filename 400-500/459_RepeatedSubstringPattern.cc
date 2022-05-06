#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    bool repeatedSubstringPattern(string s)
    {
        return (s + s).find(s, 1) != s.size();
    }
};

class Solution2 // Kmp
{
public:
    bool kmp(const string &query, const string &pattern)
    {
        int n = query.size();
        int m = pattern.size();
        vector<int> fail(m, -1);
        for (int i = 1; i < m; ++i)
        {
            int j = fail[i - 1];
            while (j != -1 && pattern[j + 1] != pattern[i])
            {
                j = fail[j];
            }
            if (pattern[j + 1] == pattern[i])
            {
                fail[i] = j + 1;
            }
        }
        int match = -1;
        for (int i = 1; i < n - 1; ++i)
        {
            while (match != -1 && pattern[match + 1] != query[i])
            {
                match = fail[match];
            }
            if (pattern[match + 1] == query[i])
            {
                ++match;
                if (match == m - 1)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool repeatedSubstringPattern(string s)
    {
        return kmp(s + s, s);
    }
};
