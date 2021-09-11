class Solution //位方法 时间复杂度：O(1)  空间复杂度：O(1)
{
public:
    bool isPowerOfTwo(int n)
    {
        if (n == 0)
            return false;
        long x = n;
        return (x & (-x)) == x;
    }
};

class Solution2 //位方法 时间复杂度：O(1)  空间复杂度：O(1)
{
public:
    bool isPowerOfTwo(int n)
    {
        if (n == 0)
            return false;
        long x = n;
        return (x & (x - 1)) == 0;
    }
};

//https://leetcode-cn.com/problems/power-of-two/solution/2de-mi-by-leetcode/