#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
            return false;
        int alpha[26];
        memset(alpha, 0x00, sizeof(alpha));
        for (int i = 0; i < s.length(); i++)
        {
            alpha[s.at(i) - 'a']++;
            alpha[t.at(i) - 'a']--;
        }
        for (int i = 0; i < 26; i++)
            if (alpha[i] != 0)
                return false;
        return true;
    }
};

int main()
{
    string s = "anagram";
    string t = "anaargm";
    Solution solution;
    cout << boolalpha << solution.isAnagram(s, t) << endl;
    return 0;
}