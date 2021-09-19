#include <string>

using namespace std;

class Solution //O(1)  O(1)或者O(N)
{
public:
    string reverseVowels(string s)
    {
        auto isVowel = [vowels = "aeiouAEIOU"s](char ch)
        {
            return vowels.find(ch) != string::npos;
        };

        int n = s.size();
        int i = 0, j = n - 1;
        while (i < j)
        {
            while (i < n && !isVowel(s[i]))
            {
                ++i;
            }
            while (j > 0 && !isVowel(s[j]))
            {
                --j;
            }
            if (i < j)
            {
                swap(s[i], s[j]);
                ++i;
                --j;
            }
        }
        return s;
    }
};
