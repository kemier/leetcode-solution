#include <vector>
#include <algorithm>
#include <functional>
#include <set>
using namespace std;

bool comp(int a, int b)
{
    return a <= b;
}
class Solution //排序  时间复杂度：O(nlog n)  空间复杂度：O(1)
{
public:
    int missingNumber(vector<int> nums)
    {
        sort(nums.begin(), nums.end(), comp);

        // 判断 n 是否出现在末位
        if (nums[nums.size() - 1] != nums.size())
        {
            return nums.size();
        }
        // 判断 0 是否出现在首位
        else if (nums[0] != 0)
        {
            return 0;
        }

        // 此时缺失的数字一定在 (0, n) 中
        for (int i = 1; i < nums.size(); i++)
        {
            int expectedNum = nums[i - 1] + 1;
            if (nums[i] != expectedNum)
            {
                return expectedNum;
            }
        }

        // 未缺失任何数字（保证函数有返回值）
        return -1;
    }
};

class Solution2 //哈希表 时间复杂度：O(n)  空间复杂度：O(n)
{
public:
    int missingNumber(vector<int> nums)
    {
        set<int> numSet;
        for (int num : nums)
            numSet.insert(num);

        int expectedNumCount = nums.size() + 1;
        for (int number = 0; number < expectedNumCount; number++)
        {
            if (numSet.count(number) == 0)
            {
                return number;
            }
        }
        return -1;
    }
};

class Solution3 //位运算  时间复杂度：O(n)  空间复杂度：O(1)
{
public:
    int missingNumber(vector<int> nums)
    {
        int missing = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            missing ^= i ^ nums[i];
        }
        return missing;
    }
};

class Solution4 //数学方法  时间复杂度：O(n)  空间复杂度：O(1)
{
public
    int missingNumber(vector<int> nums)
    {
        int expectedSum = nums.size() * (nums.size() + 1) / 2;
        int actualSum = 0;
        for (int num : nums)
            actualSum += num;
        return expectedSum - actualSum;
    }
};
