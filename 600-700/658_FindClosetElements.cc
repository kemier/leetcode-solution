#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> findClosestElements(vector<int> &arr, int k, int x) //大顶堆+数组排序
    {
        //建立一个大顶堆
        priority_queue<pair<int, int>> temp;
        for (int i = 0; i < arr.size(); i++)
        {
            //维护大顶堆的的大小为K
            if (temp.size() < k)
            {
                temp.push({abs(arr[i] - x), i});
            }
            else
            {
                if (abs(arr[i] - x) < abs(temp.top().first))
                {
                    temp.pop();
                    temp.push({abs(arr[i] - x), i});
                }
            }
        }
        vector<int> res;
        while (!temp.empty())
        {
            res.push_back(arr[temp.top().second]);
            temp.pop();
        }
        //对结果进行排序
        sort(res.begin(), res.end());
        return res;
    }
};
