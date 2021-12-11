#include <vector>

using namespace std;

class Solution1 //二分查找
{
public:
    int findDuplicate(vector<int> &nums)
    {
        int n = nums.size();
        int l = 1, r = n - 1, ans = -1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            int cnt = 0;
            for (int i = 0; i < n; ++i)
            {
                cnt += nums[i] <= mid;
            }
            if (cnt <= mid)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
                ans = mid;
            }
        }
        return ans;
    }
};

class Solution2 //位操作
{
public:
    int findDuplicate(vector<int> &nums)
    {
        int n = nums.size(), ans = 0;
        // 确定二进制下最高位是多少
        int bit_max = 31;
        while (!((n - 1) >> bit_max))
        {
            bit_max -= 1;
        }
        for (int bit = 0; bit <= bit_max; ++bit)
        {
            int x = 0, y = 0;
            for (int i = 0; i < n; ++i)
            {
                if (nums[i] & (1 << bit))
                {
                    x += 1;
                }
                if (i >= 1 && (i & (1 << bit)))
                {
                    y += 1;
                }
            }
            if (x > y)
            {
                ans |= 1 << bit;
            }
        }
        return ans;
    }
};

class Solution3 //快慢指针
{
public:
    int findDuplicate(vector<int> &nums)
    {
        int slow = 0, fast = 0;
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
