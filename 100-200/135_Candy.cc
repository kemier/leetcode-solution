#include <vector>

using namespace std;

class Solution //两次遍历
{
public:
    int candy(vector<int> &ratings)
    {
        int n = ratings.size();
        vector<int> left(n);
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && ratings[i] > ratings[i - 1])
            {
                left[i] = left[i - 1] + 1;
            }
            else
            {
                left[i] = 1;
            }
        }
        int right = 0, ret = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (i < n - 1 && ratings[i] > ratings[i + 1])
            {
                right++;
            }
            else
            {
                right = 1;
            }
            ret += max(left[i], right);
        }
        return ret;
    }
};

class Solution2 //贪心
{
public:
    int candy(vector<int> &ratings)
    {
        vector<int> candyVec(ratings.size(), 1);
        // 从前向后
        for (int i = 1; i < ratings.size(); i++)
        {
            if (ratings[i] > ratings[i - 1])
                candyVec[i] = candyVec[i - 1] + 1;
        }
        // 从后向前
        for (int i = ratings.size() - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                candyVec[i] = max(candyVec[i], candyVec[i + 1] + 1);
            }
        }
        // 统计结果
        int result = 0;
        for (int i = 0; i < candyVec.size(); i++)
            result += candyVec[i];
        return result;
    }
};
