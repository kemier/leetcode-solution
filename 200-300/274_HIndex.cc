#include <vector>
#include <algorithm>

using namespace std;

class Solution
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
