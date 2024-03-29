#include <bits/stdc++.h>

using namespace std;

class Solution // sliding window
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen)
        {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; ++i)
        {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount)
        {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i)
        {
            --sCount[s[i] - 'a'];
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount)
            {
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};

class Solution2 // optimized sliding window
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen)
        {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> count(26);
        for (int i = 0; i < pLen; ++i)
        {
            ++count[s[i] - 'a'];
            --count[p[i] - 'a'];
        }

        int differ = 0;
        for (int j = 0; j < 26; ++j)
        {
            if (count[j] != 0)
            {
                ++differ;
            }
        }

        if (differ == 0)
        {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i)
        {
            if (count[s[i] - 'a'] == 1)
            { // 窗口中字母 s[i] 的数量与字符串 p 中的数量从不同变得相同
                --differ;
            }
            else if (count[s[i] - 'a'] == 0)
            { // 窗口中字母 s[i] 的数量与字符串 p 中的数量从相同变得不同
                ++differ;
            }
            --count[s[i] - 'a'];

            if (count[s[i + pLen] - 'a'] == -1)
            { // 窗口中字母 s[i+pLen] 的数量与字符串 p 中的数量从不同变得相同
                --differ;
            }
            else if (count[s[i + pLen] - 'a'] == 0)
            { // 窗口中字母 s[i+pLen] 的数量与字符串 p 中的数量从相同变得不同
                ++differ;
            }
            ++count[s[i + pLen] - 'a'];

            if (differ == 0)
            {
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};
