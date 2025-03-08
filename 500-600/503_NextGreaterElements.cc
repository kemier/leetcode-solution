#include <vector>
#include <stack>
using namespace std;

//source: https://leetcode.cn/problems/next-greater-element-ii/
//单调栈 + 环形数组
//时间复杂度O(n)
//空间复杂度O(n)

class Solution
{
public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ret(n, -1);
        stack<int> stk;
        for (int i = 0; i < n * 2 - 1; i++)
        {
            while (!stk.empty() && nums[stk.top()] < nums[i % n])
            {
                ret[stk.top()] = nums[i % n];
                stk.pop();
            }
            stk.push(i % n);
        }
        return ret;
    }
};
