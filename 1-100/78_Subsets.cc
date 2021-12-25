#include <vector>

using namespace std;

class Solution //位运算
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> result;
        vector<int> vec;
        int all = 1 << (nums.size()); //构造所有子集
        for (int i = 1; i <= all; i++)
        {
            for (int j = 0; j < nums.size(); j++)
            {
                if (i & (1 << j))
                { //检查每个子集中包含的元素
                    vec.push_back(nums[j]);
                }
            }
            result.push_back(vec);
            vec.clear();
        }
        return result;
    }
};