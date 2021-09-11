#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    string alienOrder(vector<string> &words)
    {
        if (words.size() == 0)
            return "";
        unordered_map<char, int> indegree;
        unordered_map<char, multiset<char>> hash;
        for (auto word : words)
            for (auto ch : word)
                indegree[ch] = 0;
        for (int i = 1; i < words.size(); i++)
        {
            int k = 0, len1 = words[i - 1].size(), len2 = words[i].size();
            while (words[i - 1][k] == words[i][k])
                k++;
            if (k >= min(len1, len2))
                continue;
            indegree[words[i][k]]++;
            hash[words[i - 1][k]].insert(words[i][k]);
        }
        string ans;
        for (int i = 0; i < indegree.size(); i++)
        {
            char ch = ' ';
            for (auto val : indegree)
                if (!val.second)
                {
                    ch = val.first;
                    break;
                }
            if (ch == ' ')
                return "";
            ans += ch, indegree[ch]--;
            for (auto val : hash[ch])
                indegree[val]--;
        }
        return ans;
    }
};