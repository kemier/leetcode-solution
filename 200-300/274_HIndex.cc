#include <vector>
#include <algorithm>

using namespace std;

class Solution //排序
{
public:
    int hIndex(vector<int> &citations)
    {
        if (citations.size() == 0)
            return 0;

        sort(citations.begin(), citations.end(), cmp);
        for (int i = 0; i < citations.size(); i++)
            if (citations[i] < i + 1)
                return i;
        return citations.size(); //如果所有的序号都不大于被引次数，则论文数就是H指数，如[11,15]结果为2
    }

private:
    static bool cmp(int a, int b)
    {
        return a > b;
    }
};

class Solution2 //计数排序
{
public:
    int hIndex(vector<int> &citations)
    {
        int n = citations.size(), tot = 0;
        vector<int> counter(n + 1);
        for (int i = 0; i < n; i++)
        {
            if (citations[i] >= n)
            {
                counter[n]++;
            }
            else
            {
                counter[citations[i]]++;
            }
        }
        for (int i = n; i >= 0; i--)
        {
            tot += counter[i];
            if (tot >= i)
            {
                return i;
            }
        }
        return 0;
    }
};
