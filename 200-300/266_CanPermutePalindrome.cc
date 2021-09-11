#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    bool canPermutePalindrome(string s)
    {
        if (s.size() < 2)
            return 1;

        unordered_map<char, int> dict;
        for (int i = 0; i < s.size(); ++i)
        {
            dict[s[i]]++;
        }

        int cnt = 0;
        for (auto &i : dict)
        {
            if (i.second & 1) // 奇数 ++cnt
                ++cnt;
        }

        return cnt < 2;
    }
}