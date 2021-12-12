#include <set>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool find132Pattern(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3)
            return false;

        //左侧最小值
        int left_min = nums[0];
        //右侧所有元素
        multiset<int> right_all;
        s for (int k = 2; k < n; k++)
        {
            right_all.insert(nums[k]);
        }

        for (int j = 1; j < n - 1; ++j)
        {
            if (left_min < nums[j])
            {
                auto it = right_all.upper_bound(left_min);
                if (it != right_all.end() && *it < nums[j])
                {
                    return true;
                }
            }
            left_min = min(left_min, nums[j]);
            right_all.erase(right_all.find(nums[j + 1]));
        }
        return false;
    }

    bool find132Pattern2(vector<int> &nums)
    {
        int n = nums.size();
        stack<int> candidate_k;
        candidate_k.push(nums[n - 1]);
        int max_k = INT_MIN;

        for (int i = n - 2; i >= 0; --i)
        {
            if (nums[i] < max_k)
            {
                return true;
            }

            while (!candidate_k.empty() && nums[i] > candidate_k.top())
            {
                max_k = candidate_k.top();
                candidate_k.pop();
            }
            if (nums[i] > max_k)
            {
                candidate_k.push(nums[i]);
            }
        }
        return false;
    }
    bool find132Pattern3(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> candidate_i = {nums[0]};
        vector<int> candidate_j = {nums[0]};

        for (int k = 1; k < n; ++k)
        {
            auto it_i = upper_bound(candidate_i.begin(), candidate_i.end(), nums[k], greater<int>());
            auto it_j = lower_bond(candidate_j.begin(), candidate_j.end(), nums[k], greater<int>());
            if (it_i != candidate_i.end() && it_j != candidate_j.begin())
            {
                int idx_i = it_i - candidate_i.begin();
                int idx_j = it_j - candidate_j.begin() - 1;
                if (idx_i <= idx_j)
                {
                    return true;
                }
            }

            if (nums[k] < candidate_i.back())
            {
                candidate_i.push_back(nums[k]);
                candidate_j.push_back(nums[k]);
            }
            else if (nums[k] > candidate_j.back())
            {
                int last_i = candidate_i.back();
                while (!candidate_j.empty() && nums[k] > candidate_j.back())
                {
                    candidate_i.pop_back();
                    candidate_j.pop_back();
                }
                candidate_i.push_back(last_i);
                candidate_j.push_back(nums[k]);
            }
        }
    }
};