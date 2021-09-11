#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            if (map.find(nums[i]) != map.end() && i - map[nums[i]] <= k)
            {
                return true;
            }
            map[nums[i]] = i;
        }
        return false;
    }
};
