
// Source: https://leetcode-cn.com/problems/fibonacci-number/
// dynamic programming
// Time Complexity: O(n)
// Space Complexity: O(1)

class Solution
{
public:
    int fib(int n)
    {
        if (n < 2)
        {
            return n;
        }
        int p = 0, q = 0, r = 1;
        for (int i = 2; i <= n; ++i)
        {
            p = q;
            q = r;
            r = p + q;
        }
        return r;
    }
};
