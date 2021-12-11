#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <queue>

using namespace std;

class Solution
{
public:
    int minMeetingRooms(vector<vector<int>> &intervals)
    {
        map<int, int> m;
        for (auto &v : intervals)
            m[v[0]]++, m[v[1]]--;
        int ans = 0, res = 0;
        // 按照key值从小到大排序，如果相同，则value值小的排在前面
        // 例如(10, -1) 放在(10, 1) 前面
        for (auto &it : m)
        {
            ans += it.second;
            res = max(res, ans);
        }
        return res;
    }
};

class Solution2 //有序化处理
{
public:
    int minMeetingRooms(vector<vector<int>> &intervals)
    {
        if (intervals.size() == 0)
        {
            return 0;
        }

        vector<int> starts(intervals.size(), 0);
        vector<int> ends(intervals.size(), 0);
        for (int i = 0; i < intervals.size(); i++)
        {
            starts[i] = intervals[i][0];
            ends[i] = intervals[i][1];
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        auto startIter = starts.begin();
        auto endIter = ends.begin();
        int useRooms = 0;
        while (startIter != starts.end())
        {
            if (*startIter >= *endIter)
            {
                useRooms -= 1;
                endIter++;
            }
            useRooms += 1;
            startIter++;
        }
        return useRooms;
    }
};

class Solution3 //优先队列
{
public:
    int minMeetingRooms(vector<vector<int>> &intervals)
    {
        if (intervals.size() == 0)
        {
            return 0;
        }
        priority_queue<int, std::vector<int>, std::greater<int>> allocator;

        sort(intervals.begin(), intervals.end(),
             [](auto a, auto b) { return a[0] < b[0]; });
        allocator.push(intervals[0][1]);
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] >= allocator.top())
            {
                allocator.pop();
            }
            allocator.push(intervals[i][1]);
        }

        return allocator.size();
    }
};
