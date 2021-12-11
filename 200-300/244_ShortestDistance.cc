#include <vector>
#include <string>
#include <unordered_map>
#include <climit>
#include <cmath>

using namespace std;

class WordDistance
{
public:
    WordDistance(vector<string> &words)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            m[words[i]].push_back(i);
        }
    }

    int shortest(string word1, string word2)
    {
        int res = INT_MAX;
        for (int i = 0; i < m[word1].size(); ++i)
        {
            for (int j = 0; j < m[word2].size(); ++j)
            {
                res = min(res, abs(m[word1][i] - m[word2][j]));
            }
        }
        return res;
    }

private:
    unordered_map<string, vector<int>> m;
};