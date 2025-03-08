#include <string>
#include <algorithm>
using namespace std;

//source: https://leetcode.cn/problems/base-7/
//Time complexity: O(logn)
//Space complexity: O(logn)


class Solution
{
public:
    string convertToBase7(int num)
    {
        if (num == 0)
        {
            return "0";
        }
        bool negative = num < 0;
        num = abs(num);
        string digits;
        while (num > 0)
        {
            digits.push_back(num % 7 + '0');
            num /= 7;
        }
        if (negative)
        {
            digits.push_back('-');
        }
        reverse(digits.begin(), digits.end());
        return digits;
    }
};
