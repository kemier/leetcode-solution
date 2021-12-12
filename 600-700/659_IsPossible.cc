#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    bool isPossible(vector<int> &nums) //哈希表+小根堆
    {
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> mp;
        for (auto &x : nums)
        {
            if (mp.find(x) == mp.end())
            {
                mp[x] = priority_queue<int, vector<int>, greater<int>>();
            }
            if (mp.find(x - 1) != mp.end())
            {
                int prevLength = mp[x - 1].top();
                mp[x - 1].pop();
                if (mp[x - 1].empty())
                {
                    mp.erase(x - 1);
                }
                mp[x].push(prevLength + 1);
            }
            else
            {
                mp[x].push(1);
            }
        }
        for (auto it = mp.begin(); it != mp.end(); ++it)
        {
            priority_queue<int, vector<int>, greater<int>> queue = it->second;
            if (queue.top() < 3)
            {
                return false;
            }
        }
        return true;
    }

    bool isPossible2(vector<int> &nums) //贪心
    {
        unordered_map<int, int> countMap;
        unordered_map<int, int> endMap;
        for (auto &x : nums)
        {
            int count = countMap[x] + 1;
            countMap[x] = count;
        }
        for (auto &x : nums)
        {
            int count = countMap[x];
            if (count > 0)
            {
                int prevEndCount = endMap[x - 1];
                if (prevEndCount > 0)
                {
                    countMap[x] = count - 1;
                    endMap[x - 1] = prevEndCount - 1;
                    endMap[x] = endMap[x] + 1;
                }
                else
                {
                    int count1 = countMap[x + 1];
                    int count2 = countMap[x + 2];
                    if (count1 > 0 && count2 > 0)
                    {
                        countMap[x] = count - 1;
                        countMap[x + 1] = count1 - 1;
                        countMap[x + 2] = count2 - 1;
                        endMap[x + 2] = endMap[x + 2] + 1;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
