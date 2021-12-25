#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution //堆
{
public:
    static bool cmp(pair<int, int> &m, pair<int, int> &n)
    {
        return m.second > n.second;
    }

    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> occurrences;
        for (auto &v : nums)
        {
            occurrences[v]++;
        }

        // pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
        for (auto &[num, count] : occurrences)
        {
            if (q.size() == k)
            {
                if (q.top().second < count)
                {
                    q.pop();
                    q.emplace(num, count);
                }
            }
            else
            {
                q.emplace(num, count);
            }
        }
        vector<int> ret;
        while (!q.empty())
        {
            ret.emplace_back(q.top().first);
            q.pop();
        }
        return ret;
    }
};

class Solution2 //快速排序
{
public:
    void qsort(vector<pair<int, int>> &v, int start, int end, vector<int> &ret, int k)
    {
        int picked = rand() % (end - start + 1) + start;
        swap(v[picked], v[start]);

        int pivot = v[start].second;
        int index = start;
        for (int i = start + 1; i <= end; i++)
        {
            if (v[i].second >= pivot)
            {
                swap(v[index + 1], v[i]);
                index++;
            }
        }
        swap(v[start], v[index]);

        if (k <= index - start)
        {
            qsort(v, start, index - 1, ret, k);
        }
        else
        {
            for (int i = start; i <= index; i++)
            {
                ret.push_back(v[i].first);
            }
            if (k > index - start + 1)
            {
                qsort(v, index + 1, end, ret, k - (index - start + 1));
            }
        }
    }

    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> occurrences;
        for (auto &v : nums)
        {
            occurrences[v]++;
        }

        vector<pair<int, int>> values;
        for (auto &kv : occurrences)
        {
            values.push_back(kv);
        }
        vector<int> ret;
        qsort(values, 0, values.size() - 1, ret, k);
        return ret;
    }
};

class Solution3 //哈希表+大根堆
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        vector<int> res;
        if (nums.empty())
            return res;

        unordered_map<int, int> hash;
        priority_queue<pair<int, int>> q;

        for (int &num : nums)
            hash[num]++; //用哈希表统计每个数字出现的次数
        //将哈希表元素颠倒后存入大根堆，元素出现的次数排在前面
        for (auto &item : hash)
            q.push(make_pair(item.second, item.first));

        while (k--) //遍历k次，取出高频元素
        {
            res.push_back(q.top().second);
            q.pop();
        }

        return res;
    }
};
