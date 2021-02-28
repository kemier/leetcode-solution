#include <vector>
#include <queue>
#include <deque>
#include <iostream>

using namespace std;

class Solution //优先队列 时间复杂度：O(nlogn)  空间复杂度：O(n)
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < k; ++i)
        {
            q.emplace(nums[i], i);
        }
        vector<int> ans = {q.top().first};
        for (int i = k; i < n; ++i)
        {
            q.emplace(nums[i], i);
            while (q.top().second <= i - k)
            {
                q.pop();
            }
            ans.push_back(q.top().first);
        }
        return ans;
    }
};

class Solution2 //单调队列  时间复杂度：O(n)  空间复杂度：O(k)
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        deque<int> q;
        for (int i = 0; i < k; ++i)
        {
            while (!q.empty() && nums[i] >= nums[q.back()])
            {
                q.pop_back();
            }
            q.push_back(i);
        }

        vector<int> ans = {nums[q.front()]};
        for (int i = k; i < n; ++i)
        {
            while (!q.empty() && nums[i] >= nums[q.back()])
            {
                q.pop_back();
            }
            q.push_back(i);
            while (q.front() <= i - k)
            {
                q.pop_front();
            }
            ans.push_back(nums[q.front()]);
        }
        return ans;
    }
};

class Solution3 //分块 + 预处理  时间复杂度：O(n)  空间复杂度：O(n)
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> prefixMax(n), suffixMax(n);
        for (int i = 0; i < n; ++i)
        {
            if (i % k == 0)
            {
                prefixMax[i] = nums[i];
            }
            else
            {
                prefixMax[i] = max(prefixMax[i - 1], nums[i]);
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            if (i == n - 1 || (i + 1) % k == 0)
            {
                suffixMax[i] = nums[i];
            }
            else
            {
                suffixMax[i] = max(suffixMax[i + 1], nums[i]);
            }
        }

        vector<int> ans;
        for (int i = 0; i <= n - k; ++i)
        {
            ans.push_back(max(suffixMax[i], prefixMax[i + k - 1]));
        }
        return ans;
    }
};

int main()
{
    int nums[8] = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> v(nums, nums + 8);
    Solution solution;
    auto ans = solution.maxSlidingWindow(v, 3);
    vector<int>::iterator iter;
    for (iter = ans.begin(); iter != ans.end(); iter++)
        cout << *iter << endl;
    return 0;
}