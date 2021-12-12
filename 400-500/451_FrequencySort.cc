#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution
{
public:
    string frequencySort(string s) //哈希表
    {
        unordered_map<char, int> mp;
        int length = s.length();
        for (auto &ch : s)
        {
            mp[ch]++;
        }
        vector<pair<char, int>> vec;
        for (auto &it : mp)
        {
            vec.emplace_back(it);
        }
        sort(vec.begin(), vec.end(), [](const pair<char, int> &a, const pair<char, int> &b)
             { return a.second > b.second; });
        string ret;
        for (auto &[ch, num] : vec)
        {
            for (int i = 0; i < num; i++)
            {
                ret.push_back(ch);
            }
        }
        return ret;
    }
    string frequencySort2(string s) //桶排序
    {
        unordered_map<char, int> mp;
        int maxFreq = 0;
        int length = s.size();
        for (auto &ch : s)
        {
            maxFreq = max(maxFreq, ++mp[ch]);
        }
        vector<string> buckets(maxFreq + 1);
        for (auto &[ch, num] : mp)
        {
            buckets[num].push_back(ch);
        }
        string ret;
        for (int i = maxFreq; i > 0; i--)
        {
            string &bucket = buckets[i];
            for (auto &ch : bucket)
            {
                for (int k = 0; k < i; k++)
                {
                    ret.push_back(ch);
                }
            }
        }
        return ret;
    }
};
