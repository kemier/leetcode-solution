#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution //分治法
{
    int count_in_range(vector<int> &nums, int target, int lo, int hi)
    {
        int count = 0;
        for (int i = lo; i <= hi; ++i)
            if (nums[i] == target)
                ++count;
        return count;
    }
    int majority_element_rec(vector<int> &nums, int lo, int hi)
    {
        if (lo == hi)
            return nums[lo];
        int mid = (lo + hi) / 2;
        int left_majority = majority_element_rec(nums, lo, mid);
        int right_majority = majority_element_rec(nums, mid + 1, hi);
        if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2)
            return left_majority;
        if (count_in_range(nums, right_majority, lo, hi) > (hi - lo + 1) / 2)
            return right_majority;
        return -1;
    }

public:
    int majorityElement(vector<int> &nums)
    {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }
};

class Solution2 //哈希表
{
public:
    int majorityElement(vector<int> &nums)
    {
        unordered_map<int, int> counts;
        int majority = 0, cnt = 0;
        for (int num : nums)
        {
            ++counts[num];
            if (counts[num] > cnt)
            {
                majority = num;
                cnt = counts[num];
            }
        }
        return majority;
    }
};

class Solution3 //排序
{
public:
    int majorityElement(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

class Solution4 //随机化
{
public:
    int majorityElement(vector<int> &nums)
    {
        while (true)
        {
            int candidate = nums[rand() % nums.size()];
            int count = 0;
            for (int num : nums)
                if (num == candidate)
                    ++count;
            if (count > nums.size() / 2)
                return candidate;
        }
        return -1;
    }
};

class Solution5 // Boyer-Moore 投票算法
{
public:
    int majorityElement(vector<int> &nums)
    {
        int candidate = -1;
        int count = 0;
        for (int num : nums)
        {
            if (num == candidate)
                ++count;
            else if (--count < 0)
            {
                candidate = num;
                count = 1;
            }
        }
        return candidate;
    }
};
