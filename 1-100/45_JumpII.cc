#include <vector>

using namespace std;

// 版本一
class Solution //贪心
{
public:
    int jump(vector<int> &nums)
    {
        if (nums.size() == 1)
            return 0;
        int curDistance = 0;  // 当前覆盖最远距离下标
        int ans = 0;          // 记录走的最大步数
        int nextDistance = 0; // 下一步覆盖最远距离下标
        for (int i = 0; i < nums.size(); i++)
        {
            nextDistance = max(nums[i] + i, nextDistance); // 更新下一步覆盖最远距离下标
            if (i == curDistance)
            { // 遇到当前覆盖最远距离下标
                if (curDistance != nums.size() - 1)
                {                               // 如果当前覆盖最远距离下标不是终点
                    ans++;                      // 需要走下一步
                    curDistance = nextDistance; // 更新当前覆盖最远距离下标（相当于加油了）
                    if (nextDistance >= nums.size() - 1)
                        break; // 下一步的覆盖范围已经可以达到终点，结束循环
                }
                else
                    break; // 当前覆盖最远距离下标是集合终点，不用做ans++操作了，直接结束
            }
        }
        return ans;
    }
};

// 版本二
class Solution2 //贪心
{
public:
    int jump(vector<int> &nums)
    {
        int curDistance = 0;  // 当前覆盖的最远距离下标
        int ans = 0;          // 记录走的最大步数
        int nextDistance = 0; // 下一步覆盖的最远距离下标
        for (int i = 0; i < nums.size() - 1; i++)
        {                                                  // 注意这里是小于nums.size() - 1，这是关键所在
            nextDistance = max(nums[i] + i, nextDistance); // 更新下一步覆盖的最远距离下标
            if (i == curDistance)
            {                               // 遇到当前覆盖的最远距离下标
                curDistance = nextDistance; // 更新当前覆盖的最远距离下标
                ans++;
            }
        }
        return ans;
    }
};
