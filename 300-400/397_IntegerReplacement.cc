#include <unordered_map>

using namespace std;

class Solution //记忆化搜索
{
private:
    unordered_map<int, int> memo;

public:
    int integerReplacement(int n)
    {
        if (n == 1)
        {
            return 0;
        }
        if (memo.count(n))
        {
            return memo[n];
        }
        if (n % 2 == 0)
        {
            return memo[n] = 1 + integerReplacement(n / 2);
        }
        return memo[n] = 2 + min(integerReplacement(n / 2), integerReplacement(n / 2 + 1));
    }
};

class Solution2 //枚举
{
public:
    int integerReplacement(int n)
    {
        if (n == 1)
        {
            return 0;
        }
        if (n % 2 == 0)
        {
            return 1 + integerReplacement(n / 2);
        }
        return 2 + min(integerReplacement(n / 2), integerReplacement(n / 2 + 1));
    }
};

class Solution3 //贪心
{
public:
    int integerReplacement(int n)
    {
        int ans = 0;
        while (n != 1)
        {
            if (n % 2 == 0)
            {
                ++ans;
                n /= 2;
            }
            else if (n % 4 == 1)
            {
                ans += 2;
                n /= 2;
            }
            else
            {
                if (n == 3)
                {
                    ans += 2;
                    n = 1;
                }
                else
                {
                    ans += 2;
                    n = n / 2 + 1;
                }
            }
        }
        return ans;
    }
};
