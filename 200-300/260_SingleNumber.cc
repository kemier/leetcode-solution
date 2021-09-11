#include <vector>

using namespace std;

class Solution //时间复杂度：O(n) 空间复杂度：O(1)
{
public:
    vector<int> singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (int n : nums)
            ret ^= n;
        int div = 1;
        while ((div & ret) == 0)
            div <<= 1;
        int a = 0, b = 0;
        for (int n : nums)
            if (div & n)
                a ^= n;
            else
                b ^= n;
        return vector<int>{a, b};
    }
};
