#include <algorithm>
#include <vector>

using namespace std;

class Solution //位运算
{
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int S = nums.size();
        int N = 1 << S; //二进制数
        vector<vector<int>> res;
        for (int i = 0; i < N; ++i)
        {
            vector<int> v;
            bool flag = true;
            for (int j = 0; j < S; ++j)
            {
                if (i & (1 << j)) //取每一位：不需要声明为二进制，这样就可以！！
                {
                    if (j != 0 && nums[j] == nums[j - 1] && ((i & (1 << (j - 1))) == 0)) //除重
                    {
                        flag = false;
                        break;
                    }
                    v.push_back(nums[j]);
                }
            }
            if (flag)
                res.push_back(v);
        }
        return res;
    }
};
