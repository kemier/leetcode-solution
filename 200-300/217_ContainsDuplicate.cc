#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution //排序   时间复杂度：O(N\log N)  空间复杂度：O(\log N)
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 1; i++)
        {
            if (nums[i] == nums[i + 1])
            {
                return true;
            }
        }
        return false;
    }
};

class Solution2 //哈希表 时间复杂度：O(N)  空间复杂度：O(N)
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_set<int> s;
        for (int x : nums)
        {
            if (s.find(x) != s.end())
            {
                return true;
            }
            s.insert(x);
        }
        return false;
    }
};
