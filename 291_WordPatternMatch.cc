#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <math.h>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;

class Solution
{
public:
    bool wordPatternMatch(string pattern, string str)
    {
        return process(pattern, str);
    }
    bool process(string pattern, string str)
    {
        if (pattern.empty())
            return str.empty();
        if (str.empty())
            return pattern.empty();
        //该字符尚未匹配
        if (mymap.find(pattern[0]) == mymap.end())
        {
            for (int i = 1; i < str.length(); i++)
            {
                mymap[pattern[0]] = str.substr(0, i);
                if (process(pattern.substr(1), str.substr(i)))
                    return true;
            }
        }
        else
        { //当该字符已经匹配过了
            if (mymap[pattern[0]].length() > str.length())
                return false;
            if (mymap[pattern[0]] == str.substr(0, mymap[pattern[0]].length()))
                return process(pattern.substr(1), str.substr(mymap[pattern[0]].length()));
            else
                return false;
        }
        return false;
    }
    map<char, string> mymap; //key为pattern中的字符串，value为该元素匹配的字符串
};
int main()
{
    string pattern = "aaaa";
    string str = "asdasdasdasd";
    Solution solution;
    if (solution.wordPatternMatch(pattern, str))
    {
        for (int i = 0; i < pattern.length(); i++)
        {
            cout << pattern[i] << ": " << solution.mymap[pattern[i]] << " " << solution.mymap[pattern[i]].length() << endl;
        }
    }
    system("pause");
    return 0;
}