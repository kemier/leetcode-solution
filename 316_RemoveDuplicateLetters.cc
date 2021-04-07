#include <string>

using namespace std;

class Solution
{
public:
    string removeDuplicateLetters(string s)
    {
        int count[26] = {0};
        for (int i = 0; i < s.length(); i++)
            count[s[i] - 'a']++;
        int pos = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] < s[pos])
                pos = i;
            if (--count[s[i] - 'a'] == 0)
                break;
        }
        string suffix;
        if (pos + 1 > s.length())
            suffix = "";
        else
            suffix = s.substr(pos + 1, s.length() - pos - 1);
        return s.length() == 0 ? "" : s[pos] + removeDuplicateLetters(removeOneLetter(suffix, s[pos]));
    }
    string removeOneLetter(string s, char ch)
    {
        while (1)
        {
            int index = s.find(ch);
            if (index != -1)
                s = s.erase(index, 1);
            else
                break;
        }
        return s;
    }
};