#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;
class Solution
{

public:
    vector<string> topKFrequent(vector<string> words, int k)
    {
        // 1.先用哈希表统计单词出现的频率
        unordered_map<string, int> count;
        for (string word : words)
        {
            count.insert(make_pair(word, count[word] + 1));
        }
        // 2.构建小根堆 这里需要自己构建比较规则 此处为 lambda 写法 Java 的优先队列默认实现就是小根堆
        priority_queue<string, vector<string>, greater<string>> minHeap;

        // 3.依次向堆加入元素。
        for (auto it = count.begin(); it != count.end(); it++)
        {
            minHeap.push(it->first);
            // 当堆中元素个数大于 k 个的时候，需要弹出堆顶最小的元素。
            if (minHeap.size() > k)
            {
                minHeap.pop();
            }
        }
        // 4.依次弹出堆中的 K 个元素，放入结果集合中。
        vector<string> res;
        res.reserve(k);
        while (minHeap.size() > 0)
        {
            res.push_back(minHeap.top());
            minHeap.pop();
        }
        // 5.注意最后需要反转元素的顺序。
        reverse(res.begin(), res.end());
        return res;
    }
};
