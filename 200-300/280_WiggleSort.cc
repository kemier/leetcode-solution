#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    void wiggleSort(vector<int> &nums)
    {
        int len = nums.size(), index = 1;
        if (len == 0)
            return;
        for (int i = 0; i < len - 1; i++)
        {
            if (i % 2 == 0 && nums[i] > nums[i + 1])
                swap(nums[i], nums[i + 1]);
            if (i % 2 == 1 && nums[i] < nums[i + 1])
                swap(nums[i], nums[i + 1]);
        }
    }
};