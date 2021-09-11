#include <vector>
#include <string>
#include <unordered_map>
#include <climit>

using namespace std;

class Solution
{
public:
    int shortestDistance(vector<string> &words, string word1, string word2)
    {
        unordered_map<string, vector<int>> position;
        for (int i = 0; i < words.size(); ++i)
        {
            position[words[i]].push_back(i);
        }
        int res = INT_MAX;
        for (int i : position[word1])
        {
            for (int j : position[word2])
            {
                res = min(res, i < j ? j - i : i - j);
            }
        }
        return res;
    }
};
