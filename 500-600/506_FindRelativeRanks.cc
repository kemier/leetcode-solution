
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//source: https://leetcode.cn/problems/relative-ranks/
//排序
//时间复杂度O(nlogn)
//空间复杂度O(n)

class Solution
{
public:
    vector<string> findRelativeRanks(vector<int> &score)
    {
        int n = score.size();
        string desc[3] = {"Gold Medal", "Silver Medal", "Bronze Medal"};
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; ++i)
        {
            arr.emplace_back(make_pair(-score[i], i));
        }
        sort(arr.begin(), arr.end());
        vector<string> ans(n);
        for (int i = 0; i < n; ++i)
        {
            if (i >= 3)
            {
                ans[arr[i].second] = to_string(i + 1);
            }
            else
            {
                ans[arr[i].second] = desc[i];
            }
        }
        return ans;
    }
};
