#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int threeSumSmaller(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size(), ans = 0, i, j, k;
        for (int i = 0; i < n - 2; i++)
        {
            int j = i + 1, k = n - 1;
            while (j < k)
            {
                if (nums[i] + nums[j] + nums[k] >= target)
                    k--;
                else
                {
                    ans += (k - j);
                    j++;
                }
            }
        }
        return ans;
    }
};