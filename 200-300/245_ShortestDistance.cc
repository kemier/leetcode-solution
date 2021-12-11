#include <vector>
#include <string>
#include <unordered_map>
#include <climit>
#include <cmath>

using namespace std;

class Solution
{
public:
    int shortestWordDistance(vector<string> &words, string word1, string word2)
    {
        unordered_map<string, vector<int>> m;
        for (int i = 0; i < words.size(); ++i)
        {
            m[words[i]].push_back(i);
        }
        int res = INT_MAX;
        if (word1 != word2)
        {
            for (int i : m[word1])
            {
                for (int j : m[word2])
                {
                    res = min(res, abs(i - j));
                }
            }
        }
        else
        {
            for (int i = 1; i < m[word1].size(); ++i)
            {
                res = min(res, m[word1][i] - m[word1][i - 1]);
            }
        }
        return res;
    }
};
