#include <vector>

using namespace std;

class Solution //位运算
{
public:
    int singleNumber(vector<int> &nums)
    {
        int a = 0, b = 0;
        for (int num : nums)
        {
            tie(a, b) = pair{(~a & b & num) | (a & ~b & ~num), ~a & (b ^ num)};
        }
        return b;
    }
};
