#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<string> summaryRanges(vector<int> &nums)
    {
        vector<string> ans;
        int left = 0;

        for (int i = 0; i < nums.size(); ++i)
        {
            if (i + 1 == nums.size() || nums[i] + 1 != nums[i + 1])
            {
                ans.emplace_back(std::to_string(nums[left]) + (left == i ? "" : "->" + std::to_string(nums[i])));
                left = i + 1;
            }
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    int a[6] = {0, 1, 2, 4, 5, 7};
    vector<int> nums(a, a + 6);
    auto ans = solution.summaryRanges(nums);
    vector<string>::iterator iter;
    for (iter = ans.begin(); iter != ans.end(); iter++)
    {
        cout << *iter << endl;
    }
    return 0;
}
