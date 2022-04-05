#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution //自定义排序
{
public:
    string kthLargestNumber(vector<string> &nums, int k)
    {
        // 自定义比较函数，在 s1 对应的整数较大时返回 true，反之返回 false
        auto cmp = [](const string &s1, const string &s2) -> bool
        {
            // 首先比较字符串长度
            if (s1.size() > s2.size())
            {
                return true;
            }
            else if (s1.size() < s2.size())
            {
                return false;
            }
            else
            {
                // 长度相等时比较字符串字典序大小
                return s1 > s2;
            }
        };

        sort(nums.begin(), nums.end(), cmp);
        return nums[k - 1];
    }
};
