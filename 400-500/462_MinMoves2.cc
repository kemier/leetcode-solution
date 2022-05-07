#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int minMoves2(vector<int> nums)
    {
        sort(nums.begin(), nums.end());
        int sum = 0;
        for (int num : nums)
        {
            sum += abs(nums[nums.size() / 2] - num);
        }
        return sum;
    };
};

class Solution2 // QuickSelect
{
public:
    //快速选择寻找中位数
    int patition(vector<int> &arr, int l, int r)
    {
        int ran = rand() % (r - l + 1) + l;
        swap(arr[ran], arr[r]);

        int index = l - 1, x = arr[r];
        for (int i = l; i < r; ++i)
        {
            if (arr[i] <= x)
            {
                swap(arr[++index], arr[i]);
            }
        }

        swap(arr[++index], arr[r]);
        return index;
    }

    int quickSelect(vector<int> &arr, int l, int r, int target)
    {
        //递归到树底返回
        if (l == r)
            return arr[r];
        //获取局部排序下标
        int index = patition(arr, l, r);
        //找到返回，没找到缩小范围
        if (index == target)
            return arr[index];
        else if (index > target)
        {
            return quickSelect(arr, l, index - 1, target);
        }
        else
        {
            return quickSelect(arr, index, r, target);
        }
    }

    int minMoves2(vector<int> &nums)
    {
        srand((unsigned)time(0));
        int n = nums.size();
        int midNum = quickSelect(nums, 0, n - 1, n / 2);

        int ans = 0;
        for (int &num : nums)
        {
            ans += abs(midNum - num);
        }
        return ans;
    }
};