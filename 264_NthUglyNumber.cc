#include <vector>
#include <set>
#include <functional>
#include <queue>
#include <algorithm>

using namespace std;

class Ugly
{
public:
    vector<int> nums;
    Ugly()
    {
        nums.reserve(1690);
        set<long, greater<long>> seen;
        priority_queue<long, vector<long>, greater<long>> heap;
        seen.insert(1L);
        heap.push(1L);

        long currUgly, newUgly;
        vector<int> primes{2, 3, 5};
        for (int i = 0; i < 1690; ++i)
        {
            currUgly = heap.top();
            heap.pop();
            nums[i] = (int)currUgly;
            for (int j : primes)
            {
                newUgly = currUgly * j;
                if (!seen.count(newUgly))
                {
                    seen.insert(newUgly);
                    heap.push(newUgly);
                }
            }
        }
    }
};

class Solution
{
public:
    static Ugly u;
    int nthUglyNumber(int n)
    {
        return u.nums[n - 1];
    }
};

Ugly Solution::u = Ugly(); //类中static成员必须在类外实例化；

class Ugly2
{
public:
    vector<int> nums;
    Ugly2()
    {
        nums.reserve(1690);
        nums[0] = 1;
        int ugly, i2 = 0, i3 = 0, i5 = 0;

        for (int i = 1; i < 1690; ++i)
        {
            ugly = min(min(nums[i2] * 2, nums[i3] * 3), nums[i5] * 5);
            nums[i] = ugly;

            if (ugly == nums[i2] * 2)
                ++i2;
            if (ugly == nums[i3] * 3)
                ++i3;
            if (ugly == nums[i5] * 5)
                ++i5;
        }
    }
};

class Solution2
{
public:
    static Ugly2 u;
    int nthUglyNumber(int n)
    {
        return u.nums[n - 1];
    }
};
Ugly2 Solution2::u = Ugly2();

int main()
{
}