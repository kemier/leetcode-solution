#include <algorithm>
#include <vector>

using namespace std;

class Solution //桶排序
{
public:
    int heightChecker(vector<int> &heights)
    {
        // 预留一个，后续计算无需减1
        int cnt[101];
        memset(cnt, 0, sizeof(cnt));
        for (int height : heights)
        {
            ++cnt[height];
        }

        int res = 0;
        // 再次遍历去找对应的序号是否符合预期数字
        // heights的序号
        int j = 0;
        // i是当前的高度
        for (int i = 1; i <= 100; ++i)
        {
            while (cnt[i] > 0)
            {
                --cnt[i];
                // 不符合预期，则计数器+1
                if (heights[j] != i)
                {
                    ++res;
                }
                ++j;
            }
        }

        return res;
    }
};
