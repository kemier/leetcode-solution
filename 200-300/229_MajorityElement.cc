#include <vector>
#include <iostream>
using namespace std;

class Solution //摩尔投票法 时间复杂度:O(n)  空间复杂度:O(1)
{
public:
    vector<int> majorityElement(vector<int> &nums)
    {
        vector<int> ans;
        if (nums.empty())
            return ans;
        int cand1, cand2;
        int count1, count2;
        cand1 = cand2 = count1 = count2 = 0;
        // 抵消阶段
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == cand1)
                count1++;
            else if (nums[i] == cand2)
                count2++;
            else if (count1 && count2)
            {
                count1--;
                count2--;
            }
            else if (!count1)
            {
                cand1 = nums[i];
                count1++;
            }
            else
            {
                cand2 = nums[i];
                count2++;
            }
        }
        // 计数阶段
        count1 = count2 = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == cand1)
                count1++;
            else if (nums[i] == cand2)
                count2++; // 必须用else if，保证每个数只算到一个候选人头上
            else
            {
            }
        }
        if (count1 > nums.size() / 3)
            ans.push_back(cand1);
        if (count2 > nums.size() / 3)
            ans.push_back(cand2);
        return ans;
    }
};