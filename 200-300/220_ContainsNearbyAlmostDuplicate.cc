#include <vector>
#include <set>

using namespace std;

class Solution
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