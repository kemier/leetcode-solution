#include <algorithm>

using namespace std;

class Solution
{
public:
    int countDigitOne(int n)
    {
        int countr = 0;
        for (long long i = 1; i <= n; i *= 10)
        {
            long long divider = i * 10;
            countr += (n / divider) * i + min(max(n % divider - i + 1, 0LL), i);
        }
        return countr;
    }
};

class Solution2
{
public:
    int countDigitOne(int n)
    {
        int count = 0;
        int high = n;
        int cur = 0;
        long b = 1;
        while (high > 0)
        {
            cur = high % 10;
            high /= 10;
            count += high * b;
            if (cur == 1)
            {
                count += n % b + 1;
            }
            else if (cur > 1)
            {
                count += b;
            }
            b *= 10;
        }
        return count;
    }
};

//https://blog.csdn.net/weixin_37840621/article/details/87897369?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522161443092516780261915824%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=161443092516780261915824&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-87897369.first_rank_v2_pc_rank_v29_10&utm_term=leetcode+233&spm=1018.2226.3001.4187