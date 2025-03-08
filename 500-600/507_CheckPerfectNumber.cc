
// source: https://leetcode.cn/problems/perfect-number/
// enumerate all divisors from 2 to sqrt(n)
// Time complexity: O(sqrt(n))
// Space complexity: O(1)



class Solution
{
public:
    bool checkPerfectNumber(int num)
    {
        if (num == 1)
        {
            return false;
        }

        int sum = 1;
        for (int d = 2; d * d <= num; ++d)
        {
            if (num % d == 0)
            {
                sum += d;
                if (d * d < num)
                {
                    sum += num / d;
                }
            }
        }
        return sum == num;
    }
};
