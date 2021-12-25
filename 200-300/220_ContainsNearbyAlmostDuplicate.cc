#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

class Solution //滑动窗口 + 有序集合
{
public:
    bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
    {
        set<long> s;
        for (int i = 0; i < nums.size(); ++i)
        {
            auto lower = s.lower_bound(nums[i]);
            if (lower != s.end() && *lower <= nums[i] + t)
                return true;
            auto upper = s.upper_bound(nums[i]);
            if (upper != s.begin() && nums[i] <= *--upper + t)
                return true; // upper 为 s.begin() 时说明查找结果为空
            s.insert(nums[i]);
            if (s.size() > k)
                s.erase(nums[i - k]);
        }
        return false;
    }
};

class Solution2 //桶
{
public:
    int getID(int x, long w)
    {
        return x < 0 ? (x + 1ll) / w - 1 : x / w;
    }

    bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
    {
        unordered_map<int, int> mp;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            long x = nums[i];
            int id = getID(x, t + 1ll);
            if (mp.count(id))
            {
                return true;
            }
            if (mp.count(id - 1) && abs(x - mp[id - 1]) <= t)
            {
                return true;
            }
            if (mp.count(id + 1) && abs(x - mp[id + 1]) <= t)
            {
                return true;
            }
            mp[id] = x;
            if (i >= k)
            {
                mp.erase(getID(nums[i - k], t + 1ll));
            }
        }
        return false;
    }
};
