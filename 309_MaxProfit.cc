#include <vector>
#include <climits>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.size() <= 1)
            return 0;
        int s0 = 0;
        int s1 = -prices[0];
        int s2 = INT_MIN;
        for (int i = 1; i < prices.size(); i++)
        {
            int pre0 = s0;
            int pre1 = s1;
            int pre2 = s2;
            s0 = max(pre0, pre2);
            s1 = max(pre0 - prices[i], pre1);
            s2 = pre1 + prices[i];
        }
        //最大利润不可能出现在buy而未sell的时候，所以不考虑s1
        return max(s0, s2);
    }
};
