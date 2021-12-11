#include <vector>
#include <algorithm>

using namespace std;

class Solution1
{
public:
    int thirdMax(vector<int> &nums)
    {
        const long INF = -2147483649;
        long fir, sec, thi;
        fir = sec = thi = INF;
        for (long num : nums)
        {                  //以long类型读出，这里会有一定的效率损失
            if (num > fir) //如果比第一个大
                swap(num, fir);
            if (num < fir && num > sec) //比第一个小但比第二个大
                swap(num, sec);
            if (num < sec && num > thi) //比第二个小但比第三个大
                swap(num, thi);
        }
        if (thi != INF) //如果不是INF了
            return thi;
        return fir;
    }
};

class Solution2 //stl
{
public:
    int thirdMax(vector<int> &nums)
    {
        ​ sort(nums.begin(), nums.end());                           //排序
        ​ nums.erase(unique(nums.begin(), nums.end()), nums.end()); //除重
        ​ if (nums.size() < 3) return nums[nums.size() - 1];        //如果不到三个，返回最大的
        ​ return nums[nums.size() - 3];                             //返回第三大的
    }
};

class Solution3 //set除重+排序
{
public:
    int thirdMax(vector<int> &nums)
    {
        set<int> mySet(nums.begin(), nums.end()); //用哈希除重 + 排序
        const int length = mySet.size();
        set<int>::reverse_iterator it = mySet.rbegin(); //反向迭代器
        if (length < 3)
            return *it; //如果没有第三个大的
        ++it;
        ++it;
        return *it;
    }
};
