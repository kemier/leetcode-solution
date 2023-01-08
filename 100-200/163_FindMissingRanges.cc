//
// Created by 曾宁 on 2023/1/8.
//

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        long l = lower;
        vector<string> ans;
        for(int i = 0; i < nums.size(); ++i)
        {
            if(l == nums[i])
                l++;//相等，我跳过你
            else if(l < nums[i])
            {	//有空缺
                if(l < nums[i]-1)//大于1
                    ans.push_back(to_string(l)+"->"+to_string(nums[i]-1));
                else if(l == nums[i]-1)//等于1
                    ans.push_back(to_string(l));
                l = long(nums[i])+1;//更新l到nums[i]下一个数
                // [2147483647]
                // 0
                // 2147483647
            }
        }
        if(l < upper)
            ans.push_back(to_string(l)+"->"+to_string(upper));
        else if(l==upper)
            ans.push_back(to_string(l));
        return ans;
    }
};
