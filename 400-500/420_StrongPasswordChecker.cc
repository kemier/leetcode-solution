#include <string>

using namespace std;

class Solution
{
public:
    int strongPasswordChecker(string s)
    {
        bool a = 0, b = 0, c = 0;
        for (auto &x : s)
        {
            if (x >= '0' && x <= '9')
                c = 1;
            else if (x >= 'a' && x <= 'z')
                a = 1;
            else if (x >= 'A' && x <= 'Z')
                b = 1;
        }
        int res = 0, k = a + b + c, len = s.size();
        if (len < 5)
            return 6 - len;
        else if (len == 5)
            return max(3 - k, 1);
        else
        {
            int p = 0, j = 1, del = len - 20, l = del;
            vector<int> t(2, 0);
            for (int i = 1; i < len; ++i)
            {
                if (s[i] == s[i - 1])
                    ++j;
                else
                {
                    p += j / 3;
                    if (j >= 3 && j % 3 < 2)
                        ++t[j % 3];
                    j = 1;
                }
            }
            p += j / 3;
            if (j >= 3 && j % 3 < 2)
                ++t[j % 3];
            if (len <= 20)
                return max(p, 3 - k);
            if (t[0] && del)
            {
                int q = min(t[0], del);
                del -= q;
                p -= q;
            }
            if (t[1] && del > 1)
            {
                int q = min(t[1] * 2, del);
                del -= q;
                p -= q / 2;
            }
            if (p && del > 2)
            {
                int q = min(p * 3, del);
                p -= q / 3;
            }
            return max(p, 3 - k) + l;
        }
        return 0;
    }
};
