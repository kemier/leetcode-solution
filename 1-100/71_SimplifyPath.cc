#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    string simplifyPath(string path)
    {
        vector<string> stk;
        int n = stk.size(), i = 0;
        string str = "";
        while (i < n)
        {
            if (path[i] == '/')
                ++i;
            else
            {
                for (; i < n && path[i] != '/'; i++)
                {
                    str += path[i];
                }
                if (str == ".")
                {
                }
                else if (str == "..")
                {
                    if (!stk.empty())
                        stk.pop_back();
                }
                else
                {
                    stk.push_back(str);
                }
                str = "";
            }
        }
        if (stk.empty())
            return "/";
        string ans = "";
        for (auto &s : stk)
        {
            ans += ('/' + s);
        }

        return ans;
    }
}